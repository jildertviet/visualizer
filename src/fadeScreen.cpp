//
//  fadeScreen.cpp
//  Visualizer
//
//  Created by Jildert Viet on 13-11-16.
//
//

#include "fadeScreen.hpp"

fadeScreen::fadeScreen(){
    loc = ofVec2f(0,0);
    size = ofGetWindowSize();
    bMove = false;
    colors[0] = ofColor(0,0);
    setType("fadeScreen");
//    cout << "FDS ST: " << startTime << endl;
}

void fadeScreen::display(){
    ofFill();
    if(colors[0].a>0){
        ofSetColor(colors[0]);
        ofDrawRectangle(loc.x, loc.y, size.x, size.y);
    }
}

void fadeScreen::setBrightness(int alpha){
    alpha = 255-alpha;
    colors[0] = ofColor(0,alpha);
}
