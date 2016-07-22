//
//  Direction.hpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 17/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef Direction_hpp
#define Direction_hpp

#include <stdio.h>
#include <cstddef> // for std::size_t
#include <vector>  // for std::vector
#include <array>   // for std::array


namespace ecoli{

/*!
 * Collection of enumeration to identify the various functions to update the direction of the bacterium
 */
namespace FunctionUpdateTheta {

    /*!
     * \brief enumeration of the different type of functions that can be used as newTheta.
     *
     * These are the functions used by the <em>pointer function</em>s newTheta_ptr and diffTheta_ptr to model reorientation and rotational diffusion.
     */

    enum TypeNewTheta{
        /*! We can adopt the principle not to jump of un big step during un time-step, but distribute the reorientation along the all phase of tumbling. In such a case we have to implement diffTheta accordingly: see diffTheta and updateXTheta */
        NO_JUMP_THETA,             //!< there's no jump in the direction
        NEW_THETA_1D,              //!< reverse the velocity
        NEW_THETA_2D_UNIFORM,      //!< uniform on the circle
        NEW_THETA_2D_GAMMA,        //!< wrap-gamma on the circle
        NEW_THETA_2D_GAMMA_PAR,    //!< wrap-gamma on the circle, with settable parameters
        NEW_THETA_3D_UNIFORM       /**< uniform distribution on the unit 3d-sphere */
    };

    /*!
     * enumeration of the different type of functions that can be used to model the rotational diffusion.
     */
    enum TypeDiffheta{
        NO_ROTATIONAL_DIFF,         //!< no rotational diffusione
        DIFF_THETA_2D,              //!< diffusion on the circle
        DIFF_THETA_3D               //!< diffusion on the 3d-sphere
    };

}


/*! \brief struct that collects variables and methods related to the direction that the Ecoli follows.

 * It allows the bacterium to tumble and to perform a diffusive evolution on the (d-1)-dimenational sphere (rotational diffusion) during a run.<br>
 *  This class tries to aggregate all the variables and methods needed to deal with a direction of a bacterium in a generalized velocity-jump model.<br>
 *  The different form of the update, it be the \em tumble event or the <em>rotational diffusion</em>, is managed with the help of <b> pointer functions</b>.
 */

/* NOTICE: the assaignment of the pointer function sould be performed in the following way
 * newTheta = &Direction::newThetaXX
 * the call of the pointed function, sould be as follows: (this -> *newTheta)()
 */

template <std::size_t dimS>
struct Direction{


    //************************************************************************************************
    //*                                     VARIABLES
    //************************************************************************************************

    std::size_t dim;                    //!< dimention of the physical space, in general 1,2 or 3

    /*!If the dim is 1 then there's no rotational diffusion
     * We might want to change this coefficient between run and tumble phase.
    .*/
    double D_theta;                     //!< coefficient of the <em>rotational diffusion</em> during a run.
    double D_theta_tumble;              //!< coefficient of the <em>rotational diffusion</em> during a tumble.

    /*! the dimension of this vector is d-1, and we can construct the corresponding direction easily. Note that if dim is 1 then we can just invert the direction:.*/
    std::array<double,dimS-1> angle;          //!< vector of the spherical coordinate:
    std::array<double,dimS> theta;          //!< direction-vector in the d-dimentional cartesian space.
    std::array<double,dimS> paramNewTheta;  //!< vector of the parameters that the function newThetaxx might have.



    /*! with the help of dim, identifies univocally the function*/
    // TODO: it may be better to use an enum and use it to idenify and save the functions
    /*  something like enum{NEWTHETA1D,NEWTHETA2DUNIF,etc.}*/
    int tipoNewTheta;       //!< this variable take track of the function newTheta selected.
    int tipoDiffTheta[2];   //!< this variable take track of the function diffTheta selected (for run 0th -resp. for thumble 1st- index ).
    /* This is the typedef that allows to write nicer the pointer function used to manage the different newTheta's*/
    /*! pick the right function according to the dimension of the space of the user's preference about the form of the update.*/
    typedef void (Direction::*newTheta_ptr)(); //!< this typedef implements all the possible newThetaXX functions for a /e tumble event.
    /*! pick the right function according to the dimension of the space.*/
    typedef void (Direction::*diffTheta_ptr)(const double &dt); //!< this typedef implements all the possible diffThetaXX functions for the <em>rotational diffusion</em> during a /e run or a /e tumble.
    /*! This function is called only once when a tumble starts.*/
    newTheta_ptr newTheta;  //!< Pointer to the function to be used when updating theta with a \e jump (tumble)

    /*! It is a pointer and should have two components: position [0] for a run and [1] for a tumble
     *   - we might want to have different behaviour of the evolution of the direction according of the state.
     *   - we might want not to be using a abrupt jump in the direction at a tumble, but a smoother process during the all tumbling event.
     */
    diffTheta_ptr diffTheta[2]; //!< pointer of pointer to the function to be used when updating theta during a\e run
    //************************************************************************************************
    //*                                         METHODS
    //************************************************************************************************

    //****************************
    // CONSTRUCTORS.
    Direction();
    Direction(const Direction& directionRef);
    Direction(const bool change_par = false);    //!< constructor with only the dimension of the phisical space
    //****************************
    // DISTRUCTORS.
    ~Direction();

    /*!It should also thake care to initialize the vector paramNewTheta*/
    void setNewTheta(const int tipoNewTheta  = -1 );     //!< this function initialize the pointer newTheta to the right function.
    /*!It also initialize the value of the variable D_theta*/
    void setDiffTheta(const int tipoDiffTheta = -1, const int tipoDiffThetaTumble = -1);    //!< this function initialize the pointer diffTheta to the right function.

    void menuSetTheta();



    //************************************************************************************************

    //************************
    // newThetaXX() functions
    //************************
/*NO_JUMP_THETA*/
    void newThetaNoJump();
/*1D*/
    // 1D only one function
    /*! The tumble event in 1D <em>reverse the direction</em>*/
    void newTheta1D();  //!< newTheta in 1D
    //***************************
/*2D*/
    /*! This function picks a random point on the circle*/
    void newTheta2DUnif();             //!< Uniform distribution on the circle
    void newTheta2DGamma();
    void newTheta2DGammaPar();
    //***************************
/*3D*/
    //************************
    // diffThetaXX() function
    //************************


    void noRotationalDiff(const double &dt);
    void diffTheta2D(const double &dt);
    void diffTheta3D(const double &dt);

};

}

#endif /* Direction_hpp */
