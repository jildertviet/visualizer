//
//  Square.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class Rectangle: public Event{
public:
    __attribute__((deprecated))
    Rectangle();
    __attribute__((deprecated))
    Rectangle(float millisTime, ofVec2f loc, ofVec2f size, ofColor color=ofColor(255,255), float attack=100, float release=100, ofVec2f direction=ofVec2f(-1,0), bool move=true); // Temporary
    __attribute__((deprecated))
    Rectangle(ofVec2f loce, ofVec2f size); // Infite
    
    void test(){cout<<"Rectangle test"<<endl;};
    virtual void display();
    void specificFunction();
    
    bool bMove = false;
    float topspeed = 1.0;
    void move();
    
    void noDank();
};
#endif /* Rectangle_hpp */
