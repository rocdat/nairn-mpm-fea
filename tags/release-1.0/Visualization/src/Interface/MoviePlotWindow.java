/*******************************************************************
	MoviePlotWindow.java
	NairnFEAMPMViz

	Created by John Nairn on 2/27/07.
	Copyright 2007 RSAC Software. All rights reserved.
*******************************************************************/

import java.awt.*;

import javax.swing.*;
import java.text.*;
import java.awt.event.*;
import java.util.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;

public class MoviePlotWindow extends NFMVFrame implements Runnable
{
	static final long serialVersionUID=12L;
	
	// constants
	public static final int FRAME_RATE=30;
	
	// variables
	protected ResultsDocument resDoc;
	protected DocViewer docView;
	protected MeshPlotView plotView;
	protected MovieControls movieControls;
	protected boolean runFlag;
	protected int movieComponent;
	protected int plotType;
	
	// command file chooser
	private JFileChooser chooser=new JFileChooser();
	
	// initialize
	public MoviePlotWindow(ResultsDocument gResDoc,DocViewer gDocView)
	{	super(gResDoc.name);
		resDoc=gResDoc;
		docView=gDocView;
		setFramePrefs("Mesh Window Width",800,"Mesh Window Height",600);
		
		// size and location
		Dimension d=setFrameLocAndSize(this);
		
		// add plot view (entire window for now)
		Container content=getContentPane();
		plotView=new MeshPlotView(resDoc);
		content.add(plotView,BorderLayout.CENTER);
		
		// add controls
		movieControls=new MovieControls(d.width,resDoc,this);
		content.add(movieControls,BorderLayout.SOUTH);
		
		NFMVPrefs.setWorkspace(chooser);
	}

	// make menu bar on launch
	protected void makeMenuBar()
	{	//Create the menu bar
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		// File menu
		JMenu menu = new JMenu("File");
		menuBar.add(menu);
		makeMenuItem(menu,"Open...","OpenFile",KeyEvent.VK_O,NairnFEAMPMViz.appCtrl);
		makeMenuItem(menu,"Export Graphics...","ExportFrame",KeyEvent.VK_E,this);
		menu.addSeparator();
		makeMenuItem(menu,"Close","Close",KeyEvent.VK_W,this);
		
		// Window menu
		menu = new JMenu("Window");
		menuBar.add(menu);
		makeMenuItem(menu,"Analysis Results","ShowResults",KeyEvent.VK_D,this);
	}
	
	//----------------------------------------------------------------------------
	// detachable thread and methods for controlling movies
	//----------------------------------------------------------------------------
	
	public void run()
	{
		Date theTime,endTime;
		long pause;
		
		movieControls.setPlaying(true);
		
		try
		{	while(movieControls.incrementArchiveIndex() && runFlag)
			{	theTime=new Date();
			
				try
				{	loadPlotData();
				}
				catch(Exception e)
				{	dispose();
					Toolkit.getDefaultToolkit().beep();
					JOptionPane.showMessageDialog(null,"Error loading plot data: "+e.getMessage());
					break;
				}
				catch(OutOfMemoryError me)
				{	dispose();
					Toolkit.getDefaultToolkit().beep();
					JOptionPane.showMessageDialog(null,"Out of memory error: "+me.getMessage());
					break;
				}
				plotView.repainting=true;
				plotView.repaint();
				
				endTime=new Date();
				pause=FRAME_RATE-endTime.getTime()+theTime.getTime();
				if(pause>0) Thread.sleep(pause);
				while(plotView.repainting)
				{	Thread.sleep(0);
				}
			}
		}
		catch(InterruptedException e) {}
		
		// reset flags and buttons before done
		movieControls.setPlaying(false);
		runFlag=false;
	}
	
	// change to new time unless in a movie
	public void changeArchiveIndex(int newIndex)
	{	if(runFlag) return;
		try
		{	loadPlotData();
			plotView.repaint();
		}
		catch(Exception e)
		{	dispose();
			Toolkit.getDefaultToolkit().beep();
			JOptionPane.showMessageDialog(null,"Error loading plot data: "+e.getMessage());
		}
		catch(OutOfMemoryError me)
		{	dispose();
			Toolkit.getDefaultToolkit().beep();
			JOptionPane.showMessageDialog(null,"Out of memory error: "+me.getMessage());
		}
	}
	
