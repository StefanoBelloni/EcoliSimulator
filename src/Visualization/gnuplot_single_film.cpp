//
//  gnuplot_single_film.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 09/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

// set size ratio 0.71

#include <iostream>
#include <fstream>
#include <cmath>
#include "Declar_funz.h"
#include <limits>
#include <ctime>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "apngasm_Global.h"
#include "sssr.h"

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rIG_tExp.h"
#include "CV_rExp_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Funz_C.h"


void lunch_gnuplot(string name_file_gnu);
string setNameScriptSingleFilm(int cont_sim, int save);
int writeSciptFilmSingle(string title, double dt, double T_f, double c_max, double x_m, double  y_m, double x_M, double y_M, int n_data, int salti_, string *names_files_Ecoli_mod, string &names_file_dyn_mod, int save_, int cont_sim);
int writeSciptFilmSingle_gif(string title, double dt, double T_f, double c_max, double x_m, double  y_m, double x_M, double y_M, int n_data, int salti_, string *names_files_Ecoli_mod, string &names_file_dyn_mod, int save_, int cont_sim);
string setNameScriptLunchFilm(int cont_sim, int save);
int writeSciptLunchFilmSingle(int cont_sim, int save);
int writeSciptLunchFilmSingle_gif(int cont_sim, int save, string name_);

//************************************************************************************************************
//          .PNG
//************************************************************************************************************

void E_coli::gnuplot_single_film(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, double T_f, Funz_C *f, int cont_sim)
{
    
    string title;
    std::ofstream file_single_plot;
    std::ofstream file_gnu;

    std::ifstream file_info;
    file_info.open(names_info_mod[0].c_str());
    
    int n_data=1;
    double dt;
    double dt_=0;
    int n_Dt = 1;
    
    file_info >> title;
    file_info >> n_data;
    file_info >> dt;
    file_info >> n_Dt;
    
    dt*=n_Dt;
    
    int risp=1;
    int risp_save=1;
    int risp_par=1;
    
    cout << "Do you want to reproduce now the film of the trajectory? \npress 0 for yes, 1 for no \n";
    cout << "If you want only to save it, press 1\n...";
    sssr(risp,"Do you want to reproduce now the film of the trajectory? 0");
    
    cout << "Total time simulation: T_f = " << T_f << endl;
    cout << "insert the time (in sec) between two frames: ";
    cout << "there a frame saved for every " << dt << " seconds";
    sssr(dt_,"insert the time (in sec) between two frames");
    
    if (automatic_!=1) 
    {
        
    cout << "Do you want to save the film? \npress 0 for yes, 1 for no ";
    if (automatic_==0) {
        getInput( risp_save);
    }else {
        risp_save=0;
    }


    double c_max=-1;
    double x_M=-10000,x_m=10000,y_M=-10000,y_m=10000;
    
        // File istruzioni per gnuplot        
            
    ifstream file_c;
    ifstream file_x;
    double c_temp=0;
    double x_temp=0;
    double y_temp=0;
    int int_temp=0;
    
    c_max=0;
    
    file_c.open(names_files_Ecoli_mod[2].c_str());
    file_x.open(names_files_Ecoli_mod[0].c_str());
    
    while (!file_c.eof()) {
        file_c >> c_temp;
        file_c >> c_temp;
        c_max=max(c_max, c_temp);
    }
    
    c_max+=.05;
    
    while (!file_x.eof()) {
        file_x >> x_temp >> y_temp >> int_temp;
        x_M=max(x_M, x_temp);
        y_M=max(y_M, y_temp);
        x_m=min(x_m, x_temp);
        y_m=min(y_m, y_temp);
    }
    
    x_M+=0.05; y_M+=0.05; 
    x_m-=0.05; y_m-=0.05;
    
    file_c.close();
    file_x.close();
    
    cout << "The max ligand concentration is "<< c_max << endl; 
    cout << "The trajectory of the bacterium is inside the rectangle" << endl
         << "(x_min,y_min) = (" << x_m <<","<<y_m <<")"<<endl
         << "(x_Max,y_Max) = (" << x_M <<","<<y_M <<")"<<endl;
    
    if ((automatic_==0) && (risp==0)) {
        cout << "Set parameters of the video? press 1 for yes, 0 for no ";
        getInput( risp_par); 
    }else {
        risp_par=0;
    }

    // set parameters ...
    if (risp_par==1) {
        
        cout << "Max ligand concentration ";
        sssr(c_max, "Max ligand concentration");
        
        cout << "x_Max = ";
        sssr(x_M,"x_Max = ");
        cout << "x_min = ";
        sssr(x_m,"x_min = ");
        cout << "y_Max = ";
        sssr(y_M,"y_Max = ");
        cout << "y_min = ";
        sssr(y_m,"y_min = ");
        
        if (x_M<=x_m || y_M<=y_m) {
            cout << "Error inserting, default parameters ... ";
            x_M=f->max_x+.02;x_m=f->min_x-.02;y_M=f->max_y+.02;y_m=f->min_y-.02;
        }
    }
  
    int salti_= ((floor(dt_/dt)) > (1)) ? (floor(dt_/dt)) : (1) ;
    // Creazione File per Gnuplot          
    
    //riproduco solo il filmato
    if (risp==0 && (risp_save!=0)) {
        cout  <<"\nplay video without saving ...\n";
        writeSciptFilmSingle(title, dt, T_f, c_max, x_m, y_m, x_M, y_M, n_data, salti_, names_files_Ecoli_mod, names_file_dyn_mod, risp_save, cont_sim);
        writeSciptLunchFilmSingle(cont_sim, risp_save);
    }
    //salvo il filmato
    if (risp_save==0){
        writeSciptFilmSingle(title, dt, T_f, c_max, x_m, y_m, x_M, y_M, n_data, salti_, names_files_Ecoli_mod, names_file_dyn_mod, 1, cont_sim);
        writeSciptFilmSingle(title, dt, T_f, c_max, x_m, y_m, x_M, y_M, n_data, salti_, names_files_Ecoli_mod, names_file_dyn_mod, risp_save, cont_sim);
        writeSciptLunchFilmSingle(cont_sim, 1);
        writeSciptLunchFilmSingle(cont_sim, risp_save);
    }
        
    if (risp_save==0) {
        lunch_gnuplot(setNameScriptLunchFilm(cont_sim, risp_save).c_str());
    }else{
        lunch_gnuplot(setNameScriptLunchFilm(cont_sim, risp_save).c_str());
    }
   
    //riproduco il filmato se lo ho salvato ...
    if (risp_save==0) {
        
        cout << "Save film ...\n";

        string name = names_info_mod[0];
        name.erase(name.end()-3, name.end());
        name = name+"png";
        
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
        string command_apngas_= apngas_lunch+name+" film2D000001.png "+apngas_opt;            
        #else
        string command_apngas_= apngas_lunch+"film2D*.png -o "+name+apngas_opt;                                               
        #endif

        cout << "saving file \n";
            
        system(command_apngas_.c_str());
        
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
        system("del film2D*.png");
#else
        system("rm -Rf film2D*.png");
#endif       
        cout << "file saved \n"; 
        
        // Guardo il filmato 
        if (risp==0) {                    
            command_apngas_ = "open -a firefox "+name;
            system(command_apngas_.c_str());
            
        }
    }
    
    }
}

