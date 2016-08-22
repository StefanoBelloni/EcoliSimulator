//
//  baricentro_plot.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 05/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "ErrorsDefinition.h"

#include "setSizesTitles.hpp"
using namespace std;

void funz_clear();
void lunch_gnuplot(string name_file_gnu);
int writeScriptBarycenter(int save_, string name, string name_file_bar,long double D_msq);
string setBaricenterName(int cont_gen_sim);
int renameCpp(string oldname, string newname);
string setFitName(int cont_gen_sim);
int writeLog(string what, string msg);

string setNameScriptBaricenter(string name, int save_);

/** Constant pass to the script-writer to save the picture*/
#define SAVE 0
/** Constant pass to the script-writer not to save the picture*/
#define NO_SAVE 1


/**
 * This function calculate the baricnter, plot with gnuplot
 * @param x_t matrix of the x position x_t[time][n_bacterium]
 * @param y_t matrix of the y position y_t[time][n_bacterium]
 * @param name file where the info are saved (see line 55 - ..)
 */

void baricentro_plot(string name, std::vector<std::vector<long double> > &x_t,std::vector<std::vector<long double> > &y_t,int n_c,int dim_col_t, int cont_gen_sim)
{
    
    cout << "plot of the baricenter trajectory and the mean square displacement:";
    
    string temp;
    long double Dt=0.0L;
    int const_salv=0;
    
    long double x=0.0L,y=0.0L;
    long double x0=0.0L,y0=0.0L;
    
    long double v_x=0.0L,v_y=0.0L;
    long double x_1=0.0L,y_1=0.0L;  // coordinata prec.
    
    long double D2=0.0L;
    long double deltaD=0.0L;

    long double initalD = 0.0L;
    
    ofstream file_baricentro_speed;
    ifstream file_info;
    
    string name_file_bar = setBaricenterName(cont_gen_sim);
    file_baricentro_speed.open(name_file_bar.c_str());
    
    file_info.open(name.c_str());
    file_info >> temp;
    file_info >> const_salv;
    file_info >> Dt;
    file_info >> const_salv;
    
    Dt=Dt*const_salv*(epsilon*epsilon);
    
    file_info.close();
    
    // Dato iniziale.
    
    x=0;
    y=0;
    for (int j=0; j<n_c; j++) {
        x=x+x_t[0][j];
        y=y+y_t[0][j];
    }

    x0=x/n_c;
    y0=y/n_c;

    file_baricentro_speed << 0 << " " << 0 << " " << 0 << " " << initalD << " " << x0 << " " << y0 << endl;
    
//    D2=initalD;
    x_1=x0;
    y_1=y0;
    
    // calculation other times.
    for (int i=1; i<dim_col_t; i++) {
        x=0;
        y=0;
        for (int j=0; j<n_c; j++) {
            x=x+x_t[i][j];
            y=y+y_t[i][j];
            
            // <---------------------------------------------------------------------
//            deltaD+=pow(x_t[i][j]-x0,2)+pow(y_t[i][j]-y0,2);
            deltaD+=pow(x_t[i][j]-x_t[0][j],2)+pow(y_t[i][j]-y_t[0][j],2);
        }        
        
        v_x=(x/n_c-x_1)/Dt;
        v_y=(y/n_c-y_1)/Dt;
        x_1=x/n_c;
        y_1=y/n_c;
        deltaD=deltaD/n_c;
        
        // <------------------ CONTROLLARE QUESTO +=
//        D2+=deltaD;
        D2=deltaD;
        
        file_baricentro_speed << Dt*i << " " << v_x << " " << v_y << " " << D2 << " " << x_1 << " " << y_1 << endl;
        deltaD = 0.0;
    }
    
    cout << "\n***************************************************************\n";
    cout << "Initial value: " << initalD;
    
    file_baricentro_speed.close();
    

    //**************************************
    //**************************************
    
//    string command;
    
//    save script gnuplot
    
    writeScriptBarycenter(NO_SAVE, name, name_file_bar,initalD);
    writeScriptBarycenter(SAVE, name, name_file_bar,initalD);
    
    // Visualizzo ... 
    if (automatic_==0) {
        lunch_gnuplot(setNameScriptBaricenter(name,NO_SAVE).c_str());
    }
    
    // Save pic
    
    lunch_gnuplot(setNameScriptBaricenter(name,SAVE).c_str());
    
    if (renameCpp("fit.log",setFitName(cont_gen_sim))!=0){
        std::cout << "\nERROR" << std::endl;
        string msg("Error reading renaming log file for the linear fitting");
//        msg+=read;
        writeLog("ERROR",msg);
    }

}

