//
//  set_funz_c.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 28/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>

#include "sssr.h"
#include "Funz_C.h"
#include "GlobalVariables.h"
#include "Colori.h"

using namespace std;

void funz_clear();

/**
 * THis function set the parameters of the function c(x,t), preview tec.
 */

int set_funz_c(vector<Funz_C*> &f, int interacting){
    
    // interacting == 2 sono nella modalità particelle interagenti
    
    
    if (interacting==2) {
        
        f[2]->set_parameter();
        
        cout << "Insert the diffusion coefficient D: "<< endl 
        << "D=.001 mm2/s, which corresponds to the approximate diffusion coefficient of a small protein in solution" << endl;
        sssr(f[2]->D_c,"Insert the diffusion coefficient D");
        
    }else {
        int tipo_funz_c_class=0;
        int risposta=0;
        int risp_View=1;
        
        cout << "Do you want to try and visualize different Ligands landscapes ? \npress 0 for yes, 1 for no ";
        sssr(risp_View,"Do you want to try and visualize different Ligands landscapes");
        
        do{
            f[tipo_funz_c_class]->set_parameter();
        
        
            cout << "Do you want to change the parameters of the profile of the ligand concentration? \npress 0 for yes, 1 for no ";
            sssr(risposta,"Do you want to change the parameters of the profile of the ligand concentration?");
        
            if (risposta==0) {
                funz_clear();
                // I change the index in the array of possible f
                tipo_funz_c_class=1;
                f[tipo_funz_c_class]->set_parameter();
            }
            
            
            if (risp_View==0) {
                
                // Non è molto performante, ma almeno non devo cambiare ovunque ...
                if (automatic_==0) {
                    
                    f[tipo_funz_c_class]->preview_F_C();
                }
                
                funz_clear();
                
                cout << "Do you want to try with another set of parameters ? \npress 0 for yes, 1 for no ";
                sssr(risp_View,"Do you want to try with another set of parameters ? press 0 for yes, 1 for no ");
            }
            
        }while (risp_View==0);
        
        return tipo_funz_c_class;
    }    
    
    return 2;
}
