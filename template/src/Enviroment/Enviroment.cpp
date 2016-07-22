#include "Enviroment.hpp"

#include <iostream>

template <std::size_t dimS>
ecoli::Enviroment<dimS>::Enviroment()
{
    //ctor
}

template <std::size_t dimS>
ecoli::Enviroment<dimS>::~Enviroment()
{
    //dtor
}

/** \brief This function is used to set up the enviroemnt.
 *
 */

template <std::size_t dimS>
void ecoli::Enviroment<dimS>::setEnviroemnt(){
    std::cout << "Set the enviroment ... " << std::endl;
    std::cout << "    1 - select the area;" << std::endl;
    std::cout << "    2 - select the chemicals & functions;" << std::endl;
    std::cout << "    3 - select the unity of measurament" << std::endl;
    std::cout << "    4 - ... ;" << std::endl;

}

template class ecoli::Enviroment<1>;
template class ecoli::Enviroment<2>;
template class ecoli::Enviroment<3>;
