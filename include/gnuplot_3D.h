//
//  gnuplot_3D.h
//  EColi_2.4
//
//  Created by Stefano Belloni on 22/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//


#include <vector>
#include "Funz_C.h"


double histogram_3D_gnuplot(double max_x, double max_y, double min_x,double min_y, int n_dx, int n_dy, double dx, double dy, std::vector<std::vector<double> > x,std::vector<std::vector<double> > y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, double &maxC, std::string name_file);
double histogram_3D_gnuplotV2(double max_x, double max_y, double min_x,double min_y, int n_dx, int n_dy, double dx, double dy, std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, double &maxC, int MaxDom, int cont_sim, std::string name_file);
double histogram_3D_gnuplotV2MultiThread(double max_x, double max_y, double min_x,double min_y, int n_dx, int n_dy, double dx, double dy, std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, double &maxC, int MaxDom, int cont_sim, std::string name_file);

void filmato_3D_gnuplot(std::string file_info[], double max_x, double max_y, double min_x,double min_y, double max_z, int dim_col_t, Funz_C *f, int cont_gen_sim, double MaxC);
void baricentro_plot(std::string name,std::vector<std::vector<double> > &x_t,std::vector<std::vector<double> > &y_t,int n_c,int dim_col_t, int cont_gen_sim = 0);
void gnuplot_large_population_interacting(std::string file_info[], std::string name_dyn, double T_f, int n_c, int dim_col_t, std::string names, Funz_C *f, int cont_gen_sim, double maxC);
void lunch_gnuplot(std::string name_file_gnu);
void Histogram_Dynamic(std::string name, std::string name_dynamic, int sim_cont);
void funz_clear();
int percSignFunzC(std::vector< std::vector<double> > c_t, int n_c, int dim_col_t, std::string nameInfo);


