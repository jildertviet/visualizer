//
//  Rectangle.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#include "Rectangle.hpp"


Rectangle::Rectangle(){
    
}

Rectangle::Rectangle(float millisTime, ofVec2f loc, ofVec2f size, ofColor color, float attack, float release, ofVec2f direction, bool move){
    setType("Rectangle");
    setEndTime(millisTime);
    this->loc = loc; this->size = size;
    colors.clear();
    colors.push_back(color);
    active=true;
    addEnvAlpha(attack, millisTime-attack-release,release);
    this->direction = direction;
    speed = 1;
    bMove = move;
}

Rectangle::Rectangle(ofVec2f loc, ofVec2f size){
    setType("Rectangle");
    this->loc = loc; this->size = size; active=false;
    bMove = true;
    direction = ofVec2f(-1,0);
    speed = 1;
    
//    deleteWithFade(3000); // Test
}

void Rectangle::display(){
    ofSetColor(colors[0]);
    ofPushMatrix();
    ofTranslate(size.x*0.5, size.y*0.5);
    ofRotateZDeg(45);
    ofTranslate(-size.x*0.5, -size.y*0.5);
    ofTranslate(loc);
    ofDrawRectangle(0, 0, size.x, size.y);
    ofPopMatrix();
}

void Rectangle::specificFunction(){
    checkBorders();
    if(bMove)
        loc += direction*speed;
}

void Rectangle::move(){
    
}

void Rectangle::noDank(){
    setEndTime(400);
    loc = ofVec2f(ofRandomWidth(), 0);
    size = ofVec2f(100, ofGetWindowHeight());
    active=true;
    int attack = 10;
    int release = 300;
    int millisTime = 400;
    addEnvAlpha(attack, millisTime-attack-release,release);
    if(ofRandom(-1,1)>0){
        direction = ofVec2f(-1,0);
    } else{
        direction = ofVec2f(1,0);
    }
    speed = 1;
    bMove = true;
}
