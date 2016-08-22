//
//  gnuplot_singles_3.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "sssr.h"

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "EO_rExp_tExp.h"
#include "CV_rIG_tExp.h"
#include "CV_rExp_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Funz_C.h"

#include "setSizesTitles.hpp"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

void lunch_gnuplot(string name_file_gnu);
void gnuplot_run(string names[], string nome_info, long double mean, int tipo_run, int save_, int cont_sim);
void Name_jumps(std::string name_file_read, std::string names[], int delete_);
long double Analysis_run(string name_file_read, string names[], int run);
string setNameScriptgnuplotSingleGeneral(string tipo, int con_gen_sim, int save_);
string setNameSCRIPTlunchGnuplotSingleGeneral(string tipo, int con_gen_sim, int save_);

//*********************************************************************

void E_coli::gnuplot_single(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim){
    
    // if save_ == 1 -> salvo
    // if save_ == 0 -> 'plotto'
    
    if (save_==1) { // se salvo, salvo anche lo script per la visualizzazione visualizzo anche
        E_coli::writeScriptgnuplotSingle("-base-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, 0);
        E_coli::writeScriptLunchgnuplotSingle("-base-",0, con_gen_sim);
    }
    
    E_coli::writeScriptgnuplotSingle("-base-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, save_);
    E_coli::writeScriptLunchgnuplotSingle("-base-",save_, con_gen_sim);
    
    lunch_gnuplot(setNameSCRIPTlunchGnuplotSingleGeneral("-base-",con_gen_sim,save_));
    
}

//***********

void CV_rExp_tExp::gnuplot_single(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim){
    
    E_coli::gnuplot_single(names_files_Ecoli_mod, names_indice_mod, names_files_tau_mod, names_file_dyn_mod, names_info_mod, T_f,f,save_, con_gen_sim);
    
    if (save_==1) { // se salvo, salvo anche lo script per la visualizzazione visualizzo anche
        writeScriptgnuplotSingle("-dynamics-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, 0);
        writeScriptLunchgnuplotSingle("-dynamics-",0, con_gen_sim);
    }
    
    writeScriptgnuplotSingle("-dynamics-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, save_);
    writeScriptLunchgnuplotSingle("-dynamics-",save_, con_gen_sim);
    
    lunch_gnuplot(setNameSCRIPTlunchGnuplotSingleGeneral("-dynamics-",con_gen_sim,save_));
    
}

//***********

void Molecular_rExp_tExp::gnuplot_single(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim){
    
    E_coli::gnuplot_single(names_files_Ecoli_mod, names_indice_mod, names_files_tau_mod, names_file_dyn_mod, names_info_mod, T_f,f,save_, con_gen_sim);
    
    if (save_==1) { // se salvo, salvo anche lo script per la visualizzazione visualizzo anche
        writeScriptgnuplotSingle("-dynamics-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, 0);
        writeScriptLunchgnuplotSingle("-dynamics-",0, con_gen_sim);
    }
    
    writeScriptgnuplotSingle("-dynamics-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, save_);
    writeScriptLunchgnuplotSingle("-dynamics-",save_, con_gen_sim);
    
    lunch_gnuplot(setNameSCRIPTlunchGnuplotSingleGeneral("-dynamics-",con_gen_sim,save_));
    
}


//***********

void EO_rExp_tExp::gnuplot_single(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim){
    
    E_coli::gnuplot_single(names_files_Ecoli_mod, names_indice_mod, names_files_tau_mod, names_file_dyn_mod, names_info_mod, T_f,f,save_, con_gen_sim);
    
    if (save_==1) { // se salvo, salvo anche lo script per la visualizzazione visualizzo anche
        writeScriptgnuplotSingle("-dynamics-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, 0);
        writeScriptLunchgnuplotSingle("-dynamics-",0, con_gen_sim);
    }
    
    writeScriptgnuplotSingle("-dynamics-",names_files_Ecoli_mod, names_files_tau_mod, names_info_mod, names_file_dyn_mod, T_f, con_gen_sim, save_);
    writeScriptLunchgnuplotSingle("-dynamics-",save_, con_gen_sim);
    
    lunch_gnuplot(setNameSCRIPTlunchGnuplotSingleGeneral("-dynamics-",con_gen_sim,save_));

}


//**********************************************************************
// SCRIPTS
//**********************************************************************

int E_coli::writeScriptgnuplotSingle(string tipo, string *names_files_Ecoli_mod, string *names_files_tau_mod, string *names_info_mod, string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_){
    
    string title;
    std::ofstream file_single_plot(setNameScriptgnuplotSingleGeneral(tipo,con_gen_sim, save_).c_str());
//    std::ofstream file_gnu(setNameSCRIPTlunchGnuplotSingleGeneral(con_gen_sim, save_));
    std::ifstream file_info;
    file_info.open(names_info_mod[0].c_str());
    
    char buffer1[16];
    snprintf(buffer1, sizeof(char) * 16,"sim-%03d-",con_gen_sim);
    
    int n_data=1;
    long double dt;
    
    int conform_save = (save_==1)?sizeTitle::SAVE:sizeTitle::NO_SAVE;
    
    file_info >> title;
    file_info >> n_data;
    file_info >> dt;
    
    
    //    file_single_plot << "set key samplen 2 spacing .5 font \",20\""<<endl;
    file_single_plot << "set multiplot layout 2,2 title \""<< title << "\" "<< setSizesTitles(sizeTitle::LARGE, conform_save) << endl;
    
    //    file_single_plot << "set title \"Position\" font \",50\""<< endl;
    
    
    // Position
    //********************************************************************************************
    {
        
        if (save_==0) {
            cout << "* Position " << endl;
            file_single_plot << "stats \""<< names_files_Ecoli_mod[0]  <<"\" u 1:2 name 'Position'"<<endl;
        }
        
        file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
        file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
        << "set xlabel 'x(mm)' "<< endl
        << "set ylabel 'y(mm)' "<< endl;
        
        file_single_plot << "set title \" Position \" "/*<< title <<*/ << setSizesTitles(sizeTitle::MEDIUM, conform_save) << endl;
        file_single_plot << "set cbrange [-1:1]" << endl;
        file_single_plot << "set palette defined ( -1 \"#B0B0B0\", 0 \"#FF0000\", 1 \"#0000FF\")" << endl;
        file_single_plot << "plot \""<< names_files_Ecoli_mod[0]  <<"\" u 1:2:3 w l lc palette z title 'x(t)'" << endl;
        
    }
    // Theta
    //********************************************************************************************
    {
        if (T_f<50) {
            
            //            if (save_==0) {
            //                cout << "* Direction :" << endl;
            //                file_single_plot << "stats \""<< names_files_Ecoli_mod[1]  <<"\" u 2"<<endl;
            //            }
            
            file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
            file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
            << "set xlabel 't(sec)' "<< endl
            << "set ylabel 'angle(rad)' "<< endl;
            file_single_plot << "set title \" Direction\" "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
            file_single_plot << "plot \""<< names_files_Ecoli_mod[1]  <<"\" u 1:2 with lines linecolor rgb 'blue' title '\theta(t)'" << endl;
            
            
        }else {
            
            // Analysis run
            //********************************************************************************************
            
            string names_jumps[5];
            
            Name_jumps(names_files_tau_mod[0], names_jumps,1);
            
            long double mean=Analysis_run(names_files_tau_mod[0], names_jumps,1);
            
            if (mean<0.0) {
                cout << "\nError in Analysis_run\n";
                return -1;
            }else{
                cout << "mean = " << mean << endl;
            }
            
            file_single_plot << "set title \"Analysis Run\" " << setSizesTitles(sizeTitle::MEDIUM, conform_save)<<endl;
            file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
            file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
            << "set xlabel 'run length(sec)' " << setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl
            << "set ylabel 'fraction runs bigger than x' "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
            //                            << "set format y \"10^{%L}\""<< endl;
            
            file_single_plot << "set logscale y" << endl;
            
            if (save_==0) {cout << "The mean of the run time is " << mean << endl;}
            
            file_single_plot << "plot \""<< names_jumps[0]  <<"\" with lines linecolor rgb 'blue' title 'up', \""<< names_jumps[1]  <<"\" with lines linecolor rgb 'red' title 'down',\""<< names_jumps[2]  <<"\" with lines linecolor rgb 'green' title 'all', \""<< names_jumps[3]  <<"\" with lines linecolor rgb 'black' title 'mix',\""<< names_jumps[4]  <<"\" with lines linecolor rgb '#00ad88', exp(-"<<1/mean <<"*x) with lines title 'exp"<< setiosflags(ios::fixed) << setprecision(1)<< "'" << endl;
            
        }
    }
    // Ligand Concentration
    //********************************************************************************************
    {
        
        
        file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
        file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
        << "set xlabel 't(sec)' "<< endl
        << "set ylabel 'concentration' "<< endl;
        file_single_plot << "unset logscale y" << endl;
        
        if (save_==0) {
            cout << "* Ligand concentration " << endl;
            file_single_plot << "stats \""<< names_files_Ecoli_mod[2]  <<"\" u 2 name 'LigandConcentration'"<<endl;
        }
        
        file_single_plot << "set title \" Ligand Concentration \" "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
        file_single_plot << "plot \""<< names_files_Ecoli_mod[2]  <<"\" u 1:2 with lines linecolor rgb 'blue' title 'c(t,x)'" << endl;
        
    }
    // Histogram run
    //********************************************************************************************
    {
        
        file_single_plot << "set title \" run distributions \" " << setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
        if (save_==0) {
            cout << "* Analysis Runs " << endl;
            file_single_plot << "stats \""<< names_files_tau_mod[0]  <<"\" u 2 name 'runDistributions'"<<endl;
        }
                    
        if (T_f<=25) {
            file_single_plot << "set cbrange [-1:1]" << endl
            << "set xlabel 't(sec)' "<< endl;
            file_single_plot << "set palette defined ( -1 \"#B0B0B0\", 0 \"#FF0000\", 1 \"#0000FF\")" << endl;
            file_single_plot << "plot \""<< names_files_tau_mod[0]  <<"\" u 1:2:3 with linespoint lc palette z title 'run-tumble',  \""<< names_file_dyn_mod  <<"\" u 1:2 with lines linecolor rgb\"red\" title 'prob_r', \""<< names_file_dyn_mod  <<"\" u 1:3 with lines linecolor rgb\"green\" title 'brob_t'"<< endl;
        } else if (T_f<200) {
            file_single_plot << "set cbrange [-1:1]" << endl
            << "set xlabel 't(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
            
            file_single_plot << "set palette defined ( -1 \"#B0B0B0\", 0 \"#FF0000\", 1 \"#0000FF\")" << endl;
            file_single_plot << "plot \""<< names_files_tau_mod[0]  <<"\" u 1:2:3 with linespoint lc palette z title 'run-tumble'" << endl;
            
        }else if (T_f>=200){
            
            ifstream file_tau(names_files_tau_mod[0].c_str());
            string temp_string;
            int n_salti=0;
            
            while (!file_tau.eof()) {
                getline(file_tau,temp_string);
                n_salti++;
            }
            file_tau.close();
            
            cout << "There are " << n_salti << " jumps" << endl;
            
            n_salti=max(150,sqrt(n_salti));
            long double a=15.0/n_salti;
            
            //Primo Metodo
            
            //            file_single_plot << "set xrange [0:7]" << endl;
            ////            file_single_plot << "binwidth=5" << endl;
            //            file_single_plot << "width="<<a<<"#interval width ;"<< endl;
            //            file_single_plot << "hist(x,width)=width*floor(x/width)+width/2.0;" << endl;
            //            file_single_plot <<" set boxwidth width*0.9;" << endl;
            ////            file_single_plot <<" set boxwidth binwidth" << endl;
            //            file_single_plot << "plot \""<< names_files_tau_mod[0]  <<"\" u (hist($2,width)):(2.0) smooth freq w boxes lc rgb \"blue\";" << endl;
            
            //Secondo Metodo
            file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
            file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
            file_single_plot << "set xrange [0:7]" << endl;
            file_single_plot <<  "Min = 0.0 # where binning starts" << endl
            << "Max = 10.0 # where binning ends" << endl
            << "set xlabel 'run(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl
            << "set ylabel 'freq' "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl
            << "width = "<< a << endl
            << "bin(x) = width*(floor((x-Min)/width)+0.5) + Min" << endl
            << "plot \""<< names_files_tau_mod[0]  <<"\" using (bin($2)):(1.0) smooth freq with boxes lc rgb \"blue\" notitle" << endl;
            
            //            After the first line add a new line "stats 'data.dat' u 1". And modify the last line to "plot "data.dat" u (hist($1,width)):(1.0)/STATS_records smooth freq w boxes lc rgb"green" notitle". Then the relative frequencies is plotted.
            
        }
    }
    
    
    file_single_plot << "unset multiplot" << endl;
    
    
    file_single_plot.close();
    
    return 0;
    
}

int E_coli::writeScriptLunchgnuplotSingle(string tipo, int save_, int con_gen_sim){
    
    std::ofstream file_gnu(setNameSCRIPTlunchGnuplotSingleGeneral(tipo,con_gen_sim,save_).c_str());
    
    char buffer1[16];
    snprintf(buffer1, sizeof(char) * 16,"sim-%03d-",con_gen_sim);
    
    if (save_==0) {
        file_gnu << gnuplotSetTerminalPlot << endl;
    } else {
        file_gnu << gnuplotSetTerminalSave_eps << endl;
        string buffer = "_single_bacterium_general.eps";
        string title=buffer1+tipo+buffer;
        file_gnu << "set output \""<< title <<endl;
    }
    
    file_gnu << "b=1;" << endl
             << "load \""<< setNameScriptgnuplotSingleGeneral(tipo, con_gen_sim, save_) <<"\""<< endl;
    
    if (save_!=0) {
        file_gnu << "set output" << endl;
        file_gnu << " " << endl;
    }
    
    
    if (save_==0) {
        file_gnu << "pause mouse any" << endl;
        //        file_single_plot << "quit" <<endl;
    }
    
    file_gnu << "quit" <<endl;
    
    file_gnu.close();
    
    return 0;
    
}

//************

int CV_rExp_tExp::writeScriptgnuplotSingle(string tipo, string *names_files_Ecoli_mod, string *names_files_tau_mod, string *names_info_mod, string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_){
    
    string title;
    std::ofstream file_single_plot;
    string buffer;
    int conform_save = (save_==1)?sizeTitle::SAVE:sizeTitle::NO_SAVE;
    std::ifstream file_info;
    file_info.open(names_info_mod[0].c_str());
    
    file_info >> title;
    
    //*********************************************************************
    
    std::ofstream file_gnu;
    
    
    file_single_plot.open(setNameScriptgnuplotSingleGeneral(tipo,con_gen_sim,save_).c_str());
    
    if (!file_single_plot.is_open()) {
        return -1;
    }
    
    file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                     << "set xlabel 'run(sec)' "<< endl;
    file_single_plot << "set multiplot layout 2,1 title \" Intenal Dynamics "<< title << "\" " << setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    file_single_plot << "set title \" Intenal Dynamics\" "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:2 with lines linecolor rgb\"red\" title '\\lambda_r', \""<< names_file_dyn_mod  <<"\" u 1:3 with lines linecolor rgb\"green\" title '\\lambda_t'"<< endl;
    file_single_plot << "set title \"Memory Kernel\" "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl
                     << "set xlabel 'run(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
    file_single_plot<< "plot \""<< names_file_dyn_mod  <<"\" u 1:4 with lines linecolor rgb\"blue\" title 'Q(t)' "<< endl;
    file_single_plot<< "unset multiplot" << endl;
    
    
    file_single_plot.close();
    
    return 0;
}

//************

int Molecular_rExp_tExp::writeScriptgnuplotSingle(string tipo, string *names_files_Ecoli_mod, string *names_files_tau_mod, string *names_info_mod, string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_){
    
    string title;
    std::ofstream file_single_plot;
    string buffer;
    int conform_save = (save_==1)?sizeTitle::SAVE:sizeTitle::NO_SAVE;
    std::ifstream file_info;
    file_info.open(names_info_mod[0].c_str());
    
    file_info >> title;
    
    //*********************************************************************
    
    std::ofstream file_gnu;
    
    
    file_single_plot.open(setNameScriptgnuplotSingleGeneral(tipo,con_gen_sim,save_).c_str());
    
    if (!file_single_plot.is_open()) {
        return -1;
    }
    
    file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                     << "set xlabel 'run(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
    
    file_single_plot << "set multiplot layout 2,2 title \" Internal Dynamic "<< title <<"\" "<< setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    
    file_single_plot << "set title 'methylation level(meth)' "<< setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:4 with lines linecolor rgb\"blue\" title 'm'"<< endl;
    
    file_single_plot << "set title 'CheY-P(y)' "<< setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:5 with lines linecolor rgb\"black\" title 'y'" << endl;
    
    file_single_plot << "set title 'receptor Kinasys Activity(a)' "<< setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:6 with lines linecolor rgb\"black\" title 'a'" << endl;
    
    file_single_plot << "set title 'probability rate (p_r)' "<< setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:7 with lines linecolor rgb\"black\" title 'p_r'" << endl;
    
    file_single_plot << "unset multiplot" << endl;
    
    
    file_single_plot.close();
    
    return 0;
}


int EO_rExp_tExp::writeScriptgnuplotSingle(string tipo, string *names_files_Ecoli_mod, string *names_files_tau_mod, string *names_info_mod, string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_){
    
    string title;
    std::ofstream file_single_plot;
    string buffer;
    int conform_save = (save_==1)?sizeTitle::SAVE:sizeTitle::NO_SAVE;
    std::ifstream file_info;
    file_info.open(names_info_mod[0].c_str());
    
    file_info >> title;
    
    //*********************************************************************
    
    std::ofstream file_gnu;
    
    
    file_single_plot.open(setNameScriptgnuplotSingleGeneral(tipo,con_gen_sim,save_).c_str());
    
    if (!file_single_plot.is_open()) {return -1;}
    
    file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                     << "set xlabel 'run(sec)' " << setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
    file_single_plot << "set multiplot layout 2,1 title \" Intenal Dynamics "<< title << "\" " << setSizesTitles(sizeTitle::LARGE, conform_save)<< endl;
    file_single_plot << "set title \" Intenal Dynamics\" "<< setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:2 with lines linecolor rgb\"red\" title '\\lambda_r', \""<< names_file_dyn_mod  <<"\" u 1:3 with lines linecolor rgb\"green\" title '\\lambda_t'"<< endl;
    file_single_plot << "set title \"Memory Kernel\" "<< endl
                     << "set xlabel 'run(sec)' " << setSizesTitles(sizeTitle::MEDIUM, conform_save)<< endl;
    
    file_single_plot << "plot \""<< names_file_dyn_mod  <<"\" u 1:4 with lines linecolor rgb\"blue\" title 'y_1(t)', "<<"\""<< names_file_dyn_mod  <<"\" u 1:5 with lines linecolor rgb\"red\" title 'y_2(t)'" << endl;
    
    file_single_plot << "unset multiplot" << endl;
    file_single_plot.close();
    
    return 0;
}

//*********************************************************************
/*! set name for the general plot 1 baccterium - script*/

string setNameScriptgnuplotSingleGeneral(string tipo, int con_gen_sim, int save_){
    char buffer1[16];
    snprintf(buffer1, sizeof(char) * 16,"sim-%03d-",con_gen_sim);
    string save_str = (save_==1)?string("SAVE-"):string("VISUAL-");
    
    return string(buffer1)+tipo+string(save_str)+string("SingleGeneral.gnu");
}

/*! set name for the SCRIPT to lunch general plot 1 baccterium - script*/
string setNameSCRIPTlunchGnuplotSingleGeneral(string tipo, int con_gen_sim, int save_){
    char buffer1[32];
    snprintf(buffer1, sizeof(char) * 32,"SCRIPT-GNUPLOT-sim-%03d-",con_gen_sim);
    string save_str = (save_==1)?string("SAVE-"):string("VISUAL-");
    
    return string(buffer1)+tipo+string(save_str)+string("SingleGeneral.gnu");
}