//************************************************************************************************************
//          .GIF
//************************************************************************************************************

/*! \brief produce the .gif film*/

void E_coli::gnuplot_single_film_gif(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, double T_f, Funz_C *f, int cont_sim)
{
    
    string title;
    std::ofstream file_single_plot;
    std::ofstream file_gnu;
    
    std::ifstream file_info;
    file_info.open(names_info_mod[0].c_str());
    
    int n_data=1;
    double dt;
    double dt_=0;
    int n_Dt = 1;
    
    file_info >> title;
    file_info >> n_data;
    file_info >> dt;
    file_info >> n_Dt;
    
    dt*=n_Dt;
    
    int risp=1;
    int risp_save=1;
    int risp_par=1;
    
    cout << "Do you want to reproduce now the film of the trajectory? \npress 0 for yes, 1 for no \n";
    cout << "If you want only to save it, press 1\n...";
    sssr(risp,"Do you want to reproduce now the film of the trajectory? 0");
    
    cout << "Total time simulation: T_f = " << T_f << endl;
    cout << "insert the time (in sec) between two frames: ";
    cout << "there a frame saved for every " << dt << " seconds";
    sssr(dt_,"insert the time (in sec) between two frames");
    
    if (automatic_!=1)
    {
        
        cout << "Do you want to save the film? \npress 0 for yes, 1 for no ";
        if (automatic_==0) {
            getInput( risp_save);
        }else {
            risp_save=0;
        }
        
        
        double c_max=-1;
        double x_M=-10000,x_m=10000,y_M=-10000,y_m=10000;
        
        // File istruzioni per gnuplot
        ifstream file_c;
        ifstream file_x;
        double c_temp=0;
        double x_temp=0;
        double y_temp=0;
        int int_temp=0;
        c_max=0;
        
        file_c.open(names_files_Ecoli_mod[2].c_str());
        file_x.open(names_files_Ecoli_mod[0].c_str());
        while (!file_c.eof()) {
            file_c >> c_temp;
            file_c >> c_temp;
            c_max=max(c_max, c_temp);
        }
        
        c_max+=.05;
        while (!file_x.eof()) {
            file_x >> x_temp >> y_temp >> int_temp;
            x_M=max(x_M, x_temp);
            y_M=max(y_M, y_temp);
            x_m=min(x_m, x_temp);
            y_m=min(y_m, y_temp);
        }
        x_M+=0.05; y_M+=0.05;
        x_m-=0.05; y_m-=0.05;
        
        file_c.close();
        file_x.close();
        
        cout << "The max ligand concentration is "<< c_max << endl;
        cout << "The trajectory of the bacterium is inside the rectangle" << endl
             << "(x_min,y_min) = (" << x_m <<","<<y_m <<")"<<endl
             << "(x_Max,y_Max) = (" << x_M <<","<<y_M <<")"<<endl;
        
        if ((automatic_==0) && (risp==0)) {
            cout << "Set parameters of the video? press 1 for yes, 0 for no ";
            getInput( risp_par);
        }else {
            risp_par=0;
        }
        
        // set parameters ...
        if (risp_par==1) {
            
            cout << "Max ligand concentration ";
            sssr(c_max, "Max ligand concentration");
            
            cout << "x_Max = ";
            sssr(x_M,"x_Max = ");
            cout << "x_min = ";
            sssr(x_m,"x_min = ");
            cout << "y_Max = ";
            sssr(y_M,"y_Max = ");
            cout << "y_min = ";
            sssr(y_m,"y_min = ");
            
            if (x_M<=x_m || y_M<=y_m) {
                cout << "Error inserting, default parameters ... ";
                x_M=f->max_x+.02;x_m=f->min_x-.02;y_M=f->max_y+.02;y_m=f->min_y-.02;
            }
        }
        
        int salti_= ((floor(dt_/dt)) > (1)) ? (floor(dt_/dt)) : (1) ;
        // Creazione File per Gnuplot
        
        //riproduco solo il filmato
        if (risp==0 && (risp_save!=0)) {
            cout  <<"\nplay video without saving ...\n";
            writeSciptFilmSingle_gif(title, dt, T_f, c_max, x_m, y_m, x_M, y_M, n_data, salti_, names_files_Ecoli_mod, names_file_dyn_mod, risp_save, cont_sim);
            writeSciptLunchFilmSingle_gif(cont_sim, risp_save,names_info_mod[0]);
        }
        //salvo il filmato
        if (risp_save==0){
            writeSciptFilmSingle_gif(title, dt, T_f, c_max, x_m, y_m, x_M, y_M, n_data, salti_, names_files_Ecoli_mod, names_file_dyn_mod, 1, cont_sim);
            writeSciptFilmSingle_gif(title, dt, T_f, c_max, x_m, y_m, x_M, y_M, n_data, salti_, names_files_Ecoli_mod, names_file_dyn_mod, risp_save, cont_sim);
            writeSciptLunchFilmSingle_gif(cont_sim, 1,names_info_mod[0]);
            writeSciptLunchFilmSingle_gif(cont_sim, risp_save,names_info_mod[0]);
        }
        
        if (risp_save==0) {
            lunch_gnuplot(setNameScriptLunchFilm(cont_sim, risp_save).c_str());
        }else{
            lunch_gnuplot(setNameScriptLunchFilm(cont_sim, risp_save).c_str());
        }
        
        //riproduco il filmato se lo ho salvato ...
        if (risp_save==0) {

            string name = names_info_mod[0];
            name.erase(name.end()-3, name.end());
            name = name+"gif";
            // Guardo il filmato
            if (risp==0) {                    
                string command_apngas_ = "open -a firefox "+name;
                system(command_apngas_.c_str());
                
            }
        }
        
    }
}


