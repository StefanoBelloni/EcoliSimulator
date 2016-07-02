//
//  read_file_par.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 08/10/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <string>
#include <fstream>
#include "GlobalVariables.h"
#include "ErrorsDefinition.h"
#include "Declar_funz.h"

#define DEMO 0

using std::string;

void funz_clear();
int writeLog(string what, string msg);

using std::cout;
using std::endl;
using std::cin;

int read_file_par(int demo_mode)
/* the parameters are save in a file called: file_parameters.txt
 * 
 */
{
    string stringa_vuota;
    string stringa_vuota1;    
    double risp;
    
    funz_clear();
    
    std::cout << "\n*****************************\n";
    std::cout << "   READING FILE OF PARAMETERS \n";
    std::cout << "*******************************\n";
    
    std::ifstream file_par;
    if (demo_mode == DEMO){
        file_par.open("EcoliRisposteDEMO.Ecoli");
    }
    else{
        file_par.open(fileEcoliRisp.c_str());
    }
    
    if (!file_par.is_open()) {
        std::cout << "Error opening the file\n";
        string msg("Error opening file: ");
        msg+=fileEcoliRisp;
        writeLog("ERROR",msg);
        return -1;
    }
    
    getline (file_par,stringa_vuota);
    string compare_str(VERSION);
    compare_str='#'+compare_str;
    if (stringa_vuota.compare(compare_str)==0){
        cout << VERSION << endl;
    }else{
        
        cout << "Current version:" << VERSION << endl;
        cout << "Read " << stringa_vuota << endl;
        cout << "It might be incompatible: try anyway? 0 for yes, 1 for no ";
        int risp = 1;

        getInput( risp);
        
        if (risp!=0)
            return -1;
    }
    
    while (file_par.good()) {
        getline (file_par,stringa_vuota);
//        getline (file_par,stringa_vuota1);
        vettore_text.push_back(stringa_vuota);
        
        if (stringa_vuota=="end") {
            cout << "--->\n";
            funz_clear();
            file_par.close();
            return 0;
        }
        
        if (stringa_vuota[0]!='#'){
        
        risp = atof(stringa_vuota.c_str());
        
//        cout << stringa_vuota << endl;
//        cout << risp << endl;
        
        vettore_risposte.push_back(risp);
//        contatore_risposte++;
        }
        
    }
    
    file_par.close();
    
    funz_clear();
    
    return 0;
}
