//
//  Chemicals.hpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 21/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef Chemicals_hpp
#define Chemicals_hpp

#include <stdio.h>
#include <cstddef> // for std::size_t

#include "mesh.h"

namespace ecoli{

/*! \brief name space of the type of chemicals substances
 *
 *
 */


namespace ChemicalsSubs{
    enum TypeChemicalSubs{
        LIGAND /**< simple Ligand concentration: it is not specialized*/
    };

}

/*! \brief This class is the base class for chemicals which influnce the dynamics of bacterium.

 E. coli cells swim toward

 - amino acids (serine and aspartic acid),
 - sugars (maltose, ribose, galactose, glucose),
 - dipeptides,
 - pyrimidines
 - electron acceptors (oxygen, nitrate, fumarate).

 E. coli also swims away from potentially noxious chemicals, such as

 - alcohols
 - fatty acids,

 This class can be used as a specification af all the substance or just an average chemical that the bacterium actually 'measures' (such as the FunzC and derived classes in EcoliSimulator_4.x.x)


 */
template <std::size_t dimS>
class Chemicals{

protected:

    std::size_t dim; //!<  physical dimention
    int id; //!< identification of the chemical substance
    Mesh<dimS>* mesh;     //!< pointer to the mesh of the domain


public:

    /*! \brief record if this chemicals inteact activily with the others objects
     *
     * A chemical objects interact with the others if the mutual evolution is influenced activly by the other,
     * i.e. if when we evolve the chemicals, we have to solve a ODE/PDE or similar equation.
     *
     */
    bool interacting;

    //TODO: aggiungere i metodi che restituiscono i valori delle variaboli protette.


};

}
#endif /* Chemicals_hpp */
