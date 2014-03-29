
============================================================================================
README for the *Hearts Of Oak, Conquest of the Seas* OGRE3D-Based engine development version
============================================================================================
This is the game engine based on OGRE3D developed for the game "Hearts Of Oak, 
Conquest of the Seas" developed by the "PiratesAhoy!" community.

Thanks for reading, btw ;-)

.. contents::

1. Engine Download and Compilation instructions
===============================================
Please read this step-by-step. The full install/compile procedure requires a couple of hours, depending on your system and internet connection.
The manual steps are limited, but the building time can be quite long. So think about executing the install script before going to bed, maybe...

The sources and binaries will need approx 3Gb of Hard drive space (if you install both Debug and Release versions).

1.1 LINUX install
-----------------

1.1.1 please ensure that the following packages are installed on your machine :

 - git
 - mercurial
 - subversion
 - make
 - cmake v>=2.8.12 (you may need to `download it <http://www.cmake.org/cmake/resources/software.html>`_  and compile it)
 - gcc
 - g++
 - cpp

1.1.2 Build the engine

Open a terminal and go to the root folder of HeartsOfOakEngine and type:

- $ cmake .

or

- $ cmake -DCMAKE_INSTALL_PREFIX=<your-custom-install-dir> .

depending if you want to provide a custom install dir (which is highly suggested by the way). 

then build the dependencies by typing

- $ make

and now to build the engine, redo the same:

- $ cmake .
- $ make 


1.2 WINDOWS install
-------------------

The following procedure applies if you want tu use the MinGW compiler. If you want to use 
MS compilers, the procedure should be easier, but I let you adapt the following to you needs. ;)

1.2.1 INSTALL `MINGW compiler and its SHELL <http://www.mingw.org/>`_

- after that, enter in the mingw shell (a command line) and install **WGET** and **SSH** by typing:

~$ mingw-get install msys-wget msys-openssh
- download `UNRAR command line utility <http://www.rarlab.com/rar/unrarw32.exe>`_, install it (double-click) and copy the executable UnRAR.exe to MINGW/bin/unrar.exe (rename it to lower-case!!)
- add both **MINGW/bin** and **MINGW/msys/1.0/bin** folders to system *PATH* environment variable (replace *MINGW* with your local MinGW install folder)

1.2.2 Download and install `GIT <http://git-scm.com/downloads>`_ 

- install GIT with default install configuration

(well, if you are reading this, you should already have it installed, but anyway...)

1.2.3 Install `Tortoise MERCURIAL <http://tortoisehg.bitbucket.org/download/>`_ or `MERCURIAL alone <http://mercurial.selenic.com/downloads/>`_

- again, add the mercurial install directory to the *PATH* environment variable

1.2.4 Install `Tortoise SVN <http://tortoisesvn.net/downloads.html>`_ or `SUBVERSION alone <http://subversion.apache.org/>`_

- add the install directory to *PATH* environment variable

1.2.5 Install `CMAKE <http://www.cmake.org/cmake/resources/software.html>`_

- add it too to the *PATH* environment variable

1.2.6 Install `Direct X SDK <http://www.microsoft.com/en-us/download/details.aspx?id=6812>`_

this is required to be able to compile everything (more or less). If you get an "error code S1023":

- uninstall MSVS C++ redistributable that is already installed on your machine
- install DirectX SDK
- re-install MSVS C++ redistributable using `the last version available <http://www.microsoft.com/en-us/download/details.aspx?id=26999>`_

1.2.7 TEST THE BUILD / DOWNLOAD ENVIRONMENT

- open MingGW shell 
- change directory to the HeartsOfOak engine directory (using ~$ cd /c/path/to/HeartsOfOak/engine)
- try: 

a) $ git 
b) $ svn
c) $ hg
d) $ gcc
e) $ g++
f) $ wget
g) $ cmake

all the above commands MUST give a message that is DIFFERENT from "no such file of directory", 
this means that they are correctly installed. If you get a "no such file of directory" error, 
try adding the corresponding software to the *PATH* environment variable or to re-install the component.

1.2.8 Install and compile the engine

Open a terminal and go to the root folder of HeartsOfOakEngine and type:

- $ cmake .

or

- $ cmake -DCMAKE_INSTALL_PREFIX=<your-custom-install-dir> .

depending if you want to provide a custom install dir (which is highly suggested by the way). 

then build the dependencies by typing

- $ make

and now to build the engine, redo the same:

- $ cmake .
- $ make 

________________________________________________________________________________________________________


2. Using the Engine
===================
Well, this has still to be done ;)

2.1 Executing the engine for the first time
-------------------------------------------
todo


2.2 Using the engine with *Hearts Of Oak, Conquest of the Seas* contents
------------------------------------------------------------------------
todo

2.3 Testing with custom contents
--------------------------------
todo

3. Contributing to the Engine (please, please, PLEASE read the following section)
=================================================================================
todo

3.1 Working with GIT 
--------------------
todo

3.2 Using CMAKE
---------------
todo

3.3 Source code guidelines 
---------------------------------------------------------------
todo
