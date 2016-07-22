#include "Simulation.h"

template <std::size_t dimS>
ecoli::Simulation<dimS>::Simulation()
{
    //ctor
}

template <std::size_t dimS>
ecoli::Simulation<dimS>::~Simulation()
{
    //dtor
}

/** @brief set the simulation parameters
  *
  * (documentation goes here)
  */
  template <std::size_t dimS>
void ecoli::Simulation<dimS>::setSimulation()
{
    std::cout << "SETTING OF THE SIMULATION:" << std::endl;

}

/** @brief start the simulation, it will call the right function according to the setting
  *
  * (documentation goes here)
  */

 template <std::size_t dimS>
int ecoli::Simulation<dimS>::startSimulation()
{
    return 0;
}

/** @brief simulation of an independent population
  *
  * (documentation goes here)
  */
template <std::size_t dimS>
int ecoli::Simulation<dimS>::independentSimulation()
{
    return 0;
}

/** @brief simulation of a interacting simulation.
  *
  * (documentation goes here)
  */
template <std::size_t dimS>
int ecoli::Simulation<dimS>::interactingSimulation()
{
    return 0;
}



template class ecoli::Simulation<1>;
template class ecoli::Simulation<2>;
template class ecoli::Simulation<3>;
