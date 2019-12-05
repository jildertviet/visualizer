#ifndef JustBefore_hpp
#define JustBefore_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "SpaceCube.h"

class JustBefore: public Song{
public:
    JustBefore(Visualizer* v);
    void stop();
    
    void F0(); void F1(); void F2(); void F3();
    void F4(); void F5(); void F6(); void F7();
    void F8(); void F9(); void F10(); void F11();
    void F12(); void F13(); void F14();
    
    void exit();
    
    vector<SpaceCube*> spacecubes;
    
private:
    void makeNewSpaceCube(int amount);
    void switchRotation();
    void addAndRemoveVertices();
    void drawOneLine();
    void slow();
    void randomAngle();
    void convertToSphere();
    void blink();
    void setAlpha(int alpha);
    void transform();
    void fadeOut();
    
    void halfTime();
    void doubleTime();
    
    int maxObjects = 5;
    
    ofLight light;
    ofLight lightTwo;
};
#endif /* JustBefore */
