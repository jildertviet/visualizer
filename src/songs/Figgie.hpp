//
//  Figgie.hpp
//  Visualizer_1_4
//
//  Created by Jildert Viet on 20-01-17.
//
//

#ifndef Figgie_hpp
#define Figgie_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Colors.hpp"
#include "Visualizer.hpp"
#include "Song.hpp"

class Figgie: public Song{
public:
    Figgie(Visualizer* v);
    Visualizer* v;
    Colors* colors;
    RectangleMask* rectMask;
    vector<jRectangle*> bars;
    
    void F0(); void F1(); void F2(); void F3();
    void F4(); void F5(); void F6(); void F7();
    void F8(); void F9(); void F10(); 
    
    void songCCValue(int note, int value);
};

#endif /* Figgie_hpp */
