//
//  Set_MODE_Program.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 27/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Colori.h"
#include "sssr.h"
#include <limits>
#include <thread>
#include "Declar_funz.h"
#include "apngasm_Global.h"
#include "GlobalVariables.h"

using namespace std;

void funz_clear();
void set_gnuplot_Matlab_apngas(string &versione_Matlab);
void set_parameters_DEMO();
void timestamp();
void pritn_path(string versione_MATLAB);

//******************************************************************************************************

/**
 * This function set the MODE of the program: read from file, step-by-step or DEMO
 * pressing 121 you can enter the menu to set the parameters of the ausiliary programs
 * see function: set_gnuplot_Matlab_apngas(versione_Matlab)
 * NEW:
 * @param read_from_file: this is a new feature: not 100% optimal solution, allows the user to pass file to the argument of the progarm and it run anly the "script" 
 */

int set_MODE_Program(string &versione_Matlab, int &demo_mode, int read_from_file){
    
    int menu_=100;
//    int read_from_file=-1;
    
    if (read_from_file==0) {
        return read_from_file;
    }
    
    while (menu_==100) {
        
        funz_clear();
        timestamp();
        cout << BOLDRED << "--------------------------------------------------" <<endl
        << "-               Ecoli - Program.                 -"   << endl
        << "-                   set up                 -"   << endl
        << "--------------------------------------------------" << RESET <<endl;
        
//        cout << BOLDBLUE<< "Do you want to impost all the parameters for the simulations and collect the results in a folder on the Desktop?\n"<<endl;

        cout << BOLDBLUE<< "\nSETTING MENU FOR THE MODE OF INSERTING PARAMETERS?\nPRESS\n"<<endl;
        cout << BLACK << "[ 1 ] to Read Parameter from a File or preimpost them mnually"<<endl;
        cout          << "      (The analysis is done only via gnuplot)" << endl;
        cout << RED <<"[ 0 ] for a step-by-step programm "<<endl;
        cout        << "     (The analysis is done via gnuplot and Matlab" << endl;
        cout << YELLOW << "[-1 ] for a demo program (circa 20 min.)"<<endl;
        cout           << "      (The analysis is done only via gnuplot)" << RESET<< endl;
        if (automatic_!=121) {
            //cout << "...\n";
            cout << "[121] if you want to set the path of gnuplot and Matlab and apngas\n";
        }
        cout << "\n--> Option number: ";
        //    cin >> automatic_;
        getInput( automatic_);
        
        if (automatic_==121) {
            
            funz_clear();
            cout << BOLDRED << "**********************************" << endl;
            cout <<             "*      DEFAULT OPTIONS:" << endl;
            cout <<             "**********************************" << RESET << endl;
            pritn_path(versione_Matlab);            
            cout << BOLDBLUE << "**********************************" << RESET << endl;            
            int option_change=0;
            cout << BOLDRED <<"\n\nChange the paths and/or options? \n" << RESET << "press 0 for yes, 1 for no ";
            getInput(option_change);
            
            if (option_change==0) {
                funz_clearAll();
                remove(EcoliPath.c_str());               
                set_gnuplot_Matlab_apngas(versione_Matlab);
            }            

        }else {
            menu_=0;
        }
        
        }
        
        //    automatic_=-1;
        
        if (automatic_<=-1||automatic_>1) {
            automatic_=-1;
            demo_mode=0;
        }
    
        if (automatic_==1) {
            
            cout << BLUE << "\nDo you want to read the parameters from a file?\n0 to Load from a File and simulate;\n1 to Insert Manually the parameters\n121 if you want only to save parameters and not simulate " << RESET;
            getInput( read_from_file);
            if (read_from_file==0) {
                cout << "Do you wnat to load EcoliRisposte.Ecoli:\npress 0 if yes, 1 to change the name: ";
                int risposta=0;
                getInput( risposta);
                if (risposta!=0) {
                    string nameFile;
                    cout << "name of the file: ";
                    cin >> nameFile;
                    nameFile+=".Ecoli";
                    fileEcoliRisp = nameFile;
                }
            }
            
        }
    
    if (automatic_==-1) {
        set_parameters_DEMO();
        read_from_file=0;
        automatic_=1;
    }
    
    
    return read_from_file;
    
    }

//******************************************************************************************************

/**
 * In this function you can decide if you want to simulate, perform a statistical analysis or both
 */

int menu_simulation(){
    
    int stat_sim;
    
    cout << BOLDRED << "--------------------------------------------------" <<endl
    << "-               Ecoli - Program.                 -"   << endl
    << "-                   set up                 -"   << endl
    << "--------------------------------------------------" << RESET <<endl;
    
    cout << BOLDBLUE<< "What kind of program do you want to perform?\n"<<endl;
    cout << BLACK << "-> 1 Simulation" << endl;
    cout << RED <<"-> 2 Fit parameters of the model(s) (see documentation for details)" << endl;
    cout << YELLOW << "-> 3 Simulation and Fit parameters of the model(s)" << RESET<< endl;
    
    if (automatic_==1) cout << BOLDRED << "\n0 - Start the simulation/s ... " << RESET ;
    else cout << "0- Quit " << endl;
    
    sssr(stat_sim,"What kind of program do you want to perform?");
    
    // I might eliminate it since it doesn't produce the same sequence for theta, since in some model I produce more random number in between two theta !!
    funz_clear();
    
    if (stat_sim!=0){
        
        int risp=0;
        cout << BOLDBLUE<< "\nDo you want to use the same seed for the random generator\nfor every simulation in the same routine?\n";
        cout << BOLDRED <<"\nNOTE:" << RESET << " You'll have the same values for newly generated angles\nfor every simulations     only if the models are of the type _tExp"<< BOLDBLACK << "\n\npress 0 for yes, 1 for no " << RESET;
        sssr(risp, "same seed for the random generator");
        
        if (risp==0) {
            
            cout << BOLDRED << "same seed ... " << endl << RESET;
            
            same_seed=true;
            seed_ = (unsigned int) time(NULL);
            seed_r = seed_;
            
        }
    
//        cout << "seed same ... " << endl;
        
    }
    return stat_sim;
    
}

//******************************************************************************************************

//int set_save_folder(){
//
//int risp=0;
//
//    funz_clear();
//
//    cout << RED << "\nSave the data in a folder on the desktop? \npress 0 for yes, 1 for no " << RESET << endl;
//    cout << "Otherwise all data in the folder of the .exe file will be deleted" << endl;
//    if (automatic_==0) {
//        
//        getInput( risp)){
//            cout << "Invalid value ...  ";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "\nEnter again ... " << endl;
//        }
//        
//    }else {
//        risp=0;
//    }
//    
//    return risp;
//
//}