/*! Write the script for the film of 1D*/

int writeSciptFilmSingle(string title, double dt, double T_f, double c_max, double x_m, double  y_m, double x_M, double y_M, int n_data, int salti_, string *names_files_Ecoli_mod, string &names_file_dyn_mod, int save_, int cont_sim)
{
    
    //save_ == 0 -> salva
    
    std::ofstream file_single_plot;
    
    file_single_plot.open(setNameScriptSingleFilm(cont_sim, save_).c_str());
    
    cout <<"Elaboration and saving of the film ...\n";
    
    if (save_==0) {
        file_single_plot << "nome_out = sprintf('film2D%06d.png',c)" << endl
                         << gnuplotSetTerminalSave_png << endl
                         << "set output nome_out # output=fileout"<< endl;
    }else{
        file_single_plot << "#nome_out = sprintf('film2D%06d.png',c)" << endl
                         << gnuplotSetTerminalPlot << endl
                         << "#set output nome_out"<< endl;
    }
    
    
    file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set title \" Position "<< title << "\" font \",14\""<< endl;
    file_single_plot << "set cbrange [-1:1]" << endl;
    file_single_plot << "set palette defined ( -1 \"#B0B0B0\", 0 \"#FF0000\", 1 \"#0000FF\")" << endl;
    
    file_single_plot << "b_num = b*" << dt << endl;
    file_single_plot << "nome2 = sprintf(\"Filmato Position T = %.1f\",b_num)" << endl
                     <<  "set title nome2" << endl
                     <<  "nome = \""<< names_files_Ecoli_mod[0] <<"\""<< endl  // position
                     << "nome1 = \""<< names_files_Ecoli_mod[2] <<"\""<< endl  // ligand
                     << "nome3 = \""<< names_files_Ecoli_mod[1] <<"\""<< endl  // directions
                     << "set multiplot layout 3,1" << endl;
    file_single_plot << "set xrange ["<<x_m<<":"<<x_M<<"]"<<endl;
    file_single_plot << "set yrange ["<<y_m<<":"<<y_M<<"]"<<endl;
    file_single_plot << "plot nome every ::1::b w l ls 1 title 'X'" << endl;
    file_single_plot << "set yrange [0:"<<c_max<<"]" << endl;
    file_single_plot << "set xrange [0:"<<T_f<<"]"<<endl
                     << "nome2 = \"filmato Ligand \"" << endl
                     <<  "set title nome2" << endl
    // LIGAND
                     << "plot nome1 every ::1::b w l ls 1 title 'c'" << endl
                     << "set yrange [0 : 6.3]"<<endl
                     << "set xrange [0:"<<T_f<<"]"<<endl
                     << "nome2 = \"filmato Direction \"" << endl
                     <<  "set title nome2" << endl
    // TAU
//                     << "plot nome3 u 1:3 every ::1::b w l ls 1 title '\tau_t'" << endl
                     << "set arrow 1 from b_num,0 to b_num,0.2" << endl // nohead identified arrow 1
                     << "plot nome3 w l ls 1 title 'theta'" << endl
                     << "unset arrow 1" << endl
                     << "unset multiplot" << endl
                     << "b=b+"<< salti_ << endl
                     << "c=c+1; " << endl
                     << "if(b<" << n_data +salti_ << ") reread;"<< endl;

    file_single_plot.close();

    return 0;
}


