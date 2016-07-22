#ifndef INITIALCONDITION_H
#define INITIALCONDITION_H

#include <stdio.h>
#include <iostream>

namespace ecoli{

/*! \brief This class deals with the initial condition of a simulation
 *
 *  Here are collected the information about the distribution of the population,
 *  or the initial condition for the enviroment.
 */

template<std::size_t dimS>
class InitialCondition
{
    public:
        InitialCondition();
        virtual ~InitialCondition();
        void setInitialCondition();
    protected:
    private:
};

}
#endif // INITIALCONDITION_H
