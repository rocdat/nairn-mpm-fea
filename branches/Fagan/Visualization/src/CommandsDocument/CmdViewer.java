/*
 * CmdViewer
 * NairnFEAMPMViz Application
 * 
 * Created 
 */

import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;
import javax.swing.*;

import geditcom.JNFramework.*;

public class CmdViewer extends JNCmdTextDocument
{
	private static final long serialVersionUID = 1L;
	
	private ProcessBuilder builder;
	private Thread runThread=null;
	private boolean openMesh=false;
	private boolean wasSubmitted=false;
	private ConsolePane soutConsole;
	private DocViewer linkedResults=null;
	
	// Actions
	private BgAnalysisAction bgAnalysisCammand = new BgAnalysisAction();
	private CheckAnalysisAction checkAnalysisCammand = new CheckAnalysisAction();
	private ShowPartnerAction showPartnerCommand = new ShowPartnerAction();

	//----------------------------------------------------------------------------
	// Initialize
	//----------------------------------------------------------------------------
	
	public CmdViewer(String aType)
	{	super(aType,null,new ConsolePane());
		soutConsole=(ConsolePane)console;
	
		setFramePrefs("Commands Window Width",600,"Commands Window Height",800);
		
		makeMenuBar();
		
		// tool bar icons
		addDefaultToolBar(this);
		addToolBarIcon(null,"saveDocument","Save this document to a file.",this);
		
		Class<?> baseClass=JNApplication.main.getClass();
		addToolBarBar();
		ImageIcon goNext=new ImageIcon(baseClass.getResource("Resources/go-next.png"));
		addToolBarIcon(goNext,null,"Run FEA or MPM Analysis.",getRunAnalysisAction());
		ImageIcon goLast=new ImageIcon(baseClass.getResource("Resources/go-last.png"));
		addToolBarIcon(goLast,null,"Check mesh for FEA or MPM Analysis.",checkAnalysisCammand);
		ImageIcon doStop=new ImageIcon(baseClass.getResource("Resources/process-stop.png"));
		addToolBarIcon(doStop,null,"Run currently running FEA or MPM Analysis.",getStopAnalysisAction());

		addToolBarBar();
		ImageIcon showRes=new ImageIcon(baseClass.getResource("Resources/image-x-generic.png"));
		addToolBarIcon(showRes,null,"Show associated simulation results (if available).",showPartnerCommand);

		finishFrameworkWindow(true);
	}
	
	// make menu bar on launch
	protected void makeMenuBar()
	{
		// Create the menu bar
		JMenuBar menuBar = new JMenuBar();
		if(!JNApplication.isMacLNF())
			menuBar.add(defaultApplicationMenu());		// Application menu
		menuBar.add(defaultFileMenu(this));				// File menu
		
		// Edit menu
		JMenu menu = defaultEditMenu(true);
		menuBar.add(menu);
		menu.addSeparator();
		menu.add(getGoToLineAction());
		
		// Analyze menu
		menu = new JMenu("Analyze");
		menuBar.add(menu);
		menu.add(getRunAnalysisAction("Run FEA/MPM Analysis"));
		menu.add(bgAnalysisCammand);
		menu.add(checkAnalysisCammand);
		menu.addSeparator();
		menu.add(getStopAnalysisAction());
		
		// Window
		menu = new JMenu("Window");
		menuBar.add(menu);
		if(JNApplication.isMacLNF())
		{	menu.add(JNApplication.main.getOpenHelpAction());
		}
		menu.add(showPartnerCommand);
		menu.addSeparator();
		setWindowMenu(menu);

		// add the menu bar
		setJMenuBar(menuBar);
	}
	
