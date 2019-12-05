//
//  jLine.hpp
//  Visualizer_2_3
//
//  Created by Jildert Viet on 18-09-17.
//
//

#ifndef jLine_hpp
#define jLine_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class jLine: public Event{
public:
typedef unsigned char uint8;
    jLine();
    void display();
    void specificFunction();
    ofPolyline line;
    int amplitude = 0;
    uint8 numPoints = 10;
    float seed;
    
    float balance = 0.5;
    int heightOffset = 0;
    
    float rotation = 0;
    
    void toRect(ofVec2f loc, ofVec2f size);
    
    uint8 mode = 0;
};
#endif /* jLine_hpp */
