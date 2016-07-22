#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <iostream>

#include "Names.h"
#include "GeneralSetting.h"
#include "Enviroment.hpp"
#include "UnitMeasure.h"
#include "InitialCondition.h"

namespace ecoli{

/*! \brief this class deals with the setting and run of a simulation.
 *
 * This class will produce files with the data of the simulations. The names of the data are collected inside the struct Names.
 * The result can be used by others classes that deal with the analysis of the data.
 */

template <std::size_t dimS>
class Simulation
{
        /** Default constructor */
    public:
        Simulation();
        /** Default destructor */
        virtual ~Simulation();

        Names names; //!< struct that collects all the names where the different data are saved.
        UnitMeasure* um; //!< pointer to the unit of measure used in a particular experiment
        int general_cont; //!< general counter of the number of simulations

        // I want at least return something, to check if everything worked properly.

        int interactingSimulation();
        int independentSimulation();
        int startSimulation();

        void setSimulation();


    protected:

    private:

        double T_f; //!< final time of the simulation
        double dt;  //!< time-step

        /*!
         * The population need not be made of only one type of bacteria. We might want an eterogeneous population
         */

        unsigned int n_population; //!< number of different population in the experiment
        std::vector<int> n_bacteria; //!< Member variable "n_bacteria"
        std::vector<ecoli::Ecoli<dimS>* > bacteria_ref; //!< Member variable "bacteria_ref"

        bool interacting; //!< set if the simulation is of interacting type.
        bool compare; //!< set if we want to compare the different population or simulate all toghether

        ecoli::Enviroment<dimS>* env; //!< variable that deals with the enviromen.

        // NOTE: the initial conditions are set in the experiment.
        //       We keep a pointer for two reasons:
        //          1- we might want to subclass the Initial conditions
        //          2- we might want to keep a reference to the I.C. in the experiment.

        InitialCondition<dimS>* ic;   //!< initial condition for the simulation.

};

}
#endif // SIMULATION_H
