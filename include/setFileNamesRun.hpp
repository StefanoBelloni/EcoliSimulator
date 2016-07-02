//
//  setFileNamesRun.hpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 19/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef setFileNamesRun_hpp
#define setFileNamesRun_hpp

#include <stdio.h>
#include <iostream>

namespace tipoHistGraph {
    enum scale{
        LOG = 0,
        NOT_LOG
    };
    enum tipo{
        RUN = 1,
        TUMBLE = 2
    };
}


std::string setFileNamesRun(int save_, int frac_, int run, int cont_sim);

#endif /* setFileNamesRun_hpp */
