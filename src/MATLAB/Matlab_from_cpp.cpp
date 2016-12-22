//
//  Matlab_from_cpp.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 03/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//
//  Matlab_from_cpp.cpp
//  Menu_Vergassola_Celani_SFDE_COLI_PD_1.0_PLOT
//
//  Created by Stefano Belloni on 09/08/13.
//  Copyright (c) 2013 Heidelberg Universitaet. All rights reserved.
//

// il programma crea i file da essere letti in "SDE_Towards_Realism_1.8" (e li sposta anche laggiù)


#include <iostream>
#include <cstdio>
#include <cstdlib>


using namespace std;


// COSTANTI

#include <sstream>
#include <iostream>

#include "MATLAB_Global.h"


#include "constants.h" //#define pi 3.141592653589793238462

void Scrittura_m_files();
void Scrittura_m_filesAutomatic();

/**
 * THis function is use to call MATLAB in the "terminal form" from the program.
 * We create the .m files, run MATLAB and delete the .m files afterwords
 * NOTE: We didn't chck this on Windows.
 */


int Matlab_from_cpp(int sel_prog, string versione_Matlab){    
    
    string command;
    
    Scrittura_m_files();
//    Scrittura_m_filesAutomatic();
    
    switch (sel_prog) {
        {    
        case 1:
            // we cut location of MATLAB, its version and the call. We run as first thing
            // Movie_Matlab_from_cpp where we save all the step we have to performed.
            // We were not able to pass more then one command to MATLAB once it's open
        	command=MATLAB_loc+versione_Matlab+MATLAB_call+"Movie_Matlab_from_cpp";
			break;
            
        }
        {
        default:
            cout << "Error, no data properly fit\n";
            return 1;
            break;
        }
    }
    
    cout << "MATLAB" << endl;
    
    system(command.c_str());
    
    
//********************************************************************************************80
// CANCELLO .m FILES
//********************************************************************************************80

    remove("Caricamento_filmato_hist.m");
    remove("Movie_Matlab_from_cpp.m");
    remove("functionC.m");
    remove("hist3.m");
    remove("Evolution_Mass_center.m");
    remove("Movie_Matlab_from_cpp_and_single.m");
    remove("functionC1.m");
    remove("traiettorie_singole.m");
    remove("Filmatohist.m");
    remove("Save_Movie_avi.m");
    remove("function_c.m");
    remove("MovieCpp2matlab.m");
    remove("distribuzione_tempi.m");
    remove("getkey.m");
    remove("Call_Matlab.txt");

//********************************************************************************************80
    
    return 0;
    
}
