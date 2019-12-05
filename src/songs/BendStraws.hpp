#ifndef BendStraws_hpp
#define BendStraws_hpp

#include <stdio.h>
#include "Visualizer.hpp"
#include "ofMain.h"
#include "Song.hpp"

class BendStraws: public Song{
public:
    BendStraws(Visualizer* v); // AlphaBlackScreen maken
    void addVorm(); // 8-hoek die groter is dan de vorige
    void stop();
    
    void F0(); void F1(); void F2(); void F3();
    void F4(); void F5(); void F6(); void F7();
    void F8(); void F9(); void F10(); void F11();
    void F12(); void F13(); void F14(); void F15();
    
    void C0(int val); void C1(int val); void C2(int val);
    
    vector<int> divisions;
    vector<float> radiuses;
    char shape = 8;
    char maxVorm = 9;
    vector<Vorm*> vormen;
    Vorm* lastVorm = nullptr;
    
    void switchRadiusses(bool instant);
    void rotateVorm();
    void oneFrame();
    void formAllVorms();
    
    void addNoise();
    void randomLineMax(int min, int max);
    void setLineMax(int val);
    
    void exit();
    int deleteFade = 10000;
};
#endif /* BendStraws */
