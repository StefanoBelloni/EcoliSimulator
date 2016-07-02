//
//  gnuplot_run.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 29/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//



#include <iostream>
#include <fstream>

#include "setSizesTitles.hpp"
#include "setFileNamesRun.hpp"

using namespace std;

void lunch_gnuplot(string name_file_gnu);

/**
 * function to plot the run or tumbles
 */

void gnuplot_run(string names[], string nome_info, double mean, int tipo_run, int save_, int cont_sim)
{
    
    //tipo_run ==1 run, altro tumble
    
    string title;
    std::ifstream file_info;
    file_info.open(nome_info.c_str());
    
    file_info >> title;
    
    ofstream file_run_plot;
    
    //*******************************
    //      FRACTION
    //*******************************
    
    
    if (tipo_run==1) {
        file_run_plot.open(setFileNamesRun(save_, tipoHistGraph::LOG, tipoHistGraph::RUN, cont_sim).c_str());
        file_run_plot << "set title 'Log-Distrubution of Runs'" << setSizesTitles(sizeTitle::LARGE, save_) << endl;
        file_run_plot << "set xrange [0:6]" << endl;
    }else {
        file_run_plot.open(setFileNamesRun(save_, tipoHistGraph::LOG, tipoHistGraph::TUMBLE, cont_sim).c_str());
        file_run_plot << "set title 'Log-Distrubution of Runs'"<< setSizesTitles(sizeTitle::LARGE, save_) << endl;
        file_run_plot << "set xrange [0:1.2]" << endl;
    }
    
    string str_tipo_run = (tipo_run==1)?"runs":"tumble";
    
//    file_run_plot << "set title 'Analysis Runs'" << endl;
    file_run_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_run_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
    // TODO: check save not save ...
    
    // ingrandire size x/y tics
    << "#set size number axis" << endl
    << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
    << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
        << "set key "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                << "set xlabel 'run length(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                << "set ylabel 'fraction "<<str_tipo_run<< " bigger than x' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
    << "set format y \"10^{%L}\""<< endl;
    
    file_run_plot << "set logscale y" << endl;    
    
    mean=1/mean;
    
    file_run_plot << "plot \""<< names[4]  <<"\" u 1:2 with lines linecolor rgb 'blue' title 'all',";
    
 
    
    if (tipo_run==1) {
        file_run_plot << " \""<< names[0]  << "\" u 1:2 with lines linecolor rgb 'red' title 'up',\""<< names[1]  <<"\" u 1:2 with lines linecolor rgb 'green' title 'down',\""<< names[2]  <<"\" u 1:2 with lines linecolor rgb 'black' title 'const',\""<< names[3]  <<"\" u 1:2 with lines linecolor rgb '#00ad88' title 'mix',";
    }
    
    file_run_plot << "exp(-"<<mean <<"*x) with lines title 'exp(-x/mean)'" << endl;
    
    file_run_plot.close();    
    
    //*******************************
    //      HISTOGRAM
    //*******************************
    
    
    if (tipo_run==1) {
        file_run_plot.open(setFileNamesRun(save_, tipoHistGraph::NOT_LOG, tipoHistGraph::RUN, cont_sim).c_str());
        file_run_plot << "set title 'Distrubution of Runs'" << setSizesTitles(sizeTitle::LARGE, save_) << endl;
        file_run_plot << "set xrange [0:7]" << endl;
    }else {
        file_run_plot.open(setFileNamesRun(save_, tipoHistGraph::NOT_LOG, tipoHistGraph::TUMBLE, cont_sim).c_str());
        file_run_plot << "set title 'Distrubution of Tumbles'" << setSizesTitles(sizeTitle::LARGE, save_) << endl;
        file_run_plot << "set xrange [0:1.6]" << endl;
    }
    
//    file_run_plot << "set title 'Histograms'" << endl;
    file_run_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_run_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
    
    // ingrandire size x/y tics
    << "#set size number axis" << endl
    << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
    << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
        << "set key "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                    << "set xlabel 'length(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
    << "set ylabel 'frequence' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl;
//    mean=1/mean;
    
    file_run_plot << "unset logscale y" << endl;
    
    file_run_plot << "plot \""<< names[4]  <<"\" u 1:3 with lines linecolor rgb 'blue' title 'all',";
    
    if (tipo_run==1) {
        file_run_plot << " \""<< names[0]  <<"\" u 1:3 with lines linecolor rgb 'red' title 'up',\""<< names[1]  <<"\" u 1:3 with lines linecolor rgb 'green' title 'down',\""<< names[2]  <<"\" u 1:3 with lines linecolor rgb 'black' title 'const',\""<< names[3]  <<"\" u 1:3 with lines linecolor rgb '#00ad88' title 'mix'";
    }
    
//    file_run_plot << ",exp(-"<<mean <<"*x) with lines" << endl;
    
    file_run_plot.close(); 
    
    
}
