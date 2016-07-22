#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "Enviroment.hpp"
#include "Simulation.h"
#include "InitialCondition.h"

/*! \brief this class models an experiment.
 *
 * The experiment is made of three (there is a fourth optional) different part:
 *   - 1 setting the enviroment and kind of experiment: this is done in the costructor via setExperiment.
 *   - 2 performing the simulations: this is done in one part of SimulateAndAnalysis
 *   - 3 Analysis of the results: this is perform in SimulateAndAnalysis
 *   - [4] extraction of paramether and validation: this is done in statisticalAnalysisAndValidation.
 *
 *  An experiment may perform many simulations, which are then analyzed:
 *  A paradigmatic example might be the following:
 *  We want to simulate in a given enviroment 3 different models. We need to perform 3 simulations
 *
 */

// we might extend the template ...
template <std::size_t dimS> // = 2, bool independent = true, typename T = double>
class Experiment
{
    public:

//        Experiment();
        Experiment(bool setEnv = false);
        virtual ~Experiment();


        void simulateAndAnalyse();                  //!< This function perform the experiment and analyze the output.
        void statisticalAnalysisAndValidation();    //!< This function perform the statistical analysis and validate the results.

        void setExperiment();                       //!< this function set the parametrs of the experiment.
        void setSimulations();

        int id;                                     //!< this is the identification of the experiment:

    protected:

        ecoli::Enviroment<dimS> env;           //!< This variable rappresent an enviroment, inside which we perform the experiment
        UnitMeasure um;                             //!< unit of measure used in this simulation.

        unsigned short n_simulation;                //!< number of \e different simulations to be performed in this experiments

        std::vector<ecoli::Simulation<dimS>* > sims;   //!< This is the vector af all the simulation we want to perform

        ecoli::InitialCondition<dimS>* ic;     //!< initial condition for the simulation.

    private:
};


#endif // EXPERIMENT_H
