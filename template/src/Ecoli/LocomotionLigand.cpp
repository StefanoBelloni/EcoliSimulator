//
//  Locomotion.cpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 17/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "LocomotionLigand.hpp"

//NOTE: we might pass the enviroment

template<std::size_t dimS>
ecoli::LocomotionLigand<dimS>::LocomotionLigand(bool changePar, ecoli::Enviroment<dimS>* ligand_ptr) : theta(changePar)
{

}


/** @brief update the ligand, i.e. update the \e solution of the ligand and its value felt by the bacterium.
  *
  */
template<std::size_t dimS>
void ecoli::LocomotionLigand<dimS>::updateLigand(const double& t, const double& dt)
{

}

/** @brief function that check if a bacterium reached the boundary
  *
  */

template <std::size_t dimS>
template <typename BoundaryCondition>
bool ecoli::LocomotionLigand<dimS>::checkBoundary(BoundaryCondition BC)
{

}

/** @brief this function update the position and the ligand
  *
  */
  template<std::size_t dimS>
bool ecoli::LocomotionLigand<dimS>::upDatePositionLigand(const double& t, const double& dt)
{

}


/** @brief set the reference to the enviroemnt
  *
  */
template<std::size_t dimS>
void ecoli::LocomotionLigand<dimS>::setLigand(ecoli::Enviroment<dimS>* ligand_ptr){
    ligand = ligand_ptr;
}


/** @brief set the reference to the enviroemnt
  *
  */

template<std::size_t dimS>
void ecoli::LocomotionLigand<dimS>::updateXTheta(const double dt){
    // update XTheta in caso 1,2,3D.
}

/*
 * SPECIFICATION DIMENTION 1
 */

template<>
void ecoli::LocomotionLigand<1>::updateXTheta(const double dt){
    // update XTheta in caso 1D.
}


//***********************************************************************************
//
//***********************************************************************************

template class ecoli::LocomotionLigand<1>;
template class ecoli::LocomotionLigand<2>;
template class ecoli::LocomotionLigand<3>;
