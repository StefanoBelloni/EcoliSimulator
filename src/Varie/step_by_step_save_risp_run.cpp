//
//  step_by_step_save_risp_run.cpp
//  Ecoli_3.1.1
//
//  Created by Stefano Belloni on 25/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "GlobalVariables.h"
#include "Colori.h"
#include "Declar_funz.h"
#include <limits>
#include <ctime>

using std::string;
using std::cout;
using std::cin;
using std::endl;


/** This function deals with the expected imput
 * if we have to wait for the user, wait and save in vettore_risposte, or we just read from vettore_risposte
 * It also check if the imput is of the desired type or not.
 * @param value to be return to set it after the imput.
 */
void sssr(int &valore, string text){
    
    if (automatic_!=2) {
//        cin >> valore;
        
        
        // Controllo che il tipo sia giusto
        getInput( valore);
        
        if (automatic_==1) {
            vettore_risposte.push_back(valore);
            vettore_text.push_back(text);
            contatore_risposte++;
        }
    }else {
        valore = vettore_risposte[contatore_risposte];
        std::cout << BOLDGREEN <<  valore << endl << RESET;
//        std::cout << "press Enter to continue ";
//        cin.ignore();
        contatore_risposte++;
    }
   
}

/** This function deals with the expected imput
 * if we have to wait for the user, wait and save in vettore_risposte, or we just read from vettore_risposte
 * It also check if the imput is of the desired type or not.
 * Same function as before , but when we expect a double
 * @param value to be return to set it after the imput.
 */

void sssr(double &valore, string text){
    
    if (automatic_!=2) {
//        cin >> valore;
        
        // Controllo che il tipo sia giusto        
        getInput( valore);
        
        if (automatic_==1) {
            vettore_risposte.push_back(valore);
            vettore_text.push_back(text);
            contatore_risposte++;
        }
    }else {
        valore = vettore_risposte[contatore_risposte];        
        std::cout << BOLDGREEN <<  valore << endl << RESET;
//        std::cout << "press Enter to continue ";
//        cin.ignore();
        contatore_risposte++;
    }
    
}
