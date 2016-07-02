//
//  Cancell_histFile.cpp
//  Ecoli_4.1.4
//
//  Created by Stefano Belloni on 26/10/15.
//  Copyright © 2015 Stefano Belloni. All rights reserved.
//

#include <iostream>

using namespace std;

/** function that delete the file film3Dc%i.dat used to plot the 3D histogram and the script to call gnuplot
 * @param n_frame_max: number file to be delated: from ilm3Dc1.dat to ilm3Dcn_frame_max.dat
 */

void cancell_histFile(int n_frame_max){
    
    char buffer[32]; // The filename buffer.
    
    cout << "... PLOT GNUPOLT FILM END ..." << endl;
    
    cout << "cancell frames video ... \n";
    
    for (int i=0; i<n_frame_max+1; i++) {

        snprintf(buffer, sizeof(char) * 32, "film3Dc%i.dat", i+1);
        remove(buffer);
        
    }
    
    remove("3D_hist.gnu");
    remove("play_video.gnu");
    remove("PercUpDownh.dat");
    
    cout << "Frames video deleted ... \n\n... \n";
    
}