//
//  jTxt.cpp
//  Visualizer_2_5
//
//  Created by Jildert Viet on 02-03-19.
//

#include "jTxt.hpp"

jText::jText(ofTrueTypeFont* f){
    this->f = f;
}

void jText::display(){
    ofSetColor(colors[0]);
    ofPushMatrix();
    ofRotateX(180);
    f->drawString(txt, loc.x, -loc.y);
    ofPopMatrix();
}

void jText::setText(string txt){
    this->txt = txt;
}
