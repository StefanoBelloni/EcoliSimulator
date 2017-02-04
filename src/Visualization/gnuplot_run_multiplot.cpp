//
//  gnuplot_run_multiplot.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 09/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>

#include "GnuplotGlobal.h"
#include "setSizesTitles.hpp"
#include "setFileNamesRun.hpp"

using namespace std;


void lunch_gnuplot(string name_file_gnu);
string setNameRunMultiplot(int cont_glob_sim, int saveConforme, int tipo_grafico);

/**
 * Function to plot or save the histogram/ "log-histogram" of run/tumble: two in one image
 * @param tipo_grafico: histogram/ "log-histogram" tipo_grafico == 0 hist; == 1 frac
 * @retunr name of the file to lunch gnuplot
 */

void gnuplot_run_multiplot(string nome_info, string names[], int save_, int cont_glob_sim, int tipo_grafico){

    // if save_ == 1 -> salvo
    // if save_ == 0 -> 'plotto'

    // tipo_grafico == 0 hist
    // tipo_grafico == 1 frac


    int saveConforme = (save_==1)?0:1;

    string title;
    std::ifstream file_info;
    file_info.open(nome_info.c_str());

    string buffer;
    char buffer1[12];

    snprintf(buffer1, sizeof(char) * 12,"sim-%03d-", cont_glob_sim);

    string nameFile = setNameRunMultiplot(cont_glob_sim, saveConforme, tipo_grafico);
    file_info >> title;

    ofstream file_run_plot;

    file_run_plot.open(nameFile.c_str());

    if (tipo_grafico==0) {

        buffer = "-logHist.eps";

        if (save_==0){
            file_run_plot << gnuplotSetTerminalPlot << endl;

            title=buffer1+title+buffer;
            file_run_plot << "#"<< gnuplotSetTerminalSave_eps << endl;
            file_run_plot << "#set output \""<< title <<endl;
        }else {
            file_run_plot << gnuplotSetTerminalSave_eps << endl;

    //----------> QUI HO CAMBIATO IL FORMATO!!!!

//            snprintf(buffer1, sizeof(char) * 12,"sim-%03d-", cont_glob_sim);
            string titleOut=buffer1+title + buffer;
            file_run_plot << "set output \""<< titleOut << "\""<<endl;

        }
//        file_run_plot << "set title \""<<title<<" LOGARITHMIC HISTOGRAM\" "<< setSizesTitles(sizeTitle::HUGE_, saveConforme)<<endl;
//        file_run_plot << "set multiplot layout 2,1" << endl;

    file_run_plot << "set multiplot layout 2,1 title \""<<title<<"\" "<< setSizesTitles(sizeTitle::HUGE_, saveConforme)<<endl;

        file_run_plot << "load \""<< setFileNamesRun(saveConforme, tipoHistGraph::LOG, tipoHistGraph::RUN, cont_glob_sim) <<"\""<< endl;
        file_run_plot << "load \""<< setFileNamesRun(saveConforme, tipoHistGraph::LOG, tipoHistGraph::TUMBLE, cont_glob_sim) <<"\""<< endl;

        file_run_plot << "unset multiplot" << endl;

        if (save_==1) {
            file_run_plot << "set output" << endl;
        }else {
            file_run_plot << "pause mouse any" << endl;
        }

        file_run_plot << "quit" << endl;

    }
    else {

        buffer = "-hist.eps";

        if (save_==0){
            file_run_plot << gnuplotSetTerminalPlot << endl;
            snprintf(buffer1, sizeof(char) * 12,"sim-%03d-", cont_glob_sim);
            string title_eps=buffer1+title+buffer;

            file_run_plot << "#" << gnuplotSetTerminalSave_eps << endl;
            file_run_plot << "#set output \""<< title_eps << "\""<<endl;

        }else {
            file_run_plot << gnuplotSetTerminalSave_eps << endl;

            //----------> QUI HO CAMBIATO IL FORMATO!!!!

            snprintf(buffer1, sizeof(char) * 12,"sim-%03d-", cont_glob_sim);
            string title_eps=buffer1+title+buffer;


            file_run_plot << "set output \""<< title_eps << "\""<<endl;

        }

//        file_run_plot << "set title \""<<title<<"\" "<< setSizesTitles(sizeTitle::HUGE_, saveConforme)<<endl;
//        file_run_plot << "set multiplot layout 2,1" << endl;

        file_run_plot << "set multiplot layout 2,1 title \""<<title<<"\" "<< setSizesTitles(sizeTitle::HUGE_, saveConforme)<<endl;


        file_run_plot << "load \""<< setFileNamesRun(saveConforme, tipoHistGraph::NOT_LOG, tipoHistGraph::RUN, cont_glob_sim) <<"\""<< endl;
        file_run_plot << "load \""<< setFileNamesRun(saveConforme, tipoHistGraph::NOT_LOG, tipoHistGraph::TUMBLE, cont_glob_sim) <<"\""<< endl;

        file_run_plot << "unset multiplot" << endl;

        if (save_==1) {
            file_run_plot << "set output" << endl;
        }else {
            file_run_plot << "pause mouse any" << endl;
        }

        file_run_plot << "quit" << endl;

    }

    file_run_plot.close();

//    return nameFile;
//    lunch_gnuplot("run.gnu");


//    cout << "Premere 1 o due volte Invio ... ";
//    cin.ignore();


}


string setNameRunMultiplot(int cont_glob_sim, int saveConforme, int tipo_grafico){
    char buffer1[12];

    snprintf(buffer1, sizeof(char) * 12,"sim-%03d-", cont_glob_sim);

    string nameFile(buffer1);

    nameFile="SCRIPT-GNUPLOT"+nameFile;

    if (saveConforme==sizeTitle::SAVE){
        nameFile += "save-run-";
    }else{
        nameFile += "visual-run-";
    }

    if (tipo_grafico == 0) {
        nameFile+="logHist.gnu";
    }else{
        nameFile+="Hist.gnu";
    }

    return nameFile;
}
