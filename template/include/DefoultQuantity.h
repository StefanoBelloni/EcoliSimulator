//
//  DefoultDirection.h
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 23/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef DefoultDirection_h
#define DefoultDirection_h

/*!
 * @brief In this namespace are seved all the defoult values for the struct Direction
 */

// In this way it weill be easy to  modify and controll them.

namespace DefoultDirection {

    const std::size_t dim = 2;            //  dimension: 2D*/
    const double D_theta = 0.25;          // diffusive coefficient run (see. Celani Vergassola (2010))
    const double D_theta_tumble = 0.0;    // there's no diffusive coefficient tumble,
    const short defoultFunctions = -1;    // in this way the implementation decide which is the defoult according to the different scenarios

}

namespace DefaultLambda{
    const double tau_r = 0.8;            // defoult mean run length
    const double tau_t = 0.1;            // defoult mean tumble length
}


#endif /* DefoultDirection_h */
