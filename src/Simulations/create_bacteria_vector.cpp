//
//  create_bacteria_vector.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//************************************************************************************
//           TIPI MODELLI STOCASTICI E RELATIVO NUMERO IDENTIFICATIVO
//************************************************************************************
/*
 * 0 -> E_coli     
 *
 * 1 -> CV_rExp_t_Exp
 * 2 -> CV_rIG_t_Exp
 * 3 -> CV_rExpIG_t_Exp
 * 
 * 4 -> Molecular_rExp_t_Exp
 * 5 -> Molecular_rIG_t_Exp
 * 6 -> Molecular_rExpIG_t_Exp
 *
 * 7 -> EOth_rExp_t_Exp
 * 8 -> EOth_rIG_t_Exp
 * 9 -> EOth_rExpIG_t_Exp
 *
 */

//************************************************************************************


#include <iostream>
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "CV_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "EO_rExp_tExp.h"
#include "EO_rIG_tExp.h"
#include "EO_rExpIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Molecular_rIG_tExp.h"
#include "Molecular_rExpIG_tExp.h"

#include <vector>

#include "Colori.h"
#include "sssr.h"

using namespace std;

void funz_clear();
void timestamp ( );
void setParametersModelBacteriumInteracting(E_coli* batterio, int cont_gen_sim);
int writeLog(string what, string msg);
/**
 * This file has to be modified if you add a new model: the local variable n_sim keep the number of all model. You have to update it
 * set the model/s you want to simulate.
 * @param which_compare vector of the model to compare
 * @param statisticita = 1, statistical fitting, else simulation
 * @return number of simulation to perform with the "same envarioment setting" (func c, initial position and so on)
 */

int Set_Stocasticita(vector<int> &which_compare ,int statisticita){
    
    int tipo_simulazione=1;             // Quale stocasticità si vuole (exponential inverse gaussian etc.)
    //int compare=0;
    int compare_noch=0;
    
    // NUMBER MODEL TO BE MODIFIED IF ADD NEW MODELS ...
    int n_sim=9;
    
    funz_clear();
    
    //       TIPO STOCASTICITÀ SIMULAZIONE (InvGaus, Exp, Molec, Comparison
    
    cout << BOLDRED << "--------------------------------------------------" <<endl
    << "-               Ecoli - Program.                 -"   << endl;
    if (statisticita==1) {
        cout << "-             STATISTICAL FITTING               -" << endl;
    }
    cout << "--------------------------------------------------\n\n" << RESET <<endl;
    
    if (statisticita==1) {
        cout << BOLDBLUE << "Which kind of Model do you want to fit ? "<< endl;
    }else{
        cout << BOLDBLUE << "Which kind of Model do you want to simulate ? "<< endl;}
    cout << BOLDBLACK << "\n1 - Celani Vergassona Exponential Approach" << endl
    << "2 - CV Inverse_Gaussian Approach" << endl;
        if (statisticita!=1) {
            cout << "3 - CV Exponential_Inverse_Gaussian Approach" << endl
            << BOLDYELLOW << "4 - Molecular_rExp_tExp level Implementation" << endl
            << "5 - Molecular_rIG_tExp level Implementation " << endl
            << "6 - Molecular_rIG_tExp level Implementation" << endl
            << BOLDRED << "7 - Othmer Exponential distribution Approach" << endl
            << "8 - Othmer Inverse_Gaussian Approach" << endl
            << "9 - Othmer Exponential_Inverse_Gaussia Approach" << endl;
        }
    cout << BOLDBLUE<< "\n0 - Comparison between different approaches ... " << RESET << endl;
    
    
    cout << RESET << endl;
    
    sssr(tipo_simulazione,"Which kind of Model do you want to simulate");
    compare_noch=1;
    
    which_compare.resize(0);
    
    // if 0 compare
    
    
    if(tipo_simulazione!=0) {  // if I don't compare I save une model to simulate. If outside range, I set default E_coli base class.
        if (tipo_simulazione>n_sim || tipo_simulazione<0 ) {tipo_simulazione=0;}
        which_compare.push_back(tipo_simulazione);
    }else{
        
        //compare=1;
        
        cout << "Insert the simulation that do you want to compare. 0 to finish insert simulations ... " << endl;
        sssr(compare_noch,"Insert the simulation that do you want to compare. 0 to finish insert simulations");
        
        while(compare_noch!=0){  
            
            which_compare.push_back(compare_noch);
            cout << "Insert the simulation that do you want to compare. 0 to finish insert simulations ... " << endl;
            sssr(compare_noch,"Insert the simulation that do you want to compare. 0 to finish insert simulations");
            
        }
    }
    
    return (int)which_compare.size();
}


/**
 * for the non  population interacting with the ligand it is enough one rappresentant.
 * This file has to be modified if you add a new model add the right index as in int Set_Stocasticita(vector<int> &which_compare ,int statisticita)
 */

