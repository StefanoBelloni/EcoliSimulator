#include "UnitMeasure.h"

#include <iostream>
#include <cmath>


UnitMeasure::UnitMeasure()
{
    //TODO:
    //ctor
}

UnitMeasure::~UnitMeasure()
{
    //TODO:
    //dtor
}

/** \brief
 *
 */

void UnitMeasure::setUnitMeasure(){
    //TODO:
    std::cout << "set Unit measure" << std::endl;
    std::cout << "Set the unit of measure for the space" << std::endl;

}

/** \brief convert the measure (space/time)
*/

double UnitMeasure::convertMeasure(double measure, int starting_unit, int arrive_unit){
    double measureConverted = measure;
    int exp = starting_unit-arrive_unit;
    return (exp!=0)?measure*std::pow(10,exp):measure;
}
