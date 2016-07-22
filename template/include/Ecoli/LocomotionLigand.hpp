//
//  Locomotion.hpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 17/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef Locomotion_hpp
#define Locomotion_hpp

#include <stdio.h>
#include <cstddef> // for std::size_t
#include <vector>
#include <array>
#include <map>

#include "Direction.hpp"
#include "Definitions.h"
#include "Enviroment.hpp"

namespace ecoli{

/*!
 * Collection of enumeration to identify the various functions to update the direction of the bacterium
 */
namespace FunctionUpdateX {

    /*!
     * \brief enumeration of the different type of functions that can be used as updateX.
     *
     * These are the functions used by the <em>pointer function</em>s Direction.newTheta_ptr and Direction.diffTheta_ptr to model reorientation and rotational diffusion.
     */

    enum TypeUpdateX{

    };

}

/*! \brief struct that deals with the update of the position of the bacterium.
 *
 * The bacterium follows a \e run and \e tumble random walk. During a run the bacterium swims in direction Direction.theta with a certain speed v. During a tumble there is only a reorientation of the bacterium's direction.<br>
 */

template <std::size_t dimS>
struct LocomotionLigand{

    //************************************************************************************************
    //*                                     VARIABLES
    //************************************************************************************************

    std::size_t dim;        //!< dimention of the physical space, in general 1,2 or 3
    std::vector<double> x;  //!< position of the bacterium

    /*! the fact that we use a vector and not a scalar allows to have anisotropic speed*/
    //NOTE: it might be influnced by the enviroment ... How to deal with it?
    std::vector<double> v;  //!< speed of the bacterium
    bool constSpeed;        //!< this variable is used to keep track if we want constant speed or a variable one.


    /*!It uses the definition in "Definition.h" for the right index to be used.*/
    std::size_t run_tumble; //!< variable that takes track whether we're performing a run or a tumble

    Direction<dimS> theta;        //!< direction of the bacterium

    ecoli::Enviroment<dimS>* ligand;  //!< pointer to the enviroment

    //NOTE: consider if its necessary this partition of mainLigand and the others ...

    std::vector<double> chemicalsMeasured;  //!< vector of the chemicals measured by the bacterium
    std::map<std::vector<int>,std::vector<double> > production_rates;  //!< map from the ID for the chemicals to the relative production rate
    std::map<std::vector<int>,std::vector<double> > consume_rates;     //!< map from the ID for the chemicals to the relative degradation rate


    //************************************************************************************************
    //*                                         METHODS
    //************************************************************************************************

    // CREATOR
    LocomotionLigand(bool changePar = false, ecoli::Enviroment<dimS>* ligand_ptr = NULL);

    // TODO: decide what is the best it should do:
    // how to implement different behaviour for run/tumble??
//    void updateLocomotion();         //!< this method update the position and ditaction of the bacterium.


    void setUpdateLocomotion();        //!< set the function to be used in the update: if we are in a run or in a tumble phase.

    void setLigand(ecoli::Enviroment<dimS>* ligand_ptr);

    virtual void updateLigand(const double &t, const double &dt);    //!< function that update the Ligand

    template <typename BoundaryCondition>
    bool checkBoundary(BoundaryCondition bc);       //!< function that chacke if I reach a boundary and update consequentily

    /*!
     * @return true if we bounced agains the boder, so that a 'forced' tumble will happened.
     */
    bool upDatePositionLigand(const double &t, const double &dt);    //!< this function update the position and the ligand


    typedef void (LocomotionLigand<dimS>::*updateX_ptr)(const double &dt); //!< this typedef update the position of the bacterium.

    /*The idea is to use it as "Locomotion.updateLocomotion[run_tumble_state](dt)".*/
    // in the constructor we have to initialize it!!!
    updateX_ptr updateX[2];    //!< We will have two possible update: <em>run and tumble</em>, risp index 0 and 1.

    /*The implementation should be something like:
     remember that (this->*func)(variables)

        this->(*updateX[run_tumble])(dt);
        this.(* diffTheta_ptr)(dt)

     */
    typedef void (LocomotionLigand<dimS>::*updateXtheta_ptr)(const double &dt); //!< typedef for pointer function to update the position and direction.

    /*! It updates the position and the direction during a <em>run or a tumble</em>.
     - we might want not to be using an abrupt jump in the direction at a tumble, but a smoother process during the all tumbling event. In this case we have to implement Direction.diffTheta properly.
     - it is defined as a pointer function, so that if during a tumble nothing has to be update, we can simply set is as if(run_tumble=='tumble')return;
     */

    updateXtheta_ptr updateXtheta; //!< function pointer to update for the position and direction.

    //************************************************************************************************

    //*********************************************
    // updateXTheta...(const double dt) functions
    //*********************************************

    void updateXTheta(const double dt);



    //************************************************************************************************

    //*********************************************
    // updateX...(const double dt) functions
    //*********************************************

};

}

#endif /* Locomotion_hpp */


//************************************************************************************************
//                          IMPLEMENTATION COMMENTS & SIMILAR TOPICS ...
//************************************************************************************************


/*
 * The different form of the update is managed with the help of <b> pointer functions </b>.
 */

/* NOTE: IDEA TO AVOID CHECKING BOUNDARY AT EVERY ITERATION:
 * 1- suppose we start in x;
 * 2- I can build the maximal circonference that is ompletly contained in the domain,let R be its radius;
 * 3- Let v_m be the maximal speed that the bacterium can reach, then I can evaluate the minimum time the bacterium is going to be inside this sphere, say T_R;
 * 4- let ii_boundary = floor(T_R/dt).
 * 5- at every iteration ii_boundary--,till it reaches the level or a fixed value II_BOUNDARY_MIN.
 * 6- "If ii_boundary is really small, I check at every iteration the boundary", otherwise I start again from 1.
 */



