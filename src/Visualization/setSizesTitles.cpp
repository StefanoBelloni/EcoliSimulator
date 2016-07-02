//
//  setSizesTitles.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 19/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "setSizesTitles.hpp"

std::string setSizesTitles(int dim, int save_){
    
    int size=20;
    char buffer[24];
    if (save_==sizeTitle::NO_SAVE) {
        
        switch (dim) {
            case sizeTitle::SMALL:
                size =10;
                break;
            case sizeTitle::MEDIUM:
                size =15;
                break;
            case sizeTitle::LARGE:
                size =20;
                break;
            case sizeTitle::HUGE_:
                size =25;
                break;
                
            default:
                size =15;
                break;
        }
        
    }else{
        switch (dim) {
                
            case sizeTitle::SMALL:
                size =20;
                break;
            case sizeTitle::MEDIUM:
                size =30;
                break;
            case sizeTitle::LARGE:
                size =40;
                break;
            case sizeTitle::HUGE_:
                size =50;
                break;
                
            default:
                size =30;
                
                
        }
        
     
    }
    
    snprintf(buffer, sizeof(char) * 24, " font ',%d'", size);
    return std::string(buffer);
        
        
    }