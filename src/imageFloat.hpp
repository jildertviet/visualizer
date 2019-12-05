//
//  imageFloat.hpp
//  Visualizer_2_5
//
//  Created by Jildert Viet on 02-03-19.
//

#ifndef imageFloat_hpp
#define imageFloat_hpp

#include <stdio.h>
#include "Event.hpp"
#include "jRectangle.hpp"

class imageFloat: public Event, public ofImage{
public:
    imageFloat(string src);
};

class imageFloater: public jRectangle{ // Inherits Event
public:
    imageFloater(imageFloat* src);
    imageFloat* img;
    void display();
    void imageFloating();
    ofVec2f roi, roiSpeed;
};

#endif /* imageFloat_hpp */
