//
//  Wavetables.hpp
//  Visualizer_2_4
//
//  Created by Jildert Viet on 25-09-17.
//
//

#ifndef Wavetables_hpp
#define Wavetables_hpp

#include <stdio.h>
#include "ofMain.h"

#define DEPTH   1024

struct curve{
    vector<float> data;
    char curve;
};

class Wavetables{
public:
    Wavetables();
    vector<curve*> curves;
    curve* sine;
};
#endif /* Wavetables_hpp */
