//
//  TimeChange.cpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 18/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "TimeChange.hpp"
#include <iostream>

//**************************************************************************************
/*!
 * Constructor: it is also the default one.
 */

ecoli::TimeChange::TimeChange(bool* tumble_phase_par, bool change_param, int tipo_r, int tipo_t){

    std::cout << "TimeChange::TimeChange" << std::endl;

    this->tumble_phase = tumble_phase_par;
    this->param_changed = change_param;
    setParemeters(tipo_r,tipo_t);

}
//**************************************************************************************

/**
  *
  */
void ecoli::TimeChange::setParemeters(int tipo_r, int tipo_t)
{
    // Last tumble/run. we could also just do it when start a Simulation ...
    t_last[0]=0.0; t_last[0]=0.0;
    // set treshhold
    setTypeThreshold(tipo_r,tipo_t);
    // Initialization of the response function dLambda
    //TODO:
    dLambda = new Lambda();
    // set Type threshold check
    setCheckSubordinator(FunctionsTimeChange::SIMPLE_CROSS,FunctionsTimeChange::SIMPLE_CROSS);


}
//**************************************************************************************

/**
  *
  */
void ecoli::TimeChange::setTypeThreshold(int tipo_r, int tipo_t){

    // I do a loop on the tipo_...
    int tipo = tipo_r;
    int i=0;
    do{
        switch(tipo){
            case ecoli::FunctionsTimeChange::DET_JUMP:
            // TODO:
            // type of assagment
            // updateThreshold[i] = &'name of the function';
                break;

            case ecoli::FunctionsTimeChange::PARETO_DIST:
            // TODO:
                break;

            default:
            // TODO: here come the exponential distribution, i.e. ecoli::FunctionsTimeChange::PARETO_DIST
                break;

        }
    i++;
    tipo = tipo_t;
    }while(i==2);

}

void ecoli::TimeChange::setCheckSubordinator(const int tipoCheck_r, const int tipoCheck_t){

    std::cout << "ecoli::TimeChange::setCheckSubordinator" << std::endl;

    int tipo = tipoCheck_r;
    int i=0;
    do{
        switch(tipo){

            default:
                checkSubordinator[i]=&TimeChange::simpleCross;
                break;

        }
    i++;
    tipo = tipoCheck_t;
    }while(i==2);


}
