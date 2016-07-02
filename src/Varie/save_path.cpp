//
//  save_path.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>

#include "GnuplotGlobal.h"
#include "apngasm_Global.h"
#include "MATLAB_Global.h"
#include "GlobalVariables.h"
#include "Colori.h"
#include "Dir_Global.h"
#include "Declar_funz.h"

#include "ErrorsDefinition.h"

#include <limits>
#include <ctime>


using namespace std;

/**Check if a file with the given name exists*/

bool is_file_exist(const char* fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

/**
 * The function read the file 'EcoliPath.Ecoli', where there are saved path and option for the programs gnuplot, agapng and matlab
 */

int import_path(string version_MATLAB){
    
    if (!is_file_exist(EcoliPath.c_str())) {
        cout << "Error: File does not exists... \n";
        return 1;
    }else {
        ifstream path(EcoliPath.c_str());
        string temp_string;
        
        if (!path.is_open()) {
            cout << "Error: Can't open File ... \n";
            return 1;
        }
        
        getline(path,temp_string);
        
        // check version
        string compare_str(VERSION);
        compare_str='#'+compare_str;
        
        if (temp_string.compare(compare_str)==0){
            cout << VERSION << endl;
        }else{
            
            cout << "Current version:" << VERSION << endl;
            cout << "Read " << temp_string << endl;
            cout << "It might be incompatible: try anyway? 0 for yes, 1 for no ";
            int risp = 1;
            
            getInput( risp);
            
            if (risp!=0)
                return -1;
        }
        
        getline(path,temp_string);
        gnuplotOpen = temp_string;
        getline(path,temp_string);
        gnuplotSetTerminalPlot = temp_string;
        getline(path,temp_string);
        gnuplotSetTerminalSave_eps = temp_string;
        getline(path,temp_string);
        gnuplotSetTerminalSave_png = temp_string;
        getline(path,temp_string);
        gnuplotSetTerminalSave_gif = temp_string;
        getline(path,temp_string);
        MATLAB_loc = temp_string;
        getline(path,temp_string);
        MATLAB_call = temp_string;
        getline(path,temp_string);
        version_MATLAB = temp_string;
        getline(path,temp_string);
        apngas_lunch = temp_string;
        getline(path,temp_string);
        apngas_opt = temp_string;
        getline(path,temp_string);
        try{
            no_apngams = std::stoi(temp_string.c_str());
        }catch(std::invalid_argument&){
            cout << "Error getting value for no_apngasm" << endl;
            no_apngams = true;
        }
        
        path.close();
        
    }
    

    
    return 0;
}

int save_path(string versione_MATLAB){
    
    ofstream path(EcoliPath.c_str());
    
    if (!path.is_open()) {
        cout << "Error ... \n";
        cout << "Error saving the path data to a file ...\n";
        writeLog("ERROR", "Error saving the path data to a file.");
        return 1;
    }
    
    path << "#"  << VERSION << endl;
    
    path << gnuplotOpen << endl;
    path << gnuplotSetTerminalPlot << endl;
    path << gnuplotSetTerminalSave_eps << endl;
    path << gnuplotSetTerminalSave_png << endl;
    path << gnuplotSetTerminalSave_gif << endl;
    
    path << MATLAB_loc << endl;
    path << MATLAB_call << endl;
    path << versione_MATLAB << endl;
    
    path << apngas_lunch << endl;
    path << apngas_opt << endl;
    path << no_apngams << endl;
    
//    path << "#############################\n";
//    path << "#"  << VERSION << endl;
//    path << colors << endl;
    path.close();
    
    return 0;
}

void pritn_path(string versione_MATLAB){
    
    cout << BOLDBLUE << "*****************************************\n"
                     << "    Number cores in use:\n"
                     <<"*****************************************"<<endl<<RESET;
    cout << "n. cores in use: " << n_thread_available << endl << endl;
    cout << BOLDBLUE << "********************\n     gnuplot:\n********************"<<endl<<BOLDRED;
    cout <<"open\n";
    cout << RESET << gnuplotOpen << endl;
    cout << BOLDRED << "set terminal visualization\n";
    cout << RESET << gnuplotSetTerminalPlot << endl;
    cout << BOLDRED << "set terminal save .eps\n";
    cout << RESET << gnuplotSetTerminalSave_eps << endl;
    cout << BOLDRED << "set terminal save .png\n";
    cout << RESET << gnuplotSetTerminalSave_png << endl;
    cout << BOLDRED << "set terminal save .gif\n";
    cout << RESET << gnuplotSetTerminalSave_gif << endl;
    cout << BOLDBLUE << "\n********************\n     MATLAB:\n********************"<<endl<<BOLDRED;
    cout <<"open\n";
    cout << RESET << MATLAB_loc << versione_MATLAB << MATLAB_call << endl;
    cout << BOLDBLUE << "\n********************\n     APNGAS:\n********************"<<endl<<BOLDRED;
    cout << "open\n";
    cout << RESET << apngas_lunch << endl;
    cout << BOLDRED << "options\n";
    cout << RESET << apngas_opt << endl;
    string str = (no_apngams==true)?"false":"true";
    cout << "Fim create with apngams: " << str << endl;
    cout << BOLDBLUE << "\n********************\n .png .gif READER:\n********************"<<endl<<BOLDRED;
    cout << "Command to visualize .png/.gif format: " << RESET << firefox_path << endl;
    cout << BOLDBLUE << "\n**********************************************\n  BASE FOLDER FOR SAVINGS:\n**********************************************"<<endl<<BOLDRED;
    cout << "Location folder where saved data and summary\n";
    cout << RESET << Location << endl;
    
}

int save_risposte(){
    
    int risp = 0;
    
    cout << "The name of the file is EcoliRisposte.Ecoli" << endl
         << "Do you want to change it? \npress 0 for yes, 1 for no ";
    
    // Controllo che il tipo sia giusto
    getInput( risp);
    
    string nameFile = "EcoliRisposte.Ecoli";
    
    if (risp==0) {
        cout << "Enter the file name:\ndo not specify any extention for the file: " << endl;
        cout << "file name: ";
        cin >> nameFile;
        nameFile+=".Ecoli";
    }
    
    
//    cout << "insert the name of the file: ";
//    cin >> nameFile;
    
    ofstream EcoliRisp(nameFile.c_str());
    
    if (!EcoliRisp.is_open()) {
        cout << "Error ... \n";
        return 1;
    }
    
    EcoliRisp << "#" << VERSION << endl;
    
    for (int i=0; i<contatore_risposte; i++) {
        try{
            EcoliRisp << "#" << vettore_text[i] << endl;
        }catch(const std::out_of_range& oor){
            EcoliRisp << "#";
        }
        EcoliRisp << vettore_risposte[i] << endl;
    }
    
    EcoliRisp << "end";
    
    EcoliRisp.close();
    
    return 0;
}
