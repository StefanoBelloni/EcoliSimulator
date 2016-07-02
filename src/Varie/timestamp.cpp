//
//  timestamp.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <ctime>
using namespace std;

void timestamp ( ){
# define TIME_SIZE 40
    
    static char time_buffer[TIME_SIZE];
    const struct std::tm *tm_ptr;
    //size_t len;
    std::time_t now;
    
    now = std::time ( NULL );
    tm_ptr = std::localtime ( &now );
    
//    len = std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);
    std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);
    std::cout << time_buffer << "\n";
    
    return;
# undef TIME_SIZE
}
