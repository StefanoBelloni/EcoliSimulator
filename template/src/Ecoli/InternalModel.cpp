//
//  InternalModel.cpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 20/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "InternalModel.hpp"

/** @brief (one liner)
  *
  * (documentation goes here)
  */

template <std::size_t dimS>
double ecoli::InternalModel<dimS>::updateIntDyn(const double& dt)
{
    return 0.0;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */

  template <std::size_t dimS>
std::vector<double> ecoli::InternalModel<dimS>::vectorInternalDyn()
{
    std::vector<double> vect;

    return vect;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */

template <std::size_t dimS>
 ecoli::InternalModel<dimS>::~InternalModel()
{

}

/** @brief Internal Model contructor
  *
  * (documentation goes here)
  */

template <std::size_t dimS>
ecoli::InternalModel<dimS>::InternalModel(bool change, LocomotionLigand<dimS>* pos_lig)
{
    // TODO:

}



/** @brief (one liner)
  *
  * (documentation goes here)
  */

template <std::size_t dimS>
double ecoli::InternalModel<dimS>::doubleInternalDyn()
{

}



template class ecoli::InternalModel<1>;
template class ecoli::InternalModel<2>;
template class ecoli::InternalModel<3>;
