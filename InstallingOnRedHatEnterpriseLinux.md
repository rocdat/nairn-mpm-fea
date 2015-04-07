# Introduction #

Redhat EL does not come with the xerces libraries needed for parsing the XML input files.  Unless you installed this library under /usr/local/xerces3, the makefiles will generate a long list of errors.  Below are the steps needed **before NairnMPM and NairnFEA can be compiled** on your system.


# Details #

Download the xerces library (as binary) from http://xerces.apache.org/xerces-c/download.cgi (use tar.gz archive)

## No xerces library installed ##

  * If you have root permissions: as root execute
```
cd /usr/local
tar xzvf xerces-c-3.1.1-x86_64-linux-gcc-3.4.tar.gz
ln -s ./xerces-c-3.1.1-x86_64-linux-gcc-3.4 xerces3
```
  * If you do not have root permissions: install the xerces (your version may vary as xerces releases newer versions)
```
cd YOUR_NAIRN_MPM_FEA_DIRECTORY
tar xzvf xerces-c-3.1.1-x86_64-linux-gcc-3.4.tar.gz
ln -s ./xerces-c-3.1.1-x86_64-linux-gcc-3.4 xerces3
```
> Then, edit xercesSo and headerPath in ./NairnMPM/build/makefile and ./NairnFEA/build/makefile to reflect
```
xercesSo = ../../xerces3/lib/libxerces-c.so
headersPath = ../../xerces3/include
```

## A xerces library (version >= 3.0) is installed at different location ##

  * If you have root permissions: as root execute
```
cd /usr/local
ln -s PATH_TO_YOUR_XERCES_INSTALL_DIR xerces3
```
  * Alternatively, edit xercesSo and headerPath in ./NairnMPM/build/makefile and ./NairnFEA/build/makefile to reflect
```
xercesSo = PATH_TO_YOUR_XERCES_INSTALL_DIR/lib/libxerces-c.so
headersPath = PATH_TO_YOUR_XERCES_INSTALL_DIR/xerces3/include
```