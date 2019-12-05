//
//  Template.cpp
//  Visualizer_1_4
//
//  Created by Jildert Viet on 20-01-17.
//
//

#include "Trying.hpp"

Trying::Trying(Visualizer* v){
    this->v = v;
    v->setAlpha(255);
    v->alphaScreen->gradientColor = ofColor(255,255,255,0);
    
//    v->addEvent(new jRectangle(ofVec2f(0,0)));
//    v->last->setColor(ofColor(0,0,0, 240));
    
    v->alphaScreen->gradientAlpha = 0;
    v->alphaScreen->bGradient = false;
    cout << "Song: Trying" << endl;
//    v->bRotate = true;
    colors.push_back(ofColor(0, 0, 255));
    colors.push_back(ofColor(255, 255, 255));
}

void Trying::F0(){ // Make 4x object ||
    int width = 200;
    int height = 200;
    
    for(int i=0; i<4; i++){
        SpaceCube* s = (SpaceCube*)addEvent(new SpaceCube(ofVec3f(
                                                                  0,0,0),
                                                          ofVec3f(width, height, width),
                                                          5,
                                                          2)
                                            );
        //        s->changeType(0);
        s->offset = ofVec3f(
                            ofRandom(0, ofGetWindowWidth())-(ofGetWindowWidth()/2.),
                            ofRandom(0, ofGetWindowHeight())-400,
                            -ofRandom(50));
        s->offset *= 1.5;
//        s->setEnvelope(1000 , 3000 , 3000, &(s->colors[0].a), ofVec2f(0, objectAlpha));
        s->active = true;
        s->setEnvelope(7000, 0, 0, &(s->offset.z), ofVec2f(0, 2000));
        s->addVector(&cubes);
        s->setColor((ofFloatColor)colors[1]);
        cubes.push_back(s);
    }
}

void Trying::F1(){ // Make big||
    int width = 500;
    int height = 500;
    
    for(int i=0; i<10; i++){
        SpaceCube* s = (SpaceCube*)addEvent(new SpaceCube(ofVec3f(
                                                                  0,0,0),
                                                          ofVec3f(width, height, width),
                                                          4,
                                                          2)
                                            );
        //        s->changeType(0);
        s->offset = ofVec3f(
                            ofRandom(0, ofGetWindowWidth())-(ofGetWindowWidth()/2.),
                            ofRandom(0, ofGetWindowHeight())-400,
                            -ofRandom(50));
        s->clearEnv();
//        s->setEnvelope(ofRandom(1000,2000), 3000, ofRandom(1000,3000), &(s->colors[0].a), ofVec2f(0, objectAlpha));
        s->active = true;
        s->setEnvelope(ofRandom(5000,9000), 0, 0, &(s->offset.z), ofVec2f(0, 2300), 0, false);
        s->addVector(&cubes);
//        s->setColor(ofFloatColor(1./255, 152./255, 217./255));
        cubes.push_back(s);
    }
}

void Trying::F2(){ // Env @ rotationspeed||
    for(int i=0; i<cubes.size(); i++){
//        cubes[i]->setEnvelope(
//                              ofRandom(100,500),
//                              0,
//                              ofRandom(1000,5000),
//                              &(cubes[i]->rotation_speed),
//                              ofVec2f(cubes[i]->rotation_speed, cubes[i]->rotation_speed*8),
//                              0,
//                              false);
        
        cubes[i]->addEnv(vector<float>{cubes[i]->rotation_speed, cubes[i]->rotation_speed*8, cubes[i]->rotation_speed}, vector<float>{ofRandom(100,500), ofRandom(1000,5000)}, &cubes[i]->rotation_speed);
    }
}

void Trying::F3(){ // Make big blue||
    int width = 500;
    int height = 500;
    
    for(int i=0; i<10; i++){
        SpaceCube* s = (SpaceCube*)addEvent(new SpaceCube(ofVec3f(
                                                                  0,0,0),
                                                          ofVec3f(width, height, width),
                                                          4,
                                                          2)
                                            );
        //        s->changeType(0);
        s->offset = ofVec3f(
                            ofRandom(0, ofGetWindowWidth())-(ofGetWindowWidth()/2.),
                            ofRandom(0, ofGetWindowHeight())-400,
                            -ofRandom(50));
        s->clearEnv();
//        s->setEnvelope(ofRandom(1000,2000), 3000, ofRandom(1000,3000), &(s->colors[0].a), ofVec2f(0, objectAlpha));
        s->active = true;
        s->setEnvelope(ofRandom(5000,9000), 0, 0, &(s->offset.z), ofVec2f(0, 2300), 0, false);
        s->addVector(&cubes);
//        s->setColor(ofFloatColor(1./255, 152./255, 217./255));
        s->setColor((ofFloatColor)colors[0]);
        cubes.push_back(s);
    }
}

