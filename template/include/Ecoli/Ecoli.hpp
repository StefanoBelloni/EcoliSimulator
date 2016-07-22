//
//  Ecoli.hpp
//  EcoliSimulator_0.1
//
//  Created by Stefano Belloni on 18/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef Ecoli_hpp
#define Ecoli_hpp

#include <stdio.h>
#include <string>
#include <fstream>

#include "TimeChange.hpp"
#include "InternalModel.hpp"
#include "Lambda.hpp"
#include "LocomotionLigand.hpp"
#include "continuousmodel.h"


/*! \brief This namespace contains all classes, enumerations and methods that have to do with the implementation and simulation of the bacterium/population of Ecoli */

namespace ecoli{

/*! This connstant is used to uniformy the access to array with data about run and tumble*/
enum INDEX_PHASE{

    RUN_INDEX = 0,       //!< index for the run in an array with data about run and tumble
    TUBLE_INDEX = 1     //!<index for the run in an array with data about run and tumble

};

enum MODELS_NAMES{
    E_COLI_MODEL        //!< base class for Ecoli
};


//std::string modelstoString(int model_code){
//    return "Ecoli_base";
//}

/*! \brief Base Class for a bacterium:
 *
 * It implements the virtual function to update the dynamic of the bacterium.
 * If we would like to have a particluar model, we can just subclass this class and implement the relative parts.<br><br>
 * We have to explain a bit where all the components are and how they are projected:<br>
 *  - the struct TimeChange collects all the information about the generatized subordinator:
 *  - the subordinator are updated via the virtual function updateSubordiantor, which have access to the internal variables;
           in this way we can pass to the variable Lambda all the information needed to update the subordinator.
 *
 */

template <std::size_t dimS>
class Ecoli{

protected:

    int model;
    std::size_t num_bat;
    std::size_t dim;

    LocomotionLigand<dimS>* pos_lig; //!< variable that deals with the position and ligands updates.
    InternalModel<dimS>*    intDyn;  //!< pointer to the model used: in it are kept the variables for space and a pointer to the enviroment.
    TimeChange*             subordinator;  //!< pointer to a Variable that control the evolution of the subordinator.

    ContinuousModel*  cont_model;    //!< pointer to the continuous model.

    virtual void updateSubordiantor(const double &dt);

    std::array<std::ofstream*,3> files;   //!< "list" of files used to save the data (jumps(0-1), internal data(2)).

public:

    /*! In accordance with RUN_INDEX TUBLE_INDEX, it can have the value
          - true = 1 for \e run
          - false = 0 for \e tumble
     */
    bool tumble_phase;  //!< variable that save if we are perfroming a tumble (or a run);

    bool implementedContModel; //!< This variable tells us if there exists an implementation of the continuous model for the current Ecoli.
    bool implementedAgentModel; //!< This variable tells us if there exists an implementation of the agent-based model for the current Ecoli.

    void updateEcoli(const double &t, const double &dt);

    // CONSTRUCTORS & DISTRUCTORS:

    Ecoli(bool change_par = false/*, bool agentBased = true, bool contModel = false*/,std::size_t n_batterio = -1, ecoli::Enviroment<dimS>* ligand_ptr = NULL);
    virtual ~Ecoli();

    void setEnviroment(ecoli::Enviroment<dimS>* ligand_ptr);   // to set the reference to the enviroment (it is inside LocomotionLigand).
    void setParameters();   // to set parameters of the bacterium

    std::string ecoliToString(int model);   //!< This function return a readable name of the model

    // ::::::: SAVE DATA :::::::

    //TODO: decide if we pass the file to the function, or we store the address of the file inside the bacterium.
    // I might also move all the function which saves the data to the class Simulation ...
    //TODO, this in the implementation

    // We keep this function here for the same reasons as in saveJump ...
    virtual int saveEcoliInternalData(){};        //!< this function save the data to a file
    // We keep the function to save data inside relative to the jump inside the class Ecoli,
    // since it is easier to deal with it here.
    typedef void (Ecoli::*saveJump_ptr)(double const t, double const dt, double const tau);  //!< Pointer to the function that save the data about the jump.
    std::array<saveJump_ptr,2> saveJump;

    void saveRun(double const t, double const dt, double const tau);
    void saveTumble(double const t, double const dt, double const tau);


};

}


#endif /* Ecoli_hpp */
