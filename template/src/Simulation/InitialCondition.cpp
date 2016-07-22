#include "InitialCondition.h"

template<std::size_t dimS>
ecoli::InitialCondition<dimS>::InitialCondition()
{
    //ctor
}

template<std::size_t dimS>
ecoli::InitialCondition<dimS>::~InitialCondition()
{
    //dtor
}

template<std::size_t dimS>
void ecoli::InitialCondition<dimS>::setInitialCondition(){
    std::cout << "set initial condition" << std::cout;
}


//***************************************************
//
//***************************************************

template class ecoli::InitialCondition<1>;
template class ecoli::InitialCondition<2>;
template class ecoli::InitialCondition<3>;
