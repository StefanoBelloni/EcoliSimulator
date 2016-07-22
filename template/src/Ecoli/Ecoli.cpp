//
//  Ecoli.cpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 18/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include <iostream>

#include "Ecoli.hpp"

template <std::size_t dimS>
std::string ecoli::Ecoli<dimS>::ecoliToString(int model){

//    std::string dim;
//    std::stringstream strstream;
//    strstream << dimS;
//    strstream >> dim;

    switch (model)
    {
    case ecoli::E_COLI_MODEL:
        return "Ecoli-base";
        break;

    default:
        return "Ecoli-base";
        break;
    }


}


/** @brief this function update the subordinator.
  *
  * This virtual function, along with the InternalDynamic class, is the heart of this implementation of Ecoli experiments:
  * with this function we can decide what kind of distribution (in combination with the method update barrier in Subordinator) the run or tumble have.
  * We implement this function ouside the class Subordinator, since we need to gather the information from all over the variables in the Ecoli,
  * class in oder to perform this update.
  * \param dt time step.
  */
template <std::size_t dimS>
void ecoli::Ecoli<dimS>::updateSubordiantor(const double& dt)
{
    // classe base, avanzo mediamente
    // TODO:
    subordinator->lambda[tumble_phase]+=(subordinator->dLambda->tau_mean[tumble_phase])*dt;
}

/** @brief This function update the bactarium in all its aspects.
  *
  * This function do all the 'routine job', in the sense that it calls in sequence the right methods,
  * which are implemented in the different classes.
  * The chain is very easy:
  *     - 1 update the position, and check for the boundaries, update the internal dynamics and afterwords the subordinator
  *     - 2 check if the subordiantor hit the threshold
  *     - 3 it deals with the transition, if any, between run and tumble (and viceversa) ...
  */
template <std::size_t dimS>
void ecoli::Ecoli<dimS>::updateEcoli(const double& t, const double& dt)
{

    bool borderBounce = pos_lig->upDatePositionLigand(t,dt);

    intDyn->updateIntDyn(dt);
    updateSubordiantor(dt);

    //*************
    // NOTE on: (borderBounce && !tumble_phase)
    // in general if I'm tumbling I should not be hitting a boundary, but if I allow the possibility
    // that in a particular implementation the speed during a tumble is not 0, then it may happen that
    // I hit the boundary while tumbling !

//    if(subordinator->checkSubordinator[tumble_phase]() || (borderBounce && !tumble_phase) ){

    if((subordinator ->* (subordinator->checkSubordinator)[tumble_phase])() || borderBounce ){
        // if I begin a tumble, I tumble!
        // TODO: ...

        if (!tumble_phase)
            (pos_lig->theta .* (pos_lig->theta.newTheta))();

        (this ->* saveJump[tumble_phase])(t,dt,(subordinator ->* (subordinator->updateThreshold)[tumble_phase])(t));
        // switch phase
        tumble_phase=!tumble_phase;

    }

    std::cout << "updateEcoli finished\n*****************************************" << std::endl;

}

/** @brief Constructor, passing dimaension of the space and if we want to change the parameters
  *
  * We construct an instance of an Ecoli object.
  * @param p_dim dimention of the space (defoult is 2)
  * @param change_par variable to indicate if we want to change the parameters of the model. (defoult is false)
  * @param agentbase implement the agent base model (defoult is true)
  * @param contModel implement the continuous model (defoult is false)
  * @param ligand_ptr it is the pointer to the enviroment. We might pass it immediatly when constructing the bacterium or use the function setEnviroment
  */
  template <std::size_t dimS>
 ecoli::Ecoli<dimS>::Ecoli(bool change_par/*, bool agentbase, bool contModel*/,std::size_t n_batterio, ecoli::Enviroment<dimS>* ligand_ptr)
{

    this->num_bat = n_batterio;
    this->model = ecoli::E_COLI_MODEL;
    this->dim = dimS;
    this->tumble_phase = false;

    // SET SAVE RUN AND TUMBLE FUNCTION
    saveJump[0] = &Ecoli::saveRun;
    saveJump[1] = &Ecoli::saveTumble;

    // TODO: set the file where to save the data.

    // AGENT BASE MODEL:
    subordinator = new TimeChange(&(this->tumble_phase));
    pos_lig = new LocomotionLigand<dimS>(change_par, ligand_ptr);
    intDyn = new InternalModel<dimS>(change_par,pos_lig);
    implementedAgentModel = true;

    // CONTINUOUS TIME MODEL:
    // TODO: la classe internal model ...

    implementedContModel = true;

    //TODO: initialize
    // tumble_phase
    // saveJump

}



/** @brief (one liner)
  *
  * (documentation goes here)
  */

template <std::size_t dimS>
 ecoli::Ecoli<dimS>::~Ecoli()
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Ecoli<dimS>::setParameters(){
    std::cout<< "Ecoli in space dimantion " <<  this->dim << std::endl;
    std::cout<< "Set the parameters of the Ecoli: " <<  ecoliToString(this->model) << std::endl;
}

/** \brief set the enviroment reference
 *
 * We might want to be able to change the enviroemnt reference after the creation of the defoult bacterium,
 * an example might be when we want to perform for a specific bacterium more experiment in differen scenarios.
 *
 * \param ligand_ptr pointer to the current envirment
 *
 */

template <std::size_t dimS>
void ecoli::Ecoli<dimS>::setEnviroment(ecoli::Enviroment<dimS>* ligand_ptr){
    this->pos_lig->setLigand(ligand_ptr);
}

/** \brief
 *
 */
template <std::size_t dimS>
void ecoli::Ecoli<dimS>::saveRun(double const t, double const dt, double const tau)
{
    // TODO:
}

/** \brief
 *
 */
template <std::size_t dimS>
void ecoli::Ecoli<dimS>::saveTumble(double const t, double const dt, double const tau)
{
//    TODO:
}



//********************************************************
//
//********************************************************

template class ecoli::Ecoli<1>;
template class ecoli::Ecoli<2>;
template class ecoli::Ecoli<3>;
