//
//  Wavetables.cpp
//  Visualizer_2_4
//
//  Created by Jildert Viet on 25-09-17.
//
//

#include "Wavetables.hpp"

Wavetables::Wavetables(){
    // CURVES
    for(char i=0; i<9; i++){ // curves[4] = lineair
        curve* c = new curve();
        c->curve = i-4;
        for(short int j=0; j<DEPTH; j++){
            float v = j / (float)DEPTH;
            if(i<4){
                v = pow(v, ofMap(i, 0, 4, 1/8., 1/2.));
            } else if(i!=4){
                v = pow(v, ofMap(i, 5, 8, 2, 8));
            }
            c->data.push_back(v);
        }
        curves.push_back(c);
    }
    
    // SINE WAVE
    sine = new curve();
    for(short int i=0; i<DEPTH; i++){
        float v = i / (float)DEPTH;
        v = sin(v*TWO_PI);
        sine->data.push_back(v);
    }
}