	// start plot over at new initial index and possibly new component and options
	public void beginNewIndexNewComponent(int newIndex,int newComponent)
	{	boolean changedComponent= (movieComponent!=newComponent);
		movieComponent=newComponent;
		ControlPanel controls=resDoc.docCtrl.controls;
		plotView.setOptions(controls.getOptions(),movieComponent,plotType);
		
		if((!movieControls.setArchiveIndex(newIndex) && changedComponent) || resDoc.isFEAAnalysis())
		{	changeArchiveIndex(newIndex);
		}
		else
			plotView.repaint();
	}
	
	// load everything needed to plot or replat data - must override
	public void loadPlotData() throws Exception { }
	
	//----------------------------------------------------------------------------
	// handle movie commands
	//----------------------------------------------------------------------------
	
	public void actionPerformed(ActionEvent e)
	{   String theCmd=e.getActionCommand();
	
		if(theCmd.equals("Play"))
		{	if(runFlag)
			{   runFlag=false;
				movieControls.setPlaying(false);
			}
			else
			{	// movie thread
				runFlag=true;
				Thread movieThread=new Thread(this);
				movieThread.start();
			}
		}
		
		else if(theCmd.equals("Rewind"))
			movieControls.setArchiveIndex(0);
			
		else if(theCmd.equals("ShowResults"))
		{	docView.toFront();
		}
		
		else if(theCmd.equals("ExportFrame"))
		{	// get file if need it
			int result = chooser.showSaveDialog(this);
			if(result != JFileChooser.APPROVE_OPTION) return;
			File saveFile=NairnFEAMPMViz.CheckFileStatus(chooser.getSelectedFile(),this,"png");
			if(saveFile==null) return;
			
			// save to png file
			try
			{	BufferedImage frameCopy=plotView.frameImage();
				ImageIO.write(frameCopy,"png",saveFile);
			}
			catch(Exception fe)
			{	Toolkit.getDefaultToolkit().beep();
				JOptionPane.showMessageDialog(this,"Error exporting graphic image: " + fe);
			}
		}
		
		else
			super.actionPerformed(e);
	}

	//----------------------------------------------------------------------------
	// Window events
	//----------------------------------------------------------------------------
	
	public void windowOpened(WindowEvent e)
	{	int newComponent=docView.controls.getPlotComponent();
		beginNewIndexNewComponent(docView.controls.getArchiveIndex(),newComponent);
		plotView.setFirstLoad(true);
	}
	public void	windowClosed(WindowEvent e)
	{	docView.closePlotFrame(this);
	}
	
	//----------------------------------------------------------------------------
	// accessors
	//----------------------------------------------------------------------------
	
	public MeshPlotView getPlotView() { return plotView; }
	public boolean isMovieRunning() { return runFlag; }
	
	//----------------------------------------------------------------------------
	// static methods
	//----------------------------------------------------------------------------
	
	// nice format for any double
	public static String formatDouble(double d) { return formatDouble(d,false); }
	
	// nice format for any double
	public static String formatDouble(double d,boolean noFraction)
	{	StringBuffer ddec;
		int dlog;
		double da;
		NumberFormat nf=NumberFormat.getInstance();
		
		// display number in good format
		da=d;
		if(d<0) da=-d;
		if(da>1e9)
		{	dlog=(int)(Math.log(da)/Math.log(10.));
			d*=Math.pow(10,-dlog);
			nf.setMaximumFractionDigits(5);
			nf.setMinimumFractionDigits(1);
			ddec=new StringBuffer(nf.format(d));
			ddec.append("e+");
			nf.setMaximumFractionDigits(0);
			ddec.append(nf.format(dlog));
			return ddec.toString();
		}
		else if(da>1.e6)
		{	nf.setMaximumFractionDigits(0);
		}
		else if(da>1.e3)
		{	nf.setMaximumFractionDigits(2);
			if(noFraction) nf.setMaximumFractionDigits(0);
		}
		else if(da>1.)
		{	nf.setMaximumFractionDigits(4);
			if(noFraction) nf.setMaximumFractionDigits(0);
		}
		else if(da>1.e-2)
		{	nf.setMaximumFractionDigits(6);
		}
		else if(da==0.)
		{	nf.setMaximumFractionDigits(0);
		}
		else
		{	if(noFraction) return "0";
			dlog=(int)(Math.log(da)/Math.log(10.));
			dlog--;
			d*=Math.pow(10,-dlog);
			nf.setMaximumFractionDigits(5);
			nf.setMinimumFractionDigits(1);
			ddec=new StringBuffer(nf.format(d));
			ddec.append("e");
			nf.setMaximumFractionDigits(0);
			ddec.append(nf.format(dlog));
			return ddec.toString();
		}
		return nf.format(d);
	}
}
