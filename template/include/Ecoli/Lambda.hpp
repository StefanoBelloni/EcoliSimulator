//
//  Lambda.hpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 21/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef Lambda_hpp
#define Lambda_hpp

#include <stdio.h>
#include <vector>

#include "DefoultQuantity.h"
#include "discretelambda.h"

namespace ecoli{

enum TypeResponseFunctions{
    DEFAUL_LAMBDA,
    DEFAULT_SIGMA
};

/*! \brief this class deals with the response function which drives the update of the subordinator.
 *
 * this class implements
 */

class Lambda{

protected:


    DiscreteLambda* disc_lambda; //!< discrete version of the response function
    int type_response_lambda;  //!< type of response for lambda
    int type_response_sigma;  //!< type of response for sigma

public:
    double tau_mean[2];  //!< mean time of a tumble/run in the stationary state
    double lastLambda;  //!< This variable recoreded the last value of Lambda, before the last update
    double lastVar;     //!< This variable recorded the last variance measured, i.e. \f$dt\cdot\sigma^2(\cdot)\f$
    double mainParDist; //!< Main parameter
    std::vector<double> listParDist;  //!< variable that

    Lambda(bool change_par = false,
           DiscreteLambda* discreteVersion = NULL,
           double tau_r = DefaultLambda::tau_r,
           double tau_t = DefaultLambda::tau_t,
           int type_lambda = TypeResponseFunctions::DEFAUL_LAMBDA,
           int type_sigma = TypeResponseFunctions::DEFAULT_SIGMA);

//public:
//
//    double operator()(const bool tumble_phase){return tau_mean[tumble_phase];};
//    double operator()(const std::vector<double> &Q);
//    double operator()(const double &Q);
//
//    typedef void (*prova_pt)(const double &Q);
//    prova_pt prova;

};

}
#endif /* Lambda_hpp */
