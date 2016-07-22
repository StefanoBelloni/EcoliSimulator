//  TimeChange.hpp
//
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 18/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef TimeChange_hpp
#define TimeChange_hpp

#include <stdio.h>
#include <vector>
#include <array>
#include <cmath>

#include "Lambda.hpp"

namespace ecoli{

namespace FunctionsTimeChange {
    /*!This enum contains all the different time-change the program can deal with*/
    enum TypeUpdateBarrier{
        DET_JUMP,
        EXP_DIST,
        PARETO_DIST
    };

    enum TypeCheck {
        SIMPLE_CROSS,   //!< simple cross of the barrier
        DIFFUSION_CROSS //!< check if a diffusion cross a barrier
    };

}

/*! \brief class that deals with the event of hitting a barrier by the generalized subordinator process
 *
 * NOTE to use checkSubordinator:<br>
 * If we want to check if a diffusion process
    \f[ du(t)=a(t)dt+b(t)dW(t)\f] crossed the barrier s, we might want to check the condition:
    \f[exp(-2*(s-u)*(s-(u+du))/(dt*b^2))>=\textrm{unifRand()}.\f]
 In this case we may use the parameters Lambda.mainParDist, if only one is needed, or the relative vector, that are accessable from TimeChange
 *
 */

struct TimeChange{

    bool param_changed; //!< keep track if we change or not the parameters
    bool* tumble_phase;  //!< pointer to the current tumble phase
    double lambda[2]; //!< subordinator for the tumble phase and run phase
    double t_last[2];     //!< time when last tumble/run began
    double thershold[2]; //!< threshold for the subordinator lambda.

    Lambda* dLambda;        //!< this variable capture the response function

    /*! This functions will update thershold_(phase)
     * @return the duration of the corresponding phase, i.e. t-t_r
     */
    typedef double (TimeChange::*updateThreshold_ptr)(const double &t);  //!< typedef for the pointer function that deals with the update of the thershold
    std::array<updateThreshold_ptr,2> updateThreshold;   //!< this array save the function we want to use to update the thershold.

//    /*! This functions will update lambda_(phase):
//     *  @param dt time step
//     *  @param dLambda is the increment in the subordinator lambda_(phase)
//     */

    typedef bool (TimeChange::*checkSubordinator_ptr)();  //!< typedef for the pointer function that deals with the update of the subordinators
    /*!As usual the array is 2-dimentional, [0]-> run, [1]-> tumble*/

    std::array<checkSubordinator_ptr,2> checkSubordinator;  //!< this array save the function we want to use to check the subordinator.


    virtual void setParemeters(int tipo_r  = ecoli::FunctionsTimeChange::EXP_DIST,
                               int tipo_t = ecoli::FunctionsTimeChange::EXP_DIST);          //!< Set the parameters of this class.

    void setTypeThreshold(int tipo_r, int tipo_t);  //!< set the Threshold Type.

    void setCheckSubordinator(const int tipoCheck_r = FunctionsTimeChange::SIMPLE_CROSS,
                              const int tipoCheck_t = FunctionsTimeChange::SIMPLE_CROSS);        //!< Set the way we check for the subordinator

    TimeChange(bool* tamble_phase_par, bool change = false , int tipo_r = ecoli::FunctionsTimeChange::EXP_DIST,
                int tipo_t = ecoli::FunctionsTimeChange::EXP_DIST); //!< Constructor


    //*****************************
    // TYPE OF CHECK SUBORDINATOR
    //*****************************

    bool simpleCross(){
        return (lambda[*tumble_phase]>=this->thershold[*tumble_phase]);
    }

    bool diffusionCross(){
        //condition for a jump
        return exp( -2*(thershold[*tumble_phase]-dLambda->lastLambda)
                        *(thershold[*tumble_phase]-lambda[*tumble_phase])
                         /dLambda->lastVar ) >= 0.5;  //TODO: >= UnifRand()!!

    }

};

}

#endif /* TimeChange_hpp */
