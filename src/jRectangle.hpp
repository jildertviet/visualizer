//
//  Square.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#ifndef jRectangle_hpp
#define jRectangle_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class jRectangle: public Event{
public:
    jRectangle();
    jRectangle(float millisTime, ofVec2f loc, ofVec2f size, ofColor color=ofColor(255,255), float attack=100, float release=100, ofVec2f direction=ofVec2f(-1,0), bool move=true); // Temporary
    
    jRectangle(ofVec3f loc, ofVec3f size=ofGetWindowSize()); // Infite
    void ownDtor();
    
    void test(){cout<<"Rectangle test"<<endl;};
    virtual void display();
    void specificFunction();
    
    
    float topspeed = 1.0;
    void move();
    void jump(ofVec2f distance);
    
    void noDank();
    virtual void imageFloating(){};
    
    void addPtr(jRectangle** p);
    void addVector(vector<jRectangle*>* v);
    vector<jRectangle*>* v = nullptr; // Zou ook nog in een vector van pointers naar vector<rect*> kunnen...
    void removeFromVector();
    
    void setHeight(int height);
    void setWidth(int widht);
    
    // For division
    void divide();
    vector<jRectangle*> children;
    int numChildren = 0;
    jRectangle* getChild();
    ofMesh* m = nullptr;
    void setQuadColor(ofColor a, ofColor b, ofColor c, ofColor d);
    void setAlpha(unsigned char alpha) override;
private:
    
};
#endif /* Rectangle_hpp */