int writeSciptLunchFilmSingle(int cont_sim, int save){
    
//    save == 0 -> save
    
    std::ofstream file_gnu;
    file_gnu.open(setNameScriptLunchFilm(cont_sim, save).c_str());
    file_gnu << gnuplotSetTerminalPlot << endl;
    file_gnu << "b=1;" << endl
             << "c=1;" << endl
             << "load \"" << setNameScriptSingleFilm(cont_sim, save) << "\""<< endl;
    
    if (save!=0) {
        file_gnu << "pause mouse any" << endl;
    }
    file_gnu<< "quit" <<endl;
    file_gnu.close();
    return 0;
}

/*! Set name filmato single*/

string setNameScriptSingleFilm(int cont_sim, int save){
    char buffer[16];
    snprintf(buffer, sizeof(char)*16, "sim%03d-",cont_sim);
    string film_script(buffer);
    film_script+=(save==0)?"-save":"-visual";
    film_script+="_single_film.gnu";
    return film_script;
}

/*! Set name to lunch filmato single*/

string setNameScriptLunchFilm(int cont_sim, int save){
    char buffer[32];
    snprintf(buffer, sizeof(char)*32, "SCRIPT-GNUPLOT-sim%03d-",cont_sim);
    string film_script(buffer);
    film_script+=(save==0)?"-save":"-visual";
    film_script+="_single_film.gnu";
    return film_script;
}