void Trying::F4(){ // Add vertices||
     for(int i=0; i<cubes.size(); i++){
         cubes[i]->getBigger(1);
     }
}

void Trying::F5(){ // Change rotationspeed||
    for(int i=0; i<cubes.size(); i++){
        cubes[i]->rotateRotationSpeed();
    }
    
}
void Trying::F6(){ // Smallest cloud||
    int width = ofRandom(30,130);
    int height = width;
    
    for(int i=0; i<20; i++){
        SpaceCube* s = (SpaceCube*)addEvent(new SpaceCube(ofVec3f(
                                                                  0,0,0),
                                                          ofVec3f(width, height, width),
                                                          5,
                                                          2)
                                            );
        //        s->changeType(0);
        s->offset = ofVec3f(
                            ofRandom(0, ofGetWindowWidth())-(ofGetWindowWidth()/2.),
                            ofRandom(0, ofGetWindowHeight())-400,
                            -ofRandom(50));
        s->offset *= 1.3;
        s->clearEnv();
//        s->setEnvelope(ofRandom(2000,3000), 3000, 3000, &(s->colors[0].a), ofVec2f(0, objectAlpha));
        s->active = true;
        s->setEnvelope(9000, 0, 0, &(s->offset.z), ofVec2f(0, 2400));
        s->addVector(&cubes);
        cubes.push_back(s);
    }
    F5();
}
void Trying::F7(){ // Make mirrors||
    for(int i=0; i<12; i++){
        Event* m = new JMirror(ofVec2f(100, ofGetHeight()), ofVec2f(ofRandomWidth(), 0));
        m->setEnvelope(10, 0, 700);
        m->active = true;
        v->addEvent(m);
    }
}

void Trying::F8(){ // Bridge figures||
    cout << "F*" << endl;
    int width = 200;
    int height = 200;
    
    for(int i=0; i<3; i++){
        SpaceCube* s = (SpaceCube*)addEvent(new SpaceCube(ofVec3f(
                                                                  0,0,0),
                                                          ofVec3f(width, height, width),
                                                          3,
                                                          2)
                                            );
        //        s->changeType(0);
        float c = 0.9;
        s->setColor(ofFloatColor(c,c,c,objectAlpha));
        s->offset = ofVec3f(
                            ofRandom(0, ofGetWindowWidth())-(ofGetWindowWidth()/2.),
                            ofRandom(0, ofGetWindowHeight())-400,
                            -ofRandom(50));
        s->offset *= 1.5;
        s->clearEnv();
//        s->setEnvelope(ofRandom(1000,3000), 3000, 3000, &(s->colors[0].a), ofVec2f(0, objectAlpha));
        s->active = true;
        s->setEnvelope(10000, 0, 0, &(s->offset.z), ofVec2f(0, 2000));
        s->addVector(&cubes);
        for(char j=0; j<ofRandom(2); j++)
            s->rotateRotationSpeed();
        
        for(int j=0; j<3; j++){
            s->placeVertexOnRadius(width);
        }
        cubes.push_back(s);
    }
}

void Trying::F9(){ // Toggle RGBPP||
#if USE_PP
    if(v->rgbPP->getEnabled()){
        v->bPostProcessing = false;
        v->rgbPP->setEnabled(false);
    } else{
        v->bPostProcessing = true;
        v->rgbPP->setEnabled(true);
    }
#endif
//    v->bPostProcessing = !v->bPostProcessing;
}
void Trying::F10(){ // Kick||
    v->alphaScreen->setEnvelope(10, 10, 500, &(v->alphaScreen)->gradientAlpha, ofVec2f(0,80));
}
void Trying::F11(){ // Last kick||
    v->alphaScreen->setEnvelope(10, 10, 1000, &(v->alphaScreen)->gradientAlpha, ofVec2f(0,80));
}
void Trying::F12(){ // Toggle Gradient||
    cout << "Toggle bGradient" << endl;
    v->alphaScreen->bGradient = !v->alphaScreen->bGradient;
}
void Trying::F13(){ // Snare ||
    v->alphaScreen->setEnvelope(10, 10, 500, &(v->alphaScreen)->gradientAlpha, ofVec2f(0,40));
}
void Trying::F14(){ // Blue LED ||
    
}
void Trying::F15(){ // Toggle PP||
#if USE_PP
    v->bPostProcessing = !(v->bPostProcessing);
#endif
}

void Trying::C0(int val){ // RGB shift||
    float valF = ofMap(val, 0, 127, 0., 0.02);
#if USE_PP
    v->rgbPP->setAmount(valF);
#endif
}
void Trying::C1(int val){ // ||
    
}
void Trying::C2(int val){ // ||
    
}
void Trying::C3(int val){ // ||
    
}
void Trying::C4(int val){ // ||
    
}
void Trying::C5(int val){ // ||
    
}
void Trying::C6(int val){ // ||
    
}

void Trying::exit(){
#if USE_PP
    v->bPostProcessing = false;
#endif
}
