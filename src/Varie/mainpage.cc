/*! \mainpage INTRODUCTION
 *
 * \section intro_sec Introduction
 
 The program <tt>EcoliSimulator</tt> is a command-line based simulator of different models for Ecoli, which produce graphical, numerical and <tt>Statistical</tt> analysis of the result obtained.<br>
 The program is completely written in c++: and use <b>gnuplot</b> and/or <b>Matlab</b> as a graphical toolbox.<br> The different models are implemented to give the maximal freedom to the user to modify parameters and and try to analyze the output.<br>
 It is design to be usable in a step-by-step (the duration of the simulations are estimated) or a pre-set mode and produces a Latex file where all the informations about the simulations and output are collected in a systematic, an hopefully, coherent and readable version.<br>
It is possible to use more then one thread in order to perform the simulations in parallel.
 
 \section req_sec Requirements and Installation
 
 \subsection req Requirements
 
 In order to run all the functionalities of the program one needs that on the computer are installed
 
 - <b>Required Programs:</b>
 
    - <b>gnuplot</b> - <tt>is a portable command-line driven graphing utility for Linux, OS/2, MS Windows, OSX, VMS, and many other platforms. The source code is copyrighted but freely distributed</tt> it is important that the option of <tt>set terminal pngcairo</tt> and or <tt>set terminal gif</tt> is available: If you don't have the gif terminal, it is necessary to have the program <tt>apngasm</tt> (see below) to produce the film of the evolution of the density distribution or the single bacterium tracking.
    - <b>.gif or .png format reader</b> any program able to open .png files with multiple layers. In order to see while the program is running the video it is recommended to have installed <b>Mozilla Firefox</b> -  (known simply as Firefox) is a free and open-source web browser.
    - <b>program for LateX formats</b> In order to read and visualize the report it is necessary to have installed a program which read LateX language.
 - <b>Optional Programs:</b>
    - <b>apngasm</b> - Creates highly optimized Animated PNG files from PNG/TGA image sequences.
    - <b>Matlab</b> - Commercial Software produced by The MathWorks base on a high-level language and interactive environment. <br>
 

 
 \subsection Inst Installation
 
 To instal the program you can use the Makefile or cmake (or "by hand")
 NOTE: In order to install automatically the External programs it is raccomanded to have installed
 
 - GNU make (https://www.gnu.org/software/make/)
 - curl (https://curl.haxx.se/)
 - cmake (https://cmake.org/)
 - a program to decompress .zip files. For example, for unix unzip, for windows 7zip (http://www.7-zip.org/)
 - c++ compiler (g++) with support for c++11
 
 If you are using different programs to achive these tasks, you can modify the definitions in the Makefile.
 
 - open a terminal and navigate to the folder EcoliSimulator_0.0.1a, which contains src/ and /include.
 
    -<b>Makefile</b>: You have many options according to what you want install. Notice that the Makefile does not check if a program is already installed.
 
        - Install only EcoliSimulator:
            type make
                >:EcoliSimulator stefanobelloni$ make
            to process the Makefile
            it might happend that you need to type make.exe or the complete path to "make" or 
            mingw32-make.exe according to your needs.
            NOTE: If you use the Makefile and the compiler g++ is not in the PATH variable,
            redefine the variable CC accordingly, for example if the compiler you want to use is g++ and
            it is inside the folder C:\Dev-cpp\Ming64\bin\g++.exe, substitute the definition of the variable CC as follows:
                CC = C:\Dev-cpp\Ming64\bin\g++.exe
 
        - Install gnuplot
            type make gnuplot
                >:EcoliSimulator stefanobelloni$ make gnuplot
            For windows and Os X the installation of gnuplot will not be invasive, in the sense that
        - in Windows gnuplot is installed inside the bin folder of EcoliSimulator
        - in Os X, when you drag gnuplot in the Application folder the path to the program will be
            /Applications/Gnuplot.app/Contents/Resources/bin/
            NOTE: this version on gnuplot does not have the terminal .gif.
            You need apngasm and tell the program to use it with the option --apngasm
 
        - Install apngasm (binary)
            type make apngasm
                >:EcoliSimulator stefanobelloni$ make apngasm
 
        - Intsall apngasm from source (you need cmake) This will create the executible in the bin folder.
                >:EcoliSimulator stefanobelloni$ make apngasm_src
 
        - To install along with EcoliSimulator also gnuplot and apngasm.
                >:EcoliSimulator stefanobelloni$ make install
 
        - To show the different options to build the program.
                >:EcoliSimulator stefanobelloni$ make help
 
 
    -<b>cmake</b>: This will only build EcoliSimulator in the bin folder.
 
        - create a folder (i.e. build),
                >:build stefanobelloni$ mkdir build
        - move inside it
                >:build stefanobelloni$ cin build;
        - type:
                >:build stefanobelloni$ cmake ..
        - then type
                >:build stefanobelloni$ make
        - you can use the options of cmake to customize the installation path.
 
    -<b>compile by hand:</b>
 
        - create a folder (for example be it bin)
                >:build stefanobelloni$ mkdir bin
        - go inside it
                >:build stefanobelloni$ cin bin
        - type
                g++ -std=c++11 -I../include -Wall -o EcoliSimulator ../src/*.cpp ../src/* /*.cpp
            (instead of g++, use the compiler you prefer ...)
 
 By default the Makefile and the cmake will create a bin folder, where the executable can be found and a build folder where the .o objects are saved.
 
 \section run_sec Running the Program
 \subsection Lunch the Program
 The program can be lunch trough the terminal/DOS giving additional parameters to the program,  in the following way:
 
    -<b>Available options</b>:
        
        --matlab=x  .............................  set version matlab 'x'
        --gnuplot=y .............................  set path to gnuplot 'y'
        --file ..................................  read the file 'EcoliRisposte.Ecoli' to perform the simulations
        --file=pathtofile .......................  read file given by pathtofile.
                                                  (if the file is where the executable is run, type only the name)
        --clear .................................  clear all possible trash data
        --qclear ..................................  clear all possible trash data and exit
        --reset ..................................  rest cleaning all files and settings
        --script .................................  there's no initial page, useful if you run a script
        --j=n   ..................................  max number of cores to use: default is half of the available cores
        --nocolors ............................... it uses the default colors of the terminal.
                                                   use it, if you have some strange colors for the terminal, you might not be
                                                   able to read everything ... (not strange is white or black)
        --apngasm=x .............................. x is the path to apngasm (with / or \\) if apngasm is in the current
                                                 directory type:
                                                 --apngasm=./ for Unix , just --apngasm= on Windows
                                                 if x is set to no, then the video is not create with apngasm ('.png' file),
                                                 but as a '.gif' file.
                                                 --apngams tells to create multilayer '.png' file.
                                                 NOTE: The defoult (for the first lunch) is '.gif' file.
        --clclog ................................. clear the file Ecoli.LogEcoli.
 
 \section rout_sec Routines
 
 \subsection {Mode of Use}
 The program allows 3 different mode of use:
 
 
 - <tt>Demo Version</tt>: can be used as a validating routine.
 - <tt>Programmable Version</tt>: The user can program the sequence of the simulations to be performed as well as the parameters and options, for example "the creation of a LateX/pdf Document as summary of the simulations performed". The data are displayed via <tt>gnuplot</tt>. You can also read the parameters and MODE of simulation from a file. You can create yourself a file, or give the parameters to create a file.
 - <tt>Step-by-Step Version</tt>: in this Version the user decide step by step the options and Simulations and can visualize the results at the end of every simulating step.  In this Mode it is possible to use Matlab to analyze the data.
 - <tt>Settings - 121</tt> In this version it is possible to test if the program gnuplot, Matlab, apngasm, (LateX interpreter) are correctly installed and change the path where the program looks for these programs.
 
 
 \section stat_sec Statistical Analysis and Simulations
 
 It is possible to choose between three different options:
 
 
 - <b>Simulation</b>: to perform the simulation of the available models and produce a general analysis (see below)
 - <b>Fit parameter model(s)</b>: to fit the parameters of the models(s) from the given data
 - <b>Simulation and Statistical Analysis</b>: to perform first the simulation of the chosen models and afterwords analysis them to fit the parameters, without <tt>a priori</tt> knowing the model simulated.
 
 
 \subsection tip_sim Type of Simulations
 It is possible, afterwords decide which type of simulation the User want to perform. There are 2 alternatives:
 
 - <b>Simulation independent population</b>: produce the simulation of a single or a population of bacteria swimming in a solution of Ligand concentration, where the concentration evolves according to a function (that the user chooses) without being influence by the population of bacteria.
 - <b>Simulation of a population interacting with the ligand</b>: produce the simulation of a single or a population of bacteria swimming in a solution of Ligand concentration. The evolution of the Ligand concentration follows a Diffusion function with sink and source influenced by the bacteria population.
 
 \subsection mod_sec Models Available
 
 For the options <tt>Simulation independent population</tt> and <tt>Simulation of a population interacting with the ligand</tt> it is possible to choose among 9 different models for the dynamic of the bacteria.
 
 - [a] <tt>Celani Vergassola Memory Kernel</tt> <b>CM10</b>;
 - [b] <tt>Molecular level Implementation</tt>: Implementation of the signaling pathway in <b>CSV11</b>.
 - [c] <tt>Othmer et al. Model</tt> ;
 
 
 For every model it is possible to chose between three different forms of the run distribution, i.e. exponential, inverse-gaussian or exponential-inverse gaussian. You have the possibility to select and modify a great variety of parameters.
 
 
 
 \subsection clas_sec Ecoli Classes
 
 The program model the different Models in classes, that are hierarchically organized.
 The base class is <b>E_coli</b>, which defines the common variables and implements (as <b>virtual</b> when needed) the basic functions to produce the simulation of the movement of an Ecoli (see {\bf figure \ref{EcoliClass}}.<br>
 The program is versatile and easy adaptable to include new models: it is only needed to implement the interface of E. coli concerning internal dynamic and visualization (9 functions).<br>
 The names of the derived classes have the following feature:
 - name_rNameDistribution_tNameDistribution
 where name is the <tt>identification name</tt>, <tt>rNameDistribution</tt> means that the <tt>run</tt> distribution follows, in the stationary case the Distribution <tt>DistributionName</tt>. Similar for <tt>t</tt> where is meant the distribution of the tumble, for example <b>r_IG</b> means the <tt>run</tt> distribution in the steady state follows a Inverse gaussian distribution.
 
 
 - <b>Exp</b>: Exponential distribution
 - <b>IG</b>: Inverse Gaussian Distribution
 - <b>ExpIG</b>: Compound Exponential-Inverse Gaussian Distribution
 
 
 \subsection sub_cv CV_rExp_tExp Class
 The fist Model is taken from <b>CM10</b>, whose identification name is <b>CV_rExp_tExp</b>. The main feature is the Variable \f$Q(t)\f$ which take into account the memory of the bacterium to build the <tt>rate function</tt> of the jump process associated to the <tt>runs</tt>. The barrier for the <tt>runs</tt> is a random variable exponentially distributed\footnote{with mean equal to 1}.
 
 \f{equation}{
 \frac{d}{dt}m_{k}=-\nu\cdot m_{k} + \delta^{k}_{0} c + (1-\delta^{k}_{0})k\cdot m_{k-1},
 \f}
 \f{equation}{
 \mathcal{Q}(t)=\sum_{k=1}^{k_{N}}\beta_{k}\nu^{k+1}m_{k}(t)
 \f}
 
 \subsection sub_cv1 CV_rExpIG_tExp Class
 This class extend the class <b>CV_rExp_tExp</b> (<b>CV_rExpIG_tExp : public CV_rExp_tExp</b>), and the main feature is characterized by the fact that the evolution of the <tt>rate function</tt>, which depends also on \f$Q(t)\f$,  is not a deterministic process, but a <tt>Diffusion process</tt>\footnote{Solution of a SDE}, i.e.
 
 \f[
 d\Lambda(t)=\lambda(Q(t))dt+\sigma(Q(t))dW(t)
 \f]
 
 and the barrier for the <tt>runs</tt> is a RV exponentially distributed.
 
 \subsection sub_cv2 CV_rIG_tExp Class
 This class extend the class <b>CV_rExp_tExp</b> (<b>CV_rIG_tExp : public CV_rExp_tExp</b>), and the main feature is characterized by the fact that the evolution of the <tt>rate function</tt>, which depends also on \f$Q(t)\f$,  is not a deterministic process, but a <tt>Diffusion process</tt>\footnote{Solution of a SDE}, i.e.
 
 \f[
 d\Lambda(t)=\lambda(Q(t))dt+\sigma(Q(t))dW(t)
 \f]
 
 
 and the barrier for the <tt>runs</tt> is a deterministic value
 
 \subsection Molecular_rx_ty
 This model is taken from <b>CSV11</b>, and implement the <tt>mean field</tt> approximation for the molecular-base model of the internal dynamic of the bacterium. The generalization to the Inverse gaussian and exponential-inverse gaussian is straightforward.
 
 The chemotactic transduction pathway is conveniently modeled by the following set of mean-field equations:
 \f{align}{
 a&=G(m,L),\\
 \frac{d}{dt}m&=F(a,m),\\
 \frac{d}{dt}y&=k_a a(1-y)-k_zy,\\
 \frac{d}{dt}p_r&=\frac{1-\frac{p_r}{h(y)}}{\tau_t}.
 \f}
 
 The detailed expressions for the functions that appear above are
 \f{align*}{
 G(m,L)&=\frac{1}{1+e^{f(m,L)}},\\
 f(m,L)&=n_a\alpha_m(m_0-m)+n_a\ln\frac{1+\frac{L}{K_{off}}}{1+\frac{L}{K_{on}}},\\
 F(a,m)&=k_r[\textrm{CheR}](1-a)\frac{M-a}{M-m+K_R}-k_b[\textrm{CheB}]a\frac{m}{m+K_B};\\
 h(y)&=\frac{1}{1+\Big(\frac{y}{y_0}\Big)^H}.
 \f}
 
 
 \subsection EO_rx_ty
 This model is taken from <b>OthmerErban</b>: the function for the internal dynamics are those reported in \ref{OthmerCartoon} in {\bf Chapter \ref{Semplificato}}. The generalization to the Inverse gaussian and exponential-inverse gaussian is performed straightforward.
 
 \f{equation}{
 \begin{aligned}
 \frac{d}{dt}y_{1}(t)&=\frac{G(c(t,x))-(y_{1}+y_{2})}{\tau_{a}}\\
 \frac{d}{dt}y_{2}(t)&=\frac{G(c(t,x))-y_{2}}{\tau_{e}}
 \end{aligned}
 \f}
 
 \section sec_LIg Ligand evolution
 
 In case the program mode selected is <tt>population interacting with the ligand</tt> the Ligand concentration follows the following equation:
 
 \f[
 \frac{\partial}{\partial t}c(t,x,y)=D_c\Delta_{(x,y)}c(t,x,y)-K_c c(t,x,y)+K_p\sum_{i=1}^{n_c}\delta_{(t,x,y)}(p^i_b(t,x,y))
 \f]
 
 
 where \f$p^i_b\f$ is the position of the bacterium number \f$i\f$.
 
 The simulation is performed using an ADI method where the boundary conditions are of Neumann's type. The method is as follows:
 Let \f$U=(q_{i,j})_{i=1...n_x,j=1...n_y}\f$ be the matrix of the mesh for the rectangular domain and \f$Q\f$ the matrix of the source. Let \f$L_x^{n_x}\f$ be the Laplacian-matrix is the \f$x\f$ direction, it is a \f$n_x\times n_x\f$ matrix  (similar for \f$y\f$), then using the Thompson's Algorithm for the resulting tridiagonal system we solve the PDE in two steps:
 
 \f[
 L^{n_x}_x\otimes U = (U\otimes L^{n_y}_y)^T +\frac{dt\cdot Q}{2}
 \f]
 
 
 \f[
 L^{n_y}_y\otimes U^T = (U^T\otimes L^{n_x}_x)^T+\frac{dt\cdot Q^T}{2}
 \f]
 
 
 where with \f$\otimes\f$ we indicate the <tt>matrix</tt> product, and with \f$Q^T\f$ the transpose of \f$Q\f$.
 
 
 \section sec_Analyzis General Analysis
 
 \subsection file_sec Management Outputs and Files
 
 Since the data recorded from every simulation can reach an enormous number\footnote{For Example, simulating a single bacterium (Celani Vergassona inverse Gaussian distribution Approach) for 1000 sec. with time step of 0.01 sec. produces the following average of data:
 
 
 - Positions and sign gradient: 300000 doubles
 - Ligand concentration: 100000 doubles
 - Direction: 100000 doubles
 - Jumps: 1250 runs times and 1250 tumbles times.
 - Internal Dynamic 100000 doubles.
 
 the data are saved in .dat files, whose name are univocal determined for every run of the program and are made up of 3 different parts, Prefix-MittlePart-Suffix, i.e.
 
 
 - Prefix: <tt>sim\%03d-</tt>, where in \%03d is stored the number of the simulation in the current subsection
 - MittlePart: <tt>type_name</tt>, according to which kind of data it contains, for example <tt>Ecoli_info</tt>, <tt>run_t</tt>, <tt>theta</tt> etc.
 - Suffix <tt>\%d-\%d</tt> made of two numbers, the first one the Type of Simulation, the second the Type of Model.
 
 The same structure is use for the name of the files of the images and video produces via <tt>gnuplot</tt>
 
 At the end of every simulation the following files are created in a folder (default in the folder where the executible is run, but you can change it in the setting menu), whose name is as follows:<br>
 
 - E_coli-Day-Month-Year-hour-minute-seconds-PM/AM
 
 and for DEMO version:<br>
 
 - DEMO_E_coli-Day-Month-Year-hour-minute-seconds-PM/AM
 
 
 Single bacterium based simulation:
 
 
 - Video with the evolution single trajectory, Ligand concentration
 - Picture for the analysis of runs and tumbles
 - Evolution internal Dynamic
 - Overview Trajectory, Ligand concentration
 
 Large population based simulation:
 
 
 - Video with the evolution of Density and the Ligand concentration
 - Analysis Runs and Tumbles
 - Analysis trajectory and speed barycentre
 
 All the data and the scripts (to save and to visualize) used to generate the pictures are saved in a subfolder odf the folder of the summary colled DATA.
 
 \subsection file_sec Management Basic Analysis
 
 In this section we present the basic analysis (that is as well a Statisical analysis) that the program provide.
 
 -  We estimate the density function \f$p(t,x)dx\f$ via binning in a histogram, i.e.<br>
 let divide the area of the experiment into a grid: we call the rectangle in position \f$i\f$ along the \f$x\f$-axis and \f$j\f$ along the \f$y\f$-axis \f$\Delta x_{i,j}\f$. We denote with \f$N\f$ the number of particles in the simulation and with $x_{k}(t)$ the position of the particle \f$k\f$ at time \f$t\f$, we compute the histogram of the density function as follows
 \f[
 \mathcal{H}(t,x):=\sum_{i,j}\sum_{k=1}^{N} \mathbf{1}_{\{x_{k}(t)\in \Delta x_{i,j}\}}\cdot \mathbf{1}_{\{x\in \Delta x_{i,j}\}};
 \f]
 We do not use more sophisticated estimation since we perform no comparison with continuous model. In case such a comparison should be performed, we should employ the kernel density estimation technique with more appropriate kernel functions.
 
 - We perform the analysis of the barycenter of the population, i.e.
 \f[
 \mathcal{B}(t):=\frac{1}{N}\sum_{k=1}^{N}x_{k}(t);
 \f]
 its speed in direction \f$\vec{e_{j}}\f$, i.e.
 \f[
 \mathcal{V}_{j}(t):=\frac{1}{N}\sum_{k=1}^{N}\frac{\langle x_{k}(t+\delta t) - x_{k}(t), \vec{e}_{j} \rangle}{\delta t};
 \f]
 as well as the calculation of the mean square displacement
 \f[
 \langle r^2(\tau)\rangle=\lim\limits_{N\rightarrow\infty}\frac{1}{N}\cdot\sum\limits_{n=1}^N\left({x}_n(\tau)-{x}_n(0)\right)^2,
 \f]
 and the simple linear regression. In the present case it is appropriate to force the regression line to pass through the origin, i.e  \f$\langle r^2(\tau)\rangle = \beta\cdot t\f$.
 
 \subsection sec_Stat Fit parameters of the models
 
 The program performs the identification of the parameters of the model starting from the data.
 The program allows to analyze data with the following format:
 
 The data recoded are:
 \f[
 t_j\quad c_{\tau^r}\quad c_{\tau^t}\quad \tau^r\quad \tau^t
 \f]
 
 where \f$t_j\f$ is the time of the beginning of the \f$j\f$-th run,  \f$c_{\tau^r}\f$ is the concentration recorded at time of the end of the run \f$j\f$, \f$c_{\tau^t}\f$ the beginning end of the tumble \f$j\f$ and \f$\tau^r\f$ are (resp. \f$\tau^t\f$) the duration of the run (resp. tumble) \f$j\f$-th.
 
 Once the program identifies which kind of data are to be analyzed, it proceed trying to find which is the best model fitting the data.
 
 
 - [step  0] Construct a vector of classes <b>Q_tau_stat</b> whose dimension depends on the maximm vale of the index \f$Q\f$ and the discretization of the interval \f$[\min Q:dQ:\max Q]\f$ with step size \f$dQ\f$. Each class summarized the statistical moments and data from the data set.
 
 - [step 1] it reads through the file all the entries,
 - [step 2] calculate the \f$Q\f$-index from <b>CM10</b> and all the corresponding statistics.
 - [step 3] Plot the calculated data.
 - [step 4] Calculate the empirical rate-function using a piecewise linear model in \f$Q\f$
 - [step 5] Calculate the weighted-mean square approximation (one for positive \f$Q\f$, and one for negative value of \f$Q\f$)
 - [step 6] Produced a Kolmogorov-Smirnov test using the idea in <b>BrownIG</b> for the goodness of fit of point process
 - [step 7] Iterate the steps [0] - [6] adapting the discretization of the variable \f$Q\f$ and the maximum and minimum value that it can assume.
 
 \section add_new Note to Add new Models
 
 If you want to add new model you have to modified also the following function
 
 - Statistical_Analysis(string name_file_dati, string name_info_file, vector<int> which_compare, int n_compare, int &cont_gen_sim, string &versione_Matlab, int n_c)
 - Set_Stocasticita(vector<int> &which_compare ,int statisticita)
 - create_bacteria_vector(vector<E_coli*> &batteri)
 - initialization_interacting_population(int tipo_simulazione, vector<E_coli* > *batteri_int, int n_c)
 
 It is recommended that you implement the following virtual function when subclassing E_coli:
 
 Functions that are likely to be reimplemented
 
 - E_coli::change_par() implement the way you interact with the parameters of your model
 - virtual void E_coli::reset_par(); This is a helper function, to be sure you reset the parameters. You can implement it in the constructor of the new class
 - virtual void E_coli::stationary_dyn(double dt, std::vector<double> &m0, int changed_pos); implement the stationary distribution
 - virtual int E_coli::agg_dyn(double dt, double t); implement the condition that make you pass from tumble to run and vice versa
 - virtual void E_coli::agg_dyint(double dt, double t); implement you're internal dynamic model
 - virtual void E_coli::save_dyn(ofstream &file, double t); save which internal variable you want to analyse
 - virtual void E_coli::print_info(std::ofstream &file_save); call the base function and add what is new
 - virtual void E_coli::gnuplot_response(string names_info_mod, int save_, int con_gen_sim); you can you one of the two implementation for Exp or IG distribution
 
 Functions that are already implemented somewhere for most of the porposes
 
 - virtual double E_coli::reset_barrier(); you can you one of the two implementation for Exp or IG distribution
 - virtual double E_coli::reset_barrier_t(); you can you one of the two implementation for Exp or IG distribution
 - virtual void E_coli::s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect);  you can you one of the two implementation for Exp or IG distribution
 - virtual void E_coli::gnuplot_single add the features you want to display, such as the internal variable dynamics
 
 Function that till now have been used only in the base form
 
 - virtual void E_coli::produce(Funz_C* f_i, double dt); This function is virtual, but all model use the basic function
 - virtual void E_coli::gnuplot_single_film This function is virtual, but all model use the basic function
 - virtual void E_coli::gnuplotFunzInternalDynalmic(string buffer, int save_,  int con_gen_sim); it is not yet implemented
 
 \section biblio Bibliography
 
 - When it is said Vergassola Celani Model, sometime as [SM10] is intended
 - Celani, Antonio, and Massimo Vergassola. "Bacterial strategies for chemotaxis response." Proceedings of the National Academy of Sciences 107.4 (2010): 1391-1396.
 - When it is said Vergassola Shimitzu Celani sometimes as [CSV11] is intended
 - Celani, A., T. S. Shimizu, and M. Vergassola. "Molecular and functional aspects of bacterial chemotaxis." Journal of Statistical Physics 144.2 (2011): 219-240.
 - Othmer Model means the cartoon model in one of the following:
 - Erban, Radek, and Hans G. Othmer. "From signal transduction to spatial pattern formation in E. coli: a paradigm for multiscale modeling in biology." Multiscale Modeling \& Simulation 3.2 (2005): 362-394.
 - Xue, Chuan, and Hans G. Othmer. "Multiscale models of taxis-driven patterning in bacterial populations." SIAM journal on applied mathematics 70.1 (2009): 133-167.
 - Similar publications
 
 */


/* This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 02110-1301, USA. */