//***********************************************************************************

/*! Write the script for the film of 1D*/

int writeSciptFilmSingle_gif(string title, double dt, double T_f, double c_max, double x_m, double  y_m, double x_M, double y_M, int n_data, int salti_, string *names_files_Ecoli_mod, string &names_file_dyn_mod, int save_, int cont_sim)
{
    
    //save_ == 0 -> salva
    
    std::ofstream file_single_plot;
    
    file_single_plot.open(setNameScriptSingleFilm(cont_sim, save_).c_str());
    
    cout <<"Elaboration and saving of the film ...\n";
    
    if (save_==0) {
        file_single_plot << "#nome_out = sprintf('film2D%06d.png',c)" << endl
        << "#"<< gnuplotSetTerminalSave_png << endl
        << "#set output nome_out # output=fileout"<< endl;
    }else{
        file_single_plot << "#nome_out = sprintf('film2D%06d.png',c)" << endl
        << gnuplotSetTerminalPlot << endl
        << "#set output nome_out"<< endl;
    }
    
    
    file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_single_plot << "set title \" Position "<< title << "\" font \",14\""<< endl;
    file_single_plot << "set cbrange [-1:1]" << endl;
    file_single_plot << "set palette defined ( -1 \"#B0B0B0\", 0 \"#FF0000\", 1 \"#0000FF\")" << endl;
    
    file_single_plot << "b_num = b*" << dt << endl;
    file_single_plot << "nome2 = sprintf(\"Filmato Position T = %.1f\",b_num)" << endl
    <<  "set title nome2" << endl
    <<  "nome = \""<< names_files_Ecoli_mod[0] <<"\""<< endl
    << "nome1 = \""<< names_files_Ecoli_mod[2] <<"\""<< endl
    << "nome3 = \""<< names_files_Ecoli_mod[1] <<"\""<< endl
    << "set multiplot layout 3,1" << endl;
    file_single_plot << "set xrange ["<<x_m<<":"<<x_M<<"]"<<endl;
    file_single_plot << "set yrange ["<<y_m<<":"<<y_M<<"]"<<endl;
    file_single_plot << "plot nome every ::1::b w l ls 1 title 'X'" << endl;
    file_single_plot << "set yrange [0:"<<c_max<<"]" << endl;
    file_single_plot << "set xrange [0:"<<T_f<<"]"<<endl
    << "nome2 = \"filmato Ligand \"" << endl
    <<  "set title nome2" << endl
    << "plot nome1 every ::1::b w l ls 1 title 'c'" << endl
    << "set yrange [0 : 6.4]"<<endl
    << "set xrange [0:"<<T_f<<"]"<<endl
    << "nome2 = \"filmato Direction \"" << endl
    <<  "set title nome2" << endl
    << "set arrow 1 from b_num,0 to b_num,3.14" << endl // nohead identified arrow 1
//    << "plot nome3 u 1:3 every ::1::b w l ls 1 title '\tau_t'" << endl
    << "plot nome3 w l ls 1 title 'theta'" << endl
    << "unset multiplot" << endl
    << "unset arrow 1" << endl
    << "b=b+"<< salti_ << endl
    << "c=c+1; " << endl
    << "if(b<" << n_data +salti_ << ") reread;"<< endl;
    
    file_single_plot.close();
    
    
    return 0;
}

int writeSciptLunchFilmSingle_gif(int cont_sim, int save, string name_){
    
    string name = name_;
    name.erase(name.end()-3, name.end());
    name = name+"gif";
    
    std::ofstream file_gnu;
    
    file_gnu.open(setNameScriptLunchFilm(cont_sim, save).c_str());
    
    //    if (risp==0 && (risp_save!=0)) {
    file_gnu << gnuplotSetTerminalSave_gif << endl;
    file_gnu << "b=1;" << endl
             << "c=1;" << endl
             << "set output \""<< name << "\""<< endl
             << "load \"" << setNameScriptSingleFilm(cont_sim, save) << "\""<< endl
             << "set output" << endl;
    
    if (save!=0) {
        file_gnu << "pause mouse any" << endl;
    }

    
    file_gnu<< "quit" <<endl;
    
    file_gnu.close();
    
    return 0;
}
