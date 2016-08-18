#include <iostream>
#include "GlobalVariables.h"
#include "Colori.h"

/**
 * This function clear the terminal (different command according to the system)
 */

void funz_clear(){
    
//    #if defined(WIN32) || defined(WIN64)
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
        const char* clear_command = "cls";
//        std::cout << "WINDOWS !!!!!!!!!!!!!!!!!! 32\n";
    #else
        const char* clear_command = "clear";
    #endif

    if (automatic_!=2) {
//        system(clear_command);
    }
    
    system(clear_command);
    
}


void funz_clearAll(){
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    const char* clear_command = "cls";
    //        std::cout << "WINDOWS !!!!!!!!!!!!!!!!!! 32\n";
#else
    const char* clear_command = "clear";
#endif
    
    system(clear_command);
    
}

/*! get an input from cin and check if the type is the same as the template argument, if not, the user is asked to reinsert the value.*/
template<typename T>
void getInput(T &risposta){
    
    while(!(std::cin >> risposta)){
        std::cout << BOLDRED << "Invalid value.\n" << RESET ;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter again: ";
    }
}

template<>
void getInput(std::string &risposta){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline (std::cin,risposta);
}
// alternative version for string:
/*
void getInput(std::string &risposta){
    char input[100];
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.getline(input,sizeof(input));
	risposta=std::string(input);
}*/
template void getInput(int &risposta);
template void getInput(double &risposta);
template void getInput(bool &risposta);
template void getInput(std::string &risposta);
