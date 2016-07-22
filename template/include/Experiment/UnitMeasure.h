#ifndef UNITMEASURE_H
#define UNITMEASURE_H

/*! \brief Class that deals with the unity of measure
 *
 * It provides a unification of the unity of measure.
 */

namespace unitMeasure{

    enum prefix{

         	yotta   = 24, //!< 	Y 	Quadrilione 	1 000 000 000 000 000 000 000 000
            zetta   = 21, //!< 	Z 	Triliardo 	1 000 000 000 000 000 000 000
            exa     = 18,   //!<	E 	Trilione 	1 000 000 000 000 000 000
            peta    = 15,  //!<	P 	Biliardo 	1 000 000 000 000 000
            tera    = 12,      //!<	T 	Bilione 	1 000 000 000 000
            giga    = 9, //!<	G 	Miliardo 	1 000 000 000
            mega    = 6, //!<	M 	Milione 	1 000 000
            chilo   = 3, //!<	k 	Mille 	1 000
            hecto   = 2, //!<	h 	Cento 	100
            deca    = 1,//!<	da 	Dieci 	10
            base    = 0, //!<	Uno 	1
            deci    =-1, //!<	d 	Decimo 	0,1
            centi   =-2,//!<	c 	Centesimo 	0,01
            milli   =-3,//!<	m 	Millesimo 	0,001
            micro   =-6,//!<	µ 	Milionesimo 	0,000 001
            nano    = -9,//!<	n 	Miliardesimo 	0,000 000 001
            pico    =-12,//!<	p 	Bilionesimo 	0,000 000 000 001
            femto   =-15,//!<	f 	Biliardesimo 	0,000 000 000 000 001
            atto    =-18,//!<	a 	Trilionesimo 	0,000 000 000 000 000 001
            zepto   =-21,//!<	z 	Triliardesimo 	0,000 000 000 000 000 000 001
            yocto   =-24//!<	y 	Quadrilionesimo 	0,000 000 000 000 000 000 000 001

    };


//    enum unityTime {
//        secondo = 0,
//        minuto,
//        ora,
//        giorno,
//        settimana
//    };

}

class UnitMeasure
{
    public:
        /** Default constructor */
        UnitMeasure();
        /** Default destructor */
        virtual ~UnitMeasure();

        void setUnitMeasure();


        double convertMeasure(double measure, int starting_unit, int arrive_unit);        //!< convert the measure (space/time)
//        void convertMeasureTime(double measure, int starting_unit, int arrive_unit);    //!< convert the measure (only time)
        double measureToString();   //!< return a readable string of the unit of measure.


    protected:
        int u_space; //!< unit of measure for the space
        int u_time; //!< unit of measure for the time
        bool diffusiveScale; //!< if the riscale is diffusive, i.e. \f$ x\mapsto\epsilon x,t\mapsto\frac{t}{\epsilon^2} \f$
        double epsilon_time; //!< value of the riscaling factor for the time (\f$t\mapsto\frac{t}{\epsilon_t}\f$)
        double epsilon_space; //!< value of the riscaling factor for the space (\f$ x\mapsto\epsilon_x x\f$)
};

#endif // UNITMEASURE_H
