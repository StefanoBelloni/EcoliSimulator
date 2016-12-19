#EcoliSimulator
Version 2.0.1a

The program EcoliSimulator is a command-line based simulator of different models for Ecoli, which produce graphical, numerical and Statistical analysis of the result obtained.
The documentation can be found at https://stefanobelloni.github.io/EcoliSimulator/

A small video about this program can be found at http://www.stefanobelloni.it/#EcoliSimulator

-------------------------------------------------------------------------------

Contents
========

I.   Introduction

II.  External Programs

1.) Required Packages

- gnuplot
- png reader
- LateX compiler

2.) Optional Packages
- MATLAB
- apngasm

III. Installation

IV.  Lunch the Program

-------------------------------------------------------------------------------


I) Introduction
===============

The program EcoliSimulator is a command-line based simulator of different models for Ecoli, which produce graphical, numerical and Statistical analysis of the result obtained.

It is design to be usable in a step-by-step (the duration of the simulations are estimated) or a pre-set mode and produces, a Latex file where all the informations about the simulations and output are collected in a systematic, an hopefully, coherent and readable version.


II) External Programs
=====================

1) Required Programs
--------------------

The software-packages mentioned here are mandatory. You will not be
able to use EcoliSimulator without them.


- gnuplot   — is a portable command-line driven graphing utility for Linux, OS/2, MS
Windows, OSX, VMS, and many other platforms. The source code is 
copyrighted but freely distributed it is important that the option of set 
terminal 'pngcairo'  and 'gif' are available.

- .gif or .png reader - any program able to open .png or .gif files with multiple layers. In 
order to see while the program is running the video it is 
recommended to have installed Mozilla Firefox - (known simply as 
Firefox) is a free and open-source web browser.

- LateX compiler - In order to read and visualize the report it is necessary to have 
installed a program which read LateX language.

NOTE: To uese the multithread options you need a c++ compiler which support c++11


2) Optional Programs
--------------------

- apngasm   — Creates highly optimized Animated PNG files from PNG/TGA image sequences.
Take care to have the “command line” version.
- Matlab - Commercial Software produced by The MathWorks base on a high-level language and interactive environment.


III) Installation
======================

To instal the program you can use the Makefile or cmake (or "by hand")
NOTE: In order to install automatically the External programs it is raccomanded to have installed 

- GNU make (https://www.gnu.org/software/make/)
- curl (https://curl.haxx.se/)
- cmake (https://cmake.org/)
- a program to decompress .zip files. For example, for unix unzip, for windows 7zip (http://www.7-zip.org/)
- c++ compiler (g++) with support for c++11

If you are using different programs to achive these tasks, you can modify the definitions in the Makefile.

- open a terminal and navigate to the folder EcoliSimulator_0.0.1a, which contains src/ and /include.

=======
    -Makefile: You have many options according to what you want install. Notice that the Makefile does not check if a program is already installed.
        
        - Install only EcoliSimulator:
            - type make
                >:EcoliSimulator stefanobelloni$ make 
              to process the Makefile
              it might happend that you need to type make.exe or the complete path to "make" or mingw32-make.exe according to your needs.
                NOTE: If you use the Makefile and the compiler g++ is not in the PATH variable, 
                      redefine the variable CC accordingly, for example if the compiler you want to use is g++ and 
                      it is inside the folder C:\Dev-cpp\Ming64\bin\g++.exe, substitute the definition of the variable CC as follows:
                                  CC = C:\Dev-cpp\Ming64\bin\g++.exe

        - Install gnuplot 
              type make gnuplot
                >:EcoliSimulator stefanobelloni$ make gnuplot
        For windows and Os X the installation of gnuplot will not be invasive, in the sense that
        - in Windows gnuplot is installed inside the bin folder of EcoliSimulator
        - in Os X, when you drag gnuplot in the Application folder the path to the program will be 
                /Applications/Gnuplot.app/Contents/Resources/bin/ 
            NOTE: this version on gnuplot does not have the terminal .gif. 
            You need apngasm and tell the program to use it with the option --apngasm
        
        - Install apngasm (binary)
              type make apngasm
                >:EcoliSimulator stefanobelloni$ make apngasm

        - Intsall apngasm from source (you need cmake) This will create the executible in the bin folder.            
                >:EcoliSimulator stefanobelloni$ make apngasm_src

        - To install along with EcoliSimulator also gnuplot and apngasm.
                >:EcoliSimulator stefanobelloni$ make install

        - To show the different options to build the program.
                >:EcoliSimulator stefanobelloni$ make help

        - If you do not want to use c++11 features, first of all multitrhread simulations, you can deactivate it by passing the option opt=NO_M_THREAD to make, i.e. write
                >:make [options] opt=NO_M_THREAD

    -cmake: This will only build EcoliSimulator in the bin folder.
    
        - create a folder (i.e. build), 
            >:build stefanobelloni$ mkdir build
        - move inside it
            >:build stefanobelloni$ cin build
        - type: 
            >:build stefanobelloni$ cmake ..
        - then type
            >:build stefanobelloni$ make
        - you can use the options of cmake to customize the installation path.

 By default the Makefile and the cmake will create a bin folder, where the executable can be found and a build folder where the .o objects are saved. 

    -compile by hand:
    
        -create a folder (for example be it bin)
            >:build stefanobelloni$ mkdir bin
        - go inside it 
            >:build stefanobelloni$ cin bin
        - type
            g++ -std=c++11 -I../include -Wall -o EcoliSimulator ../src/*.cpp ../src/*/*.cpp
            (instead of g++, use the compiler you prefer ...)
    

IV) Lunch the Program
======================

Open a terminal windows and navigate till the folder “/bin” to lunch the program.
You can visualize the different option you can pass to the program, by typing —help.

Aviable options:

    -  --matlab=x  ........  set version matlab 'x'
    -  --gnuplot=y ........  set path to gnuplot 'y'
    -  --file .............  read the file 'EcoliRisposte.Ecoli' to perform the simulations
    -  --file=pathtofile ..  read file given by pathtofile.
                            (if the file is where the executible is run, type only the name)
    -  --clear ............  clear all possible trash data
    -  --qclear ............  clear all possible trash data and exit
    -  --reset ............  rest cleaning all files and settings
    -  --script ...........  there's no initial page, useful if you run a script
    -  --j=n   ............  max number of cores to use: default is half of the aviable cores
    -  --nocolors ...........it uses the default colors of the terminal.
                             use it, if you have some strange colors for the terminal, you might not be
                             able to read everything ... (not strange is white or black)
    - --apngasm=x ......... x is the path to apngasm (with / or \\) if apngasm is in the current 
                            directory type:
                            --apngasm=./ for Unix , just --apngasm= on Windows
                            if x is set to no, then the video is not create with apngasm ('.png' file), 
                            but as a '.gif' file.
                            --apngams tells to create multilayer '.png' file.
                            NOTE: The defoult (for the first lunch) is '.gif' file.
    - --clclog ............ clear the file Ecoli.LogEcoli.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
