//
//  Juncture.hpp
//  Bas
//
//  Created by Jildert Viet on 06-04-16.
//
//

#ifndef Juncture_hpp
#define Juncture_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "JMirror.h"
#include "jRectangle.hpp"

class Juncture: public Song{
public:
    Juncture(Visualizer* V);
    void stop();
    
    void F0(); void F1(); void F2(); void F3();
    void F4(); void F5(); void F6(); void F7();
    void F8(); void F9(); void F10();
    
    int numSquares = 0; int numSquares1=0; int numSquares2=0; int numSquares3 = 0;
    jRectangle* allSquares[150];
    jRectangle* squares1[50]; int maxSquares1 = 50;
    jRectangle* squares2[50]; int maxSquares2 = 50;
    jRectangle* squares3[50]; int maxSquares3 = 50;

    int maxMirrors = 10;
    int numMirrors = 0;
    vector<JMirror*> mirrors;
    void exit();
private:
    
    void makeSquare(int type);
    void randomMizeMirrorAngle(int min, int max, int index=99);
    void randomMizeSquareSpeed(float min, float max, int index=99);
    void switchMirrorMovement();
    void switchMirrorVisibility();
    void deleteAllSquares();
    void makeRandomMirror();
    void fadeOutAllSquares();
    void jumpForWard(int index, int amount);
    
    void jumpAllForward(int min, int max);
    void deleteHalfSquares();
    void halfTime();
    void doubleTime();
    
    Event* topLayer;
};

#endif /* Juncture_hpp */
