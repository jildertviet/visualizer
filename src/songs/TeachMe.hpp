//
//  TeachMe
//  Visualizer_1_4
//
//  Created by Jildert Viet on 20-01-17.
//
//

#ifndef TeachMe_hpp
#define TeachMe_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Colors.hpp"
#include "Visualizer.hpp"
#include "Song.hpp"

class TeachMe: public Song{
public:
    TeachMe(Visualizer* v);
    Colors* colorsObj;
    RectangleMask* rectMask;
    vector<jRectangle*> bars;
    jRectangle* bg;
    
    void F0(); void F1(); void F2(); void F3();
    void F4(); void F5(); void F6(); void F7();
    void F8(); void F9(); void F10(); void F11();
    void F12(); void F13(); void F14(); void F15();
    
    void C0(int v); void C1(int v); void C2(int);  void C3(int v);
    void C4(int v); void C5(int v); void C6(int v); void C7(int v);
    
    void exit();
    
    string colorsName = "BatobeTeachMe";
};

#endif /* TeachMe */