/**
 * This function is similar as setting names, but is only for the file of the barycenter which will be name as follows:<br>
 * "baricenter-[cont_gen_sim].dat
 * @params cont_gen_sim is the simulation number.
 */

string setBaricenterName(int cont_gen_sim){
    
    char buffer_sim[20];
    
    snprintf(buffer_sim, sizeof(char) * 20,"baricenter-%03d.dat",cont_gen_sim);
    
    return buffer_sim;
}


/**
 * This function is similar as setting names, but is only for the file of the barycenter which will be name as follows:<br>
 * "baricenter-[cont_gen_sim].dat
 * @params cont_gen_sim is the simulation number.
 */

string setFitName(int cont_gen_sim){
    
    char buffer_sim[20];
    
    snprintf(buffer_sim, sizeof(char) * 20,"Z_fit-msd-%03d.fit",cont_gen_sim);
    
    return buffer_sim;
}

/**
 * This function writes the script for the baricentro_plot
 */
// One should do the same for the other scripts in the program ...

int writeScriptBarycenter(int save_, string name, string name_file_bar, long double initialD){
    
    string name_script_baricenter = setNameScriptBaricenter(name, save_);
    
    std::ofstream file_baricentro_plot(name_script_baricenter.c_str());
    
    if (!file_baricentro_plot.is_open()) {
        cout << "Error opening the file 'baricentro_plot.gnu'" << endl;
        
        string msg("Error opening the file: ");
        msg+=name_script_baricenter;
        writeLog("ERROR",msg);
        return ERROR_OPENING_FILE;
    }
    
    string buffer = name;
    buffer.erase(buffer.end()-4, buffer.end());
    
    if (save_==SAVE) {
        
        file_baricentro_plot << gnuplotSetTerminalSave_eps << endl;
        file_baricentro_plot << "set output \""<< buffer <<"baricentro_.eps\""<<endl;
    }else{
        file_baricentro_plot << gnuplotSetTerminalPlot << endl;
        file_baricentro_plot <<"#" << gnuplotSetTerminalSave_eps << endl;
        file_baricentro_plot << "#set output \""<< buffer <<"baricentro_.eps\""<<endl;
    }
 
    file_baricentro_plot << "#set multiplot" << endl;
    file_baricentro_plot << "set multiplot layout 3,1 title \""<< buffer <<"\"" << setSizesTitles(sizeTitle::MEDIUM, save_) << endl;
    file_baricentro_plot << "set key " << setSizesTitles(sizeTitle::MEDIUM, save_) << endl;
    
    // POSITION BARYCENTER ...

    file_baricentro_plot << "set size 1,.33" << endl
    << "set origin 0.0,0.66" << endl;
    file_baricentro_plot << "set title 'Trajectory of the Baricenter'" << setSizesTitles(sizeTitle::LARGE, save_)<< endl;
    file_baricentro_plot << "# move legent to top left" << endl;
    file_baricentro_plot << "set key left top" << endl;
    file_baricentro_plot  << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set xlabel 'x(mm)' "<< setSizesTitles(sizeTitle::MEDIUM, save_) << endl
                        << "set ylabel 'y(mm)' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "#set size number axis" << endl
                        << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl;
    
    file_baricentro_plot << "plot \""<<name_file_bar<<"\" u 5:6 with lines linecolor rgb 'blue' title 'barycenter' " << endl;
    
    
    // SPEED BARYCENTER ...
    
    file_baricentro_plot << "set size 1,.33" << endl
                        << "set origin 0.0,.33" << endl;
    file_baricentro_plot << "set title 'Speed of the Barycentre'"<< setSizesTitles(sizeTitle::LARGE, save_) << endl;
    file_baricentro_plot  << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set xlabel 't(s)' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "set ylabel 'v' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "#set size number axis" << endl
                        << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl;
    file_baricentro_plot << "plot \""<<name_file_bar<<"\" u 1:2 with lines linecolor rgb \"red\" title 'v_x', \""<<name_file_bar<<"\" u 1:3 with lines linecolor rgb 'blue' title 'v_y'" << endl;
    
    // Fitting, without y=ax
    file_baricentro_plot << "#FIT LIM" << endl;
    file_baricentro_plot << "FIT_LIMIT=1.e-12" << endl;
    file_baricentro_plot <<"# regression line"<<endl;
    file_baricentro_plot << "f(x) = a*x " <<endl;
    file_baricentro_plot << "fit f(x) \""<<name_file_bar<<"\" u 1:4  via a" << endl;
    file_baricentro_plot <<"title_f(a,b) = sprintf('f(x) = %ft', a)"<<endl;

    // Fitting, without y=ax^2+bx
    file_baricentro_plot <<"# regression line"<<endl;
    file_baricentro_plot << "f2c(x) = b*x*x +c*c*x" <<endl;
    file_baricentro_plot << "fit f2c(x) \""<<name_file_bar<<"\" u 1:4  via b,c" << endl;
    file_baricentro_plot <<"title_f2c(a,b) = sprintf('f(x) = %ft^2+%ft', b,c*c)"<<endl;
    
    // M.S.D and LINEAR FITTINGS
    file_baricentro_plot << "set size 1,.33" << endl
                        << "set origin 0.0,0.0" << endl;
    file_baricentro_plot << "set title 'Mean Square Displacement and Linear Regression'" << setSizesTitles(sizeTitle::LARGE, save_) << endl; //   font 'sans, 10'
    file_baricentro_plot  << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set xlabel 't(s)' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "set ylabel 'm.s.d' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "#set size number axis" << endl
                        << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                        << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl;
    
    file_baricentro_plot << "plot \""<<name_file_bar<<"\" u 1:4 with lines linecolor rgb 'blue' title 'm.s.d.'"
                         << ", f(x) t title_f(a,b)"
                         << ", f2c(x) t title_f2c(a,b)"
//                         << ", f2(x) t title_f2(a,b)"
                         << "#, f3(x) t title_f3(a,b), fsqrt(x) t title_fsqrt(a,b)"<< endl;
    
    file_baricentro_plot << "#unset multiplot" << endl;
    file_baricentro_plot << "unset multiplot" << endl;
    
    if (save_==NO_SAVE) {
        file_baricentro_plot<< "pause mouse any" << endl
                            << "quit" <<endl;
    }
    
    file_baricentro_plot.close();
    
    funz_clear();
    
    if (save_==SAVE) {
        return writeScriptBarycenter(NO_SAVE,name,name_file_bar,initialD);
    }
    
    return 0;
}


/*! \brief this function is used to rename a file.
 */

int renameCpp(string oldname, string newname){
    
    int result;
    
    result= rename( oldname.c_str() , newname.c_str());

    if ( result == 0 )
        puts ( "File successfully renamed" );
    else
        perror( "Error renaming file" );
    
    return result;
}

/*! \brief resturn the name of the file for the script of the baricenter
 */

string setNameScriptBaricenter(string name, int save_){
    
    name.erase(name.end()-4, name.end());
    
    name = "SCRIPT-GNUPLOT-"+name;
    
    name+=(save_==SAVE)?"-save":"-visual";
    
    return name+"-baricentro_plot.gnu";
}
