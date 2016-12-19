//
//  GlobalRandomVariables.h
//  EcoliSimulator_0.0.1a
//
//  Created by Stefano Belloni on 26/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include <random>
#include <vector>

#ifndef NO_M_THREAD
#include <thread>
#endif


/*! \brief this struct is used to generate random variables for the multi-thread case
 */

struct randomObj{

    std::vector<bool> random_engines_seeded;
    
    std::vector<std::mt19937_64> random_engines;
    
    std::vector<std::mt19937_64> random_engine_saved;
    
    std::vector<std::mt19937_64> random_engines_theta;
    std::vector<std::mt19937_64> random_engines_theta_saved;
    
    std::vector<std::mt19937_64> random_engines_barrier;
    std::vector<std::mt19937_64> random_engines_barrier_saved;
    
    std::vector<bool> random_engines_seeded_theta;
    std::vector<bool> random_engines_seeded_barrier;

    //    std::vector<bool> random_engines_seeded_saved;
    
};

/** \brief this global variable is used to keep track of the seeds (random engine)
 */

extern randomObj rnd_ecoli;

#ifndef NO_M_THREAD
void seedRandomObj(int n_this_thread, std::thread::id hash_code);
#else
void seedRandomObj(int n_this_thread, long hash_code);
#endif
