//
//  stamp_gnuplot_instruction.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//
//  stamp_gnuplot_instructions.cpp
//  
//
//  Created by Stefano Belloni on 09/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//
//**************************************************************************************

#include <iostream>
#include <fstream>

using namespace std;

void stamp_gnuplot_instructions(){
    
    ofstream file1("Instal_Gnuplot_Mac.txt");
    
    //**************************************************************************************
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Instal_Gnuplot_Mac.txt
    //**************************************************************************************
    
    
    {
        file1 << "Gnuplot " << endl 
        << "There does not appear to be a convenient installer for the newer OS X versions including OX 10.8 Mountain Lion. To install a fully functional version of Gnuplot including x11 and png terminal support you need to download and install X11, zlib, libpng, freetype, and gdlib, before installing Gnuplot. " << endl 
        << "Install XQuartz " << endl 
        << "Download and install XQuartz. " << endl 
        << " " << endl 
        << "This is needed to set terminal x11 in Gnuplot, and also enables you to run Xwindow based graphics programs like Dr. Mike Creutz' Xtoys. " << endl 
        << "Install zlib " << endl 
        << "Download the latest source code archive for zlib - scroll down to zlib source code, version 1.2.7, tar.gz format " << endl 
        << " " << endl 
        << "Assuming you have downloaded and unpacked the distribution, open a Terminal window, cd to the zlib source folder, and configure, make, and install the library as follows: " << endl 
        << " " << endl 
        << " " << endl 
        << "macuser:~/Downloads$ cd zlib-1.2.7 " << endl 
        << "macuser:~/Downloads/zlib-1.2.7$ ./configure " << endl 
        << "macuser:~/Downloads/zlib-1.2.7$ make " << endl 
        << "macuser:~/Downloads/zlib-1.2.7$ sudo make install " << endl 
        << " " << endl 
        << "Install libpng " << endl 
        << "Download and install libpng " << endl 
        << " " << endl 
        << " " << endl 
        << "macuser:~/Downloads$ cd libpng-1.5.13 " << endl 
        << "macuser:~/Downloads/libpng-1.5.13$ ./configure " << endl 
        << "macuser:~/Downloads/libpng-1.5.13$ make " << endl 
        << "macuser:~/Downloads/libpng-1.5.13$ make check " << endl 
        << "macuser:~/Downloads/libpng-1.5.13$ sudo make install " << endl 
        << " " << endl 
        << "Install freetype " << endl 
        << "Download and install freetype using this link: http://download.savannah.gnu.org/releases/freetype/freetype-2.4.10.tar.gz " << endl 
        << " " << endl 
        << " " << endl 
        << "macuser:~/Downloads$ cd freetype-2.4.10 " << endl 
        << "macuser:~/Downloads/freetype-2.4.10$ ./configure " << endl 
        << "macuser:~/Downloads/freetype-2.4.10$ make " << endl 
        << "macuser:~/Downloads/freetype-2.4.10$ sudo make install " << endl 
        << " " << endl 
        << "Install libgd " << endl 
        << "Download and install libgd using this link: http://www.boutell.com/gd/http/gd-2.0.33.tar.gz " << endl 
        << " " << endl 
        << " " << endl 
        << "macuser:~/Downloads$ cd gd-2.0.33 " << endl 
        << "macuser:~/Downloads/gd-2.0.33$ ./configure " << endl 
        << "macuser:~/Downloads/gd-2.0.33$ make " << endl 
        << "macuser:~/Downloads/gd-2.0.33$ sudo make install " << endl 
        << " " << endl 
        << "Install Gnuplot " << endl 
        << "Download and install Gnuplot " << endl 
        << " " << endl 
        << "Note the --with-readline=builtin in the configure command - the INSTALL file explains why it is needed. " << endl 
        << " " << endl 
        << " " << endl 
        << "macuser:~/Downloads$ cd gnuplot-4.6.0 " << endl 
        << "macuser:~/Downloads/gnuplot-4.6.0$ ./configure --with-readline=builtin " << endl 
        << "macuser:~/Downloads/gnuplot-4.6.0$ make " << endl 
        << "macuser:~/Downloads/gnuplot-4.6.0$ sudo make install " << endl 
        << " " << endl 
        << " " << endl 
        << "Test your Gnuplot using terminal: " << endl 
        << " " << endl 
        << " " << endl 
        << "macuser:~ gnuplot " << endl 
        << "gnuplot>  plot sin(x) " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
}
