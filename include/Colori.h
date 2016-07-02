//
//  Colori.h
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

/**
 * Define font for the terminal: for windows nothing happens, no colors, no bold .
 */

#ifndef COLORS_h
#define COLORS_h


#include "GlobalVariables.h"

#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)

//#define RESET   ""
//#define BLACK   ""                  /** Black */
//#define RED     ""                  /** Red */
//#define GREEN   ""                  /** Green */
//#define YELLOW  ""                  /** Yellow */
//#define BLUE    ""                  /** Blue */
#define MAGENTA ""                  /** Magenta */
#define CYAN    ""                  /** Cyan */
#define WHITE   ""                  /** White */
//#define BOLDBLACK   ""       /** Bold Black */
//#define BOLDRED     ""       /** Bold Red */
//#define BOLDGREEN   ""       /** Bold Green */
//#define BOLDYELLOW  ""       /** Bold Yellow */
//#define BOLDBLUE    ""       /** Bold Blue */
#define BOLDMAGENTA ""       /** Bold Magenta */
#define BOLDCYAN    ""       /** Bold Cyan */
#define BOLDWHITE   ""       /** Bold White */


// ConsoleColor.h


#include <windows.h>

inline std::ostream& RESET(std::ostream &s)
{ 
	if (!colors)
		return s;

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

inline std::ostream& BLUE(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
                            |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& BOLDBLUE(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
                            |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& RED(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& BOLDRED(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& GREEN(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& BOLDGREEN(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& YELLOW(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& BOLDYELLOW(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& BLACK(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

inline std::ostream& BOLDBLACK(std::ostream &s)
{ 
	if (!colors)
		return s;


    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

struct color {

    color(WORD attribute):m_color(attribute){};
    WORD m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits>&
operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c)
{ 

    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,c.m_color);
    return i;
}

// Copyleft Vincent Godin


#else

//#define RESET   "\033[0m"
////#define RESET "\033[47;37m"
////#define BLACK   "\033[30m"                  /** Black */
//#define BLACK   ""                  /** Black */
//#define RED     "\033[31m"                  /** Red */
//#define GREEN   "\033[32m"                  /** Green */
//#define YELLOW  "\033[33m"                  /** Yellow */
//#define BLUE    "\033[34m"                  /** Blue */
//#define MAGENTA "\033[35m"                  /** Magenta */
//#define CYAN    "\033[36m"                  /** Cyan */
//#define WHITE   "\033[37m"                  /** White */
////#define BOLDBLACK   "\033[1m\033[30m"       /** Bold Black */
//#define BOLDBLACK   ""       /** Bold Black */
//#define BOLDRED     "\033[1m\033[31m"       /** Bold Red */
//#define BOLDGREEN   "\033[1m\033[32m"       /** Bold Green */
//#define BOLDYELLOW  "\033[1m\033[33m"       /** Bold Yellow */
//#define BOLDBLUE    "\033[1m\033[34m"       /** Bold Blue */
//#define BOLDMAGENTA "\033[1m\033[35m"       /** Bold Magenta */
//#define BOLDCYAN    "\033[1m\033[36m"       /** Bold Cyan */
//#define BOLDWHITE   "\033[1m\033[37m"       /** Bold White */


inline std::ostream& RESET(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[0m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BLACK (std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[0m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& RED(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<      "\033[31m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& GREEN(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[32m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& YELLOW(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<   "\033[33m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BLUE(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<     "\033[34m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& MAGENTA(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<  "\033[35m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& CYAN(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<     "\033[36m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& WHITE(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[37m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDBLACK(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[0m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDRED(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<      "\033[1m\033[31m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDGREEN(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[1m\033[32m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDYELLOW(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<   "\033[1m\033[33m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDBLUE(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<     "\033[1m\033[34m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDMAGENTA(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<  "\033[1m\033[35m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDCYAN(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<     "\033[1m\033[36m";
		my_mutex.unlock();
	}
	return s;
}

inline std::ostream& BOLDWHITE(std::ostream& s){
	if (colors){
		my_mutex.lock();
		std::cout <<    "\033[1m\033[37m";
		my_mutex.unlock();
	}
	return s;
}

#endif

#endif
