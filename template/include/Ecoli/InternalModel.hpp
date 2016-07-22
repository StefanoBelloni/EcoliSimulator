//
//  InternalModel.hpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 20/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef InternalModel_hpp
#define InternalModel_hpp

#include <stdio.h>
#include <vector>
#include <map>

#include "Chemicals.hpp"
#include "Lambda.hpp"
#include "LocomotionLigand.hpp"


namespace ecoli{

/*! \brief This class implements the internal dynamic of the bacterium.
 *
 *
 */

template <std::size_t dimS>
class InternalModel{

protected:

    std::vector<double> InternalVar;  //!< Variables that deals with the evolution of the internal dynamics.


public:

    LocomotionLigand<dimS>* pos_lig; //!< reference to the (pointer) space and Ligands

    /*!
     * @param dt time step on which perfom the up-date
     * @return the vector of the quantity that are used by the operator Lambda to calculate the probability rate
     */
    virtual double updateIntDyn(const double &dt);   //!< this function update the internal dynamic of the Bacterium

    virtual std::vector<double> vectorInternalDyn(); //!< returns the vector of internal variable used to calculate the update of the Subordinator
    virtual double doubleInternalDyn(); //!< returns the variable from the internal variable used to calculate the update of the Subordinator

    InternalModel(bool change, LocomotionLigand<dimS>* pos_lig = NULL);
    virtual ~InternalModel();

};

}

#endif /* InternalModel_hpp */
