#include "Mesh.h"

template<std::size_t dimS>
ecoli::Mesh<dimS>::Mesh()
{
    //ctor
}

template<std::size_t dimS>
ecoli::Mesh<dimS>::~Mesh()
{
    //dtor
}




//*******************************************************
//
//*******************************************************

template class ecoli::Mesh<1>;
template class ecoli::Mesh<2>;
template class ecoli::Mesh<3>;
