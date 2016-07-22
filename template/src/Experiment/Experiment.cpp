#include "Experiment.h"

#include <iostream>

//template <std::size_t dimS>
//Experiment<dimS>::Experiment()
//    : env(), um()
//{
////    this->setExperiment();
//    std::cout << "***************************************************" << std::endl;
//    std::cout << "Experiment constructed: " << std::endl;
//
//}


template <std::size_t dimS>
Experiment<dimS>::Experiment(bool setEnv)
    : env(), um()
{
//    this->setExperiment();
    std::cout << "***************************************************" << std::endl;
    std::cout << "Experiment constructed: " << std::endl;
    if (setEnv){
        this->setExperiment();
    }

}

template <std::size_t dimS>
Experiment<dimS>::~Experiment()
{
    //dtor
}

/** \brief This function is used to set the experiment.
 *
 *
 */

template <std::size_t dimS>
void Experiment<dimS>::setExperiment(){
    // To perform an experiment, we need to set

    // 1- set Unit measured
    um.setUnitMeasure();
    // 2- the enviroment:
    env.setEnviroemnt();
    // 3- set the initial conditions
    ic->setInitialCondition();
    // 4 - set the simulations
    this->setSimulations();

}

template <std::size_t dimS>
void Experiment<dimS>::setSimulations(){

    std::cout << "set the Simulations" << std::endl;

}


//***************************************************
//
//***************************************************

template class Experiment<1>;
template class Experiment<2>;
template class Experiment<3>;
