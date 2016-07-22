//
//  Direction.cpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 17/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include <iostream>

#include "Direction.hpp"
#include "DefoultQuantity.h"


// BOOST LIBRARY INCLUDE

#include "boost/random/uniform_on_sphere.hpp"


// This constructor is inglobated inside the one with boolean argument
//*! @brief defoult constructor
//
// * The dimention of the space is set equal to 2, the other quantities are set as in DefoultDirection.
// * We might want to eliminate it and use anly the explicit constructor with defoult parameters
//*/
//template <std::size_t dimS>
//ecoli::Direction<dimS>::Direction(){
//
//    dim = DefoultDirection::dim;
//    D_theta = DefoultDirection::D_theta;
//    D_theta_tumble = DefoultDirection::D_theta_tumble;
//
////    angle.resize(dim-1);
////    theta.resize(dim);
//
//    setNewTheta(DefoultDirection::defoultFunctions);
//    setDiffTheta(DefoultDirection::defoultFunctions,DefoultDirection::defoultFunctions);
//
//}


/*! This constructor set the dimension of the space and all the other variables as defoults is change par is false
 * otherwise it allows the uso chose a function (depending on p_dim)
 */

template <std::size_t dimS>
ecoli::Direction<dimS>::Direction(const bool change_par){

    std::cout << "Direction<" << dimS << ">::Direction" << std::endl;

    if (change_par){
        menuSetTheta();
    }else{
        D_theta = DefoultDirection::D_theta;
        D_theta_tumble = DefoultDirection::D_theta_tumble;
        setNewTheta(DefoultDirection::defoultFunctions);
        setDiffTheta(DefoultDirection::defoultFunctions,DefoultDirection::defoultFunctions);
    }

}

/** @brief Copy-constructor
  *
  * We use this constructor to construct an object direction equal to the one passed.
  * This will be used in the case we have a large population, all with identical characteristics,
  * and we simulate the entair population simultoniously and not only one rappesentative (i.e. in the intercating case).
  * @param directionRef reference direction
  */
template <std::size_t dimS>
ecoli::Direction<dimS>::Direction(const Direction& directionRef):
     angle(directionRef.angle), D_theta(directionRef.D_theta),
     dim(directionRef.dim), tipoNewTheta(directionRef.tipoNewTheta),
     theta(directionRef.theta),paramNewTheta(directionRef.paramNewTheta),
     D_theta_tumble(directionRef.D_theta_tumble)
{
    // Esplicito il riferimento dei puntatori
//    tipoDiffTheta[0] = directionRef.tipoDiffTheta[0];
//    tipoDiffTheta[1] = directionRef.tipoDiffTheta[1];
//    setNewTheta(tipoNewTheta);
//    setDiffTheta(tipoDiffTheta[0],tipoDiffTheta[1]);

    // potrebbe essere sufficiente

    newTheta = directionRef.newTheta;
    diffTheta[0] = directionRef.diffTheta[0];

}

/** @brief distructor
  *
  */
template <std::size_t dimS>
ecoli::Direction<dimS>::~Direction()
{
    delete this;
}



/*! This function set the function pointer to the function whose type is tipoNewTheta.
 *  @param tipoNewTheta
 */
template <std::size_t dimS>
void ecoli::Direction<dimS>::setNewTheta(const int tipoNewTheta_par){

    tipoNewTheta = tipoNewTheta_par;

    switch (tipoNewTheta_par) {

        case FunctionUpdateTheta::NEW_THETA_1D:
            newTheta = &Direction::newTheta1D;
            break;

        case FunctionUpdateTheta::NEW_THETA_2D_UNIFORM :
            newTheta = &Direction::newTheta2DUnif;
            break;

        default:

            if (dim==1) {
                newTheta = &Direction::newTheta1D;
            }else if (dim ==2){
                newTheta = &Direction::newTheta2DGamma;
            }

            // TODO: 3rd dimension ...

            break;
    }

}

/*! @brief This function set the function pointer to the function whose type is tipoDiffTheta: it is a two dimensional array.
 *
 *   We set the function pointer to be used during the update of the direction due to the diffusive component.
 *
 *  @param tipoDiffThetaRun type of diffusion during a run
 *  @param tipoDiffThetaTumble type of diffusion during a tumble
 */
 template <std::size_t dimS>
void ecoli::Direction<dimS>::setDiffTheta(const int tipoDiffThetaRun, const int tipoDiffThetaTumble){

//     I will save whatever value I pass. The assigment will make the trick...

    tipoDiffTheta[0]=tipoDiffThetaRun;
    tipoDiffTheta[1]=tipoDiffThetaTumble;

    switch (tipoDiffThetaRun) {
        case FunctionUpdateTheta::DIFF_THETA_2D:
            diffTheta[0] = &Direction::diffTheta2D;
            break;

        case FunctionUpdateTheta::DIFF_THETA_3D:
            diffTheta[0] = &Direction::diffTheta3D;
            break;

        default:

            if (dim==1) {
                diffTheta[0] = &Direction::noRotationalDiff;
            }else if (dim ==2){
                diffTheta[0] = &Direction::diffTheta2D;
            }else{
                diffTheta[0] = &Direction::diffTheta3D;
            }

            break;
    }

    switch (tipoDiffThetaTumble) {
        case FunctionUpdateTheta::DIFF_THETA_2D:
            diffTheta[1] = &Direction::diffTheta2D;
            break;

        case FunctionUpdateTheta::DIFF_THETA_3D:
            diffTheta[1] = &Direction::diffTheta3D;
            break;

        default:
            diffTheta[1] = &Direction::noRotationalDiff;
            break;
    }

}

/** @brief new Theta doen't not jump
  *
  * It does not do anything
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::newThetaNoJump(){}

/** @brief new Theta in 1D
  *
  * We simply invert the direction.
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::newTheta1D()
{
    theta[0]*= -1;
}

/** @brief the new theta is uniformly distributed on the unit sphere
  *
  * we might want to
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::newTheta2DUnif()
{
    // TODO:
    theta;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::newTheta2DGamma()
{
    //TODO:

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::newTheta2DGammaPar()
{
    //TODO:
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::noRotationalDiff(const double& dt)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::diffTheta2D(const double& dt)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::diffTheta3D(const double& dt)
{

}

/** @brief function to 'display the menu' for the selection of the functions related to theta
  *
  * We use this function to set the functions about the jump of theta, its diffusivity behaviour during a run or a tumble.
  */
  template <std::size_t dimS>
void ecoli::Direction<dimS>::menuSetTheta()
// we have to initialize all the different parameters ...
{

}


/*
 * Specific constructor for the dimention 1
 *
 */

template<>
ecoli::Direction<1>::Direction(){

    dim = 1;
    setNewTheta(FunctionUpdateTheta::NEW_THETA_1D);

}

template<>
ecoli::Direction<1>::Direction(const bool change_par){

    dim = 1;
    setNewTheta(FunctionUpdateTheta::NEW_THETA_1D);

}

template<>
ecoli::Direction<1>::Direction(const Direction& directionRef)
{
    dim = 1;
    setNewTheta(FunctionUpdateTheta::NEW_THETA_1D);
}

//***********************************************************************************
//
//***********************************************************************************

template class ecoli::Direction<1>;
template class ecoli::Direction<2>;
template class ecoli::Direction<3>;