void create_bacteria_vector(vector<E_coli*> &batteri){

    batteri.push_back(new E_coli);                  // 0  [x]
    batteri.push_back(new CV_rExp_tExp);            // 1  [x]
    batteri.push_back(new CV_rIG_tExp);             // 2  [x]
    batteri.push_back(new CV_rExp_tExp);            // 3  [x]
    batteri.push_back(new Molecular_rExp_tExp);     // 4  [x]
    batteri.push_back(new Molecular_rIG_tExp);      // 5  [x]
    batteri.push_back(new Molecular_rExpIG_tExp);   // 6  [.]
    batteri.push_back(new EO_rExp_tExp);            // 7  [x]
    batteri.push_back(new EO_rIG_tExp);             // 8  [x]
    batteri.push_back(new EO_rExpIG_tExp);             // 9  [x]
    
}

/**
 * This file has to be modified if you add a new model like in void create_bacteria_vector(vector<E_coli*> &batteri)
 * but we have to create a vector of number of population bacteria, since they interact with each other.
 * Note that they have all defaoult parameters, a part from the production rate a static variable for E_coli class
 * @param tipo_simulazione: model
 * @param batteri_int pointer to the population of bacteria
 * @param n_c number bacteria
 */

void initialization_interacting_population(int tipo_simulazione, vector<E_coli* > *batteri_int, int n_c, int cont_gen_sim){
    
    double _production_rate = 10;
    cout << "Insert the rate of production of Ligand of a bacterium (default value 10.0) " << endl;
    sssr(_production_rate,"Insert the rate of production of Ligand of a bacterium (default value 10.0)");

    
    // BATTERIO BASE
    // I create a base bacterium, modify the parameters and then use the copy constructor.
    
    
    
    switch (tipo_simulazione) {
        
            // SET PARAMETERS:
            
        //*******************************************
        //  CV
        //*******************************************            
            
        {
        case 1:
            
            CV_rIG_tExp* batterio = new CV_rIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);
            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new CV_rExp_tExp(*batterio));
            }
            
            break;                        
        }
        {
        case 2:
            
            CV_rIG_tExp* batterio = new CV_rIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new CV_rIG_tExp(*batterio));
            }
            
            break;                        
        }
        {
        case 3:
            
            CV_rExpIG_tExp* batterio = new CV_rExpIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new CV_rExpIG_tExp(*batterio));
            }
            
            break;                        
        }
           
        //*******************************************
        //  MOLECULAR            
        //*******************************************            
            
        {
        case 4:
            
            Molecular_rExp_tExp* batterio = new Molecular_rExp_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new Molecular_rExp_tExp(*batterio));
            }
            
            break;                        
        }
        {
        case 5:
            
            Molecular_rIG_tExp* batterio = new Molecular_rIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new Molecular_rIG_tExp(*batterio));
            }
            
            break;                        
        }
        {
        case 6:
            
            Molecular_rExpIG_tExp* batterio = new Molecular_rExpIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new Molecular_rExpIG_tExp(*batterio));
            }
            
            break;                        
        }
            
        //*******************************************
        //  EO            
        //*******************************************            
            
        {
        case 7:
            
            EO_rExp_tExp* batterio = new EO_rExp_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new EO_rExp_tExp(*batterio));
            }
            
            break;                        
        }
        {
        case 8:
            
            EO_rIG_tExp* batterio = new EO_rIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new EO_rIG_tExp(*batterio));
            }
            
            break;                        
        }
        {
        case 9:
            
            EO_rExpIG_tExp* batterio = new EO_rExpIG_tExp();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new EO_rExpIG_tExp(*batterio));
            }
            
            break;                        
        }
            
            //*******************************************
            //******************************************* 
            
        {
        default:
            
            E_coli* batterio = new E_coli();
            setParametersModelBacteriumInteracting(batterio,cont_gen_sim);

            
            cout << "Error, it will be simulated a E_coli default bacterium. "<<endl;
            
            
            string msg("Error opening the file: ");
//            msg+=name_script_baricenter;
            writeLog("ERROR","Error identifying the class E.coli, default bacterium simulated");
            
            for (int i=0; i<n_c; i++) {
                //                            cout << i << "Building Interacting vector ... " <<endl;
                (*batteri_int).push_back(new E_coli(*batterio));
            }
            
            break;
        }
    }
    
    (*batteri_int)[0]->setProductionRate(_production_rate);
    
}


// This function set allow to set the parameter

void setParametersModelBacteriumInteracting(E_coli* batterio, int cont_gen_sim){

    int change_parameters;
    //    int risposta;
    // Parameter setting
    if (batterio->simulation!=1) {
        batterio->reset_par();
    }


    funz_clear();
    std::cout << "simulation number " << cont_gen_sim << endl;
    cout << "\n****************************************\n";
    timestamp();
    cout << "Type bacterium: "<< batterio->Tipo_batterio << endl;

    if (batterio->simulation==0) {
        
        cout << "\nDo you want to change the parameters?"<< endl
        << "0 to use the default" << endl
        //         << "1 setting of the previous simulation" << endl
        //         << "2 take file from a file" << endl
             << "1 edit manually parameters" << endl;
        
        sssr(change_parameters,"Do you want to change the parameters?");
        batterio->change_par(change_parameters);
    }
    
}

