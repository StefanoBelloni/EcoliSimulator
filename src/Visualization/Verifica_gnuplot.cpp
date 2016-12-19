//
//  Verifica_gnuplot.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Colori.h"

#include "GnuplotGlobal.h"

using namespace std;
void stamp_gnuplot_instructions();

void funz_clear();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)

bool Verifica_gnuplot(){
    
    cout << "The current path where gnuplot.exe is located is :\n";
    cout << gnuplotSetTerminalPlot << endl;
    
    return false;

}
#else



bool Verifica_gnuplot(){
    
    cout << "The current path where gnuplot.exe is located is :\n";
    cout << gnuplotSetTerminalPlot << endl;
    
    return false;
}


#endif


/* OLD VERSION
    
bool Verifica_gnuplot(){ 
 
     int gnuplot_inital=1;
     int risposta=0;
     
     cout << BLUE << "\nDo you have gnuplot installed on this computer?\npress 1 for yes, 0 for no,\n0 if you want to install it " << RESET;
     cin >> gnuplot_inital;
     
     if (gnuplot_inital==0) {
     
     stamp_gnuplot_instructions();
     
     system("open Instal_Gnuplot_Mac.txt");
     funz_clear();
     
     cout << BOLDRED <<"Remember to close all the file now in use ... \n" << RESET;
     cout << "--> 0 to continue \n";
     cin >> risposta;
     
     remove("Instal_Gnuplot_Mac.txt");
     
     funz_clear();               
     
     std::cout << "\n\n----------------------------------------------" << std::endl;
     std::cout << "\nThe program terminated\n" << std::endl;
     
     return true;
     }
     
     return false;

 }

*/