	// default file menu refering to document target
	public static JMenu defaultFileMenu(JNDocument target)
	{	JMenu fileMenu=target.defaultFileMenu();
		JMenuItem newMPM=fileMenu.getItem(1);
		newMPM.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N,
				JNApplication.menuKeyMask()+ActionEvent.SHIFT_MASK));
		return fileMenu;
	}
	
	// default tool bar icons
	public static void addDefaultToolBar(JNDocument target)
	{
		// tool bar icons
		target.addToolBarBar();
		target.addToolBarIcon(null,null,"Open the preferences window.",JNApplication.main.getOpenPreferencesAction());
		target.addToolBarIcon(null,null,"Open the help information window.",JNApplication.main.getOpenHelpAction());
		
		target.addToolBarBar();
		target.addToolBarIcon(null,"openDocument","Open a saved document file.",JNApplication.main);
		Class<?> baseClass=JNApplication.main.getClass();
		ImageIcon newMPM=new ImageIcon(baseClass.getResource("Resources/document-new.png"));
		target.addToolBarIcon(newMPM,"newDocumentMPMCmd","Create a new document.",JNApplication.main);
		ImageIcon newFEA=new ImageIcon(baseClass.getResource("Resources/document-newfea.png"));
		target.addToolBarIcon(newFEA,"newDocumentFEACmd","Create a new document.",JNApplication.main);
	}
	
	//----------------------------------------------------------------------------
	// handle running analysis
	//----------------------------------------------------------------------------
	
	// default command run method passed to custom one
	public void runAnalysis() { runNFMAnalysis(false,false); }
	
	// Run FEA or MPM analysis
	public void runNFMAnalysis(boolean doBackground,boolean checkMesh)
	{
		// only allowed if the commands have been saved
		if(getFile()==null)
		{	JNApplication.appBeep();
			JOptionPane.showMessageDialog(this,"The XML input commands have to be saved to a file before running an analysis.");
			return;
		}
		
		// what is process is current running?
		if(running)
		{	JNApplication.appBeep();
			String message="An FEA or MPM process is currently running.\nDo you want stop it and start a new process?";
			int result=JOptionPane.showConfirmDialog(this, message, "Continue?", JOptionPane.OK_CANCEL_OPTION);
			if(result==JOptionPane.CANCEL_OPTION) return;
			if(runThread.isAlive())
			{	running=false;
				try
				{	runThread.join();
				}
				catch(InterruptedException ie)
				{
				}
			}
		}
		
		// save the commands
		File inFile=getFile();
		
		// prepare output path
		boolean mpmAnalysis=isMPMAnalysis();
		boolean doValidate;
		String myCmd,myDTD;
		if(mpmAnalysis)
		{	if(!soutConsole.setOutputPath(inFile,"mpm")) return;
		
			// get path to NairnFEA and NairnMPM
			myCmd=NFMVPrefs.prefs.get(NFMVPrefs.NairnMPMKey,NFMVPrefs.NairnMPMDef);
			myDTD=NFMVPrefs.prefs.get(NFMVPrefs.NairnMPMDTDKey,NFMVPrefs.NairnMPMDTDDef);
			doValidate=NFMVPrefs.prefs.getBoolean(NFMVPrefs.NairnMPMValidateKey,NFMVPrefs.NairnMPMValidateDef);
		}
		else
		{	if(!soutConsole.setOutputPath(inFile,"fea")) return;
		
			// get path to NairnFEA and NairnMPM
			myCmd=NFMVPrefs.prefs.get(NFMVPrefs.NairnFEAKey,NFMVPrefs.NairnFEADef);
			myDTD=NFMVPrefs.prefs.get(NFMVPrefs.NairnFEADTDKey,NFMVPrefs.NairnFEADTDDef);
			doValidate=NFMVPrefs.prefs.getBoolean(NFMVPrefs.NairnFEAValidateKey,NFMVPrefs.NairnFEAValidateDef);
		}
		
		// insert DTD path if validating
		if(doValidate)
		{	if(!insertDTD(myDTD))
			{	JNApplication.appBeep();
				JOptionPane.showMessageDialog(this,"The file does not start with the required <?xml ...?> element.");
				return;
			}
		}
		
		// copy command file (if needed)
		if(!saveDocument()) return;
		File outFile=soutConsole.getFile();
		if(!inFile.getParent().equals(outFile.getParent()))
			inFile=saveCopyOfCommands(new File(outFile.getParent()+"/"+inFile.getName()),this);
		if(inFile==null) return;
			
		// set commands and options
		ArrayList<String> cmds=new ArrayList<String>(20);
		
		// start login bash shell
		cmds.add(NFMVPrefs.prefs.get(NFMVPrefs.ShellKey,NFMVPrefs.ShellDef));
		cmds.add("--login");			// only needed for windows
		cmds.add("-c");
		
		// build shell command
		StringBuffer shell=new StringBuffer();
		
		// cd to file directory
		shell.append("cd ");
		String shellCD=outFile.getParent();
		if(NairnFEAMPMViz.isWindowsOS())
		{	//shellCD=shellCD.replace('\\','/');
			shellCD=PathToCygwin(shellCD);
		}
		if(shellCD.indexOf(' ')>=0)
			shell.append("'"+shellCD+"'; ");
		else
			shell.append(shellCD+"; ");

		// executable (as shell command)
		if(NairnFEAMPMViz.isWindowsOS())
		{	//myCmd=myCmd.replace('\\','/');
			myCmd=PathToCygwin(myCmd);
		}
		if(myCmd.indexOf(' ')>=0)
			shell.append("'"+myCmd+"'");
		else
			shell.append(myCmd);
			
		// options (-a to abort after setup, -v to validate)
		if(checkMesh) shell.append(" -a");
		if(doValidate) shell.append(" -v");
			
		String inName=inFile.getName();
		if(inName.indexOf(' ')>=0)
			shell.append(" '"+inName+"'");
		else
			shell.append(" "+inName);
		
		if(doBackground)
		{	shell.append(" >& ");
			
			// output file
			String outFileName=outFile.getName();
			if(outFileName.indexOf(' ')>=0)
				shell.append("'"+outFileName+"'");
			else
				shell.append(outFileName);
				
			shell.append(" &");
		}
		
		// add the shell command
		System.out.println(shell);
		cmds.add(shell.toString());

		// create the process and set working directory
		builder = new ProcessBuilder(cmds);
		//Map<String, String> environ = builder.environment();
		//builder.directory(myFile.getParentFile());
		builder.redirectErrorStream(true);
		
		runThread=new Thread(this);
		running=true;
		openMesh=checkMesh;
		wasSubmitted=doBackground;
		runThread.start();
	}
	
	// insert DTD path into commands
	public boolean insertDTD(String dtdPath)
	{
		String initText=cmdField.getCommands();
		int offset=initText.indexOf("<!DOCTYPE"),endOffset=0;
		int docOffset=offset;
		if(offset>0)
		{	offset=initText.indexOf("JANFEAInput",offset+9);
			if(offset>0)
			{	offset=initText.indexOf("SYSTEM",offset+6);
			
				// if filed <!DOCTYPE JANFEAInput SYSEM located quoted path name
				if(offset>0)
				{	char startChar=' ';
					while(offset<initText.length())
					{	startChar=initText.charAt(offset);
						if(startChar=='\'' || startChar=='\"') break;
						if(startChar=='\n' || startChar=='\r')
						{	offset=0;
							break;
						}
						offset++;
					}
					if(offset>0)
					{	offset++;
						endOffset=offset;
						while(endOffset<initText.length())
						{	char endChar=initText.charAt(endOffset);
							if(endChar==startChar) break;
							if(endChar=='\n' || endChar=='\r')
							{	offset=0;
								break;
							}
							endOffset++;
						}
					}
				}
			}
		}
		dtdPath=PathToCygwin(dtdPath);
		if(offset>0)
		{	// insert path if needed
			String oldDTD=initText.substring(offset,endOffset);
			if(!oldDTD.equals(dtdPath))
			{	cmdField.setCommands(initText.substring(0,offset)+dtdPath+
							initText.substring(endOffset,initText.length()));
				changed=true;
			}
		}
		else if(docOffset>0)
		{	docOffset+=9;
			cmdField.setCommands(initText.substring(0,docOffset)+" JANFEAInput SYSTEM '"
				+dtdPath+"'"+initText.substring(docOffset,initText.length()));
			changed=true;
		}
		else
		{	// insert <!DOCTYPE
			docOffset=initText.indexOf("?>");
			if(docOffset<=0) return false;
			docOffset+=2;
			cmdField.setCommands(initText.substring(0,docOffset)
						+"\n<!DOCTYPE JANFEAInput SYSTEM '"+dtdPath+"'>"
						+initText.substring(docOffset,initText.length()));
			changed=true;
		}
		
		return true;
	}

	// convert Windows path to cygwin
	private String PathToCygwin(String path)
	{	if(JNApplication.isWindowsOS())
		{	path=path.replace('\\','/');
			// Replace C: by /cygdrive/c (if needed)
			if(path.charAt(1)==':')
			{	char drive=path.charAt(0);
				if(drive<'a') drive+=32;
				path="/cygdrive/"+drive+path.substring(2);
			}
		}
		return path;
	}

	// save commands and return saved file (or null)
	public File saveCopyOfCommands(File saveFile,JFrame fileWindow)
	{
		// save to saveFile
		try
		{	FileWriter theFile=new FileWriter(saveFile);
			theFile.write(cmdField.getCommands());
			theFile.flush();
			theFile.close();
		}
		catch (Exception fe)
		{	JNApplication.appBeep();
			JOptionPane.showMessageDialog(fileWindow,"Error writing XML input  commands: " + fe);
			return null;
		}
		
		return saveFile;
	}
	
	//----------------------------------------------------------------------------
	// detachable to run the process
	//----------------------------------------------------------------------------
	
	public void run()
	{	
		try
		{	Process process = builder.start();
			InputStream is = process.getInputStream();
			InputStreamReader isr = new InputStreamReader(is);
			BufferedReader br = new BufferedReader(isr);
			
			soutConsole.clear();
			String line;
			while((line = br.readLine()) != null)
			{	soutConsole.appendLine(line);
				if(!running) break;
			}
			
			// if done and no errors, save and open for visualization
			if(running)
			{	int result=1;
				try
				{	process.waitFor();
					result=process.exitValue();
				}
				catch (InterruptedException ie) {}
				if(result==0)
				{	if(wasSubmitted)
					{	JOptionPane.showMessageDialog(this,"FEA or MPM job submitted"+soutConsole.processID());
					}
					else if(soutConsole.saveOutput(this))
					{	if(linkedResults!=null)
						{	linkedResults.windowClosing(null);
						}
						NairnFEAMPMViz.main.openDocument(soutConsole.getFile());
						linkedResults=(DocViewer)NairnFEAMPMViz.main.frontDocument();
						linkedResults.setCommandsWindow(this);
						if(linkedResults!=null && openMesh)
						{	linkedResults.checkMeshNow();
						}
					}
				}
				else
					soutConsole.saveOutput(this);		// save in case needed
			}
			else
				soutConsole.saveOutput(this);			// save in case needed
			is.close();
			process.destroy();
		}
		catch(IOException tpe)
		{	JNApplication.appBeep();
			JOptionPane.showMessageDialog(this,tpe.toString());
		}
		running=false;
	}

	//----------------------------------------------------------------------------
	// Accessors
	//----------------------------------------------------------------------------
	
	// empty if no text or if has welcome message
	public boolean isEmptyDocument()
	{	String cmds=cmdField.getCommands();
		if(cmds.length()==0) return true;
		if(cmds.equals("Welcome to "+NairnFEAMPMViz.appNameReadable+", "+NairnFEAMPMViz.versionReadable)) return true;
		return false;
	}
	
	// look for required MPMHeader element
	public boolean isMPMAnalysis()
	{	return cmdField.getCommands().indexOf("<MPMHeader>")>0;
	}
	
	// call by results when it closes
	public void setLinkedResults(DocViewer someResults) { linkedResults=someResults; }
	
	// tell linked results your are closing
	public void windowClosed(WindowEvent e)
	{	if(linkedResults!=null) linkedResults.setCommandsWindow(null);
		super.windowClosed(e);
	}

	//----------------------------------------------------------------------------
	// Actions as inner classes
	//----------------------------------------------------------------------------
	
	// action for stop analysis menu command
	protected class BgAnalysisAction extends JNAction
	{	private static final long serialVersionUID = 1L;

		public BgAnalysisAction()
		{	super("Background FEA/MPM Analysis...",KeyEvent.VK_B);
		}
 
		public void actionPerformed(ActionEvent e) { runNFMAnalysis(true,false); }
	}

	// action for stop analysis menu command
	protected class CheckAnalysisAction extends JNAction
	{	private static final long serialVersionUID = 1L;

		public CheckAnalysisAction()
		{	super("Test FEA/MPM Mesh...",KeyEvent.VK_T);
		}
 
		public void actionPerformed(ActionEvent e) { runNFMAnalysis(false,true); }
	}
	
	// action to shaw partner menu command
	protected class ShowPartnerAction extends JNAction
	{	private static final long serialVersionUID = 1L;

		public ShowPartnerAction()
		{	super("Show Results");
		}
 
		public void actionPerformed(ActionEvent e)
		{	if(linkedResults!=null)
				linkedResults.toFront();
			else
				JNApplication.appBeep();
		}
	}
}