#ifndef ENVIROMENT_H
#define ENVIROMENT_H


#include <vector>

#include "Chemicals.hpp"
#include "Mesh.h"

namespace ecoli{

/** \brief This class models the enviroment where the bacteria swims
 *
 *
 */


template <std::size_t dimS>
class Enviroment
{
    public:
        /** Default constructor */
        Enviroment();
        /** Default destructor */
        virtual ~Enviroment();

        /*!
         * this 'function' is used to update the enviroment, in the following sense:
         *   - if there is no interaction, then the call of the function is simply empty.
         *   - if there is interaction, then a specific function is called, e.g.
         *      - if the only chemical concentation is a general ligand, then the usual 'diffusion with degradation and source' is solved for the matrix fuctions
         *          whose imput are recorded inside the proper Chemical.
         * \param dt time step.
         * \param t current time.
         */

        typedef void (Enviroment::*updateEnviroment_ptr)(const double& dt, const double& t); //!< typedef for pointer function to update the enviroment.

         // it'd be nice that if there's no interaction all the empty functions were not called!
         // (and in general if any is called)

        updateEnviroment_ptr updateEnviroment;  //!< function used to update the enviroment

        void setEnviroemnt();

    protected:

        std::vector<Chemicals<dimS>* > chemicals; //!< list of the chemical subsatnce in the envirmoment
        // We might want to use something like in DUNE ...
        Mesh<dimS> mesh;                          //!< mesh of the enviroment
        // to keep uniforminty ...
        bool* interacting;                   //!< pointer to the memeber in simulation (or whatever) about interaction:



};

}
#endif // ENVIROMENT_H
