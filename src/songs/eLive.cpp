//
//  eLive
//  Visualizer_1_4
//
//  Created by Jildert Viet on 20-01-17.
//
//
#ifndef TARGET_RASPBERRY_PI
#define SPLIT   false

#include "eLive.hpp"

eLive::eLive(Visualizer* v){
    this->v = v;
    cout << "Song: eLive" << endl;
    
    mt = new MaybeTomorrow(v);
    j = new Juncture(v);
    j->maxMirrors = 30;
    
    fade1 = (jRectangle*)v->addEvent(new jRectangle(ofVec2f(0,0), ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight())), 3);
    fade2 = (jRectangle*)v->addEvent(new jRectangle(ofVec2f(ofGetWindowWidth()/2.,0), ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight())), 3);
//    F0();
    
    if(SPLIT){
        fade1->colors[0] = ofColor(0, 0);
        fade1->bMove = false;
        fade2->colors[0] = ofColor(0, 0);
        fade2->bMove = false;
    }
    
//    mask = (Image*)v->addEvent(new Image("/Users/Jildert/of_v0.9.6_osx_release/apps/myApps/Visualizer_1_5/bin/data/test.png", ofVec2f(ofGetWindowWidth()/2.,0)), 3);
}

void eLive::F0(){ // Make particle system ||
//    if(!ps){
//        ps = (particleSystem*)addEvent(new particleSystem(1000000));
//
//        ps->setForcesRange(1.5);
//        ps->setForcesSpeed(1);
//        if(SPLIT)
//            ps->loc = ofVec2f(-ofGetWindowWidth()/4.,0);
//
//        v->addMapper(new Mapper(&v->mappers, (Event*)this, "/26", "Onset1", ps->getLinkTap("forceOnePower")));
//        v->addMapper(new Mapper(&v->mappers, (Event*)this, "/28", "Onset2", ps->getLinkTap("forceTwoPower")));
//        v->addMapper(new Mapper(&v->mappers, (Event*)this, "/30", "Onset3", ps->getLinkTap("forceThreePower")));
//    }
}

void eLive::F1(){ // Move Screen||
//    ofSetWindowPosition(0, 0);
}

void eLive::F2(){ // ||
//    ofSetFullscreen(true);
}

void eLive::F3(){ // ||
//    ofSetFullscreen(false);
}

void eLive::F4(){ // Delete PSystem ||
    if(!ps)
        return;
    ps->setEnvelope(5000,0,0, &(ps->color.a), ofVec2f(0.05, 0.0), 0, true);
    ps->active = true;
    v->mappers.clear();
    ps = nullptr;
//    ps->deleteWithFade(5000);
}

void eLive::F5(){ // Hoekige lines||
    mt->F0();
    for(int i=0; i<mt->multiMesh.size(); i++){
//        mt->multiMesh[i]->loc.x *= 0.5;
//        mt->multiMesh[i]->loc.x += ofGetWindowWidth()/2.;
//        mt->multiMesh[i]->loc.x = 800;
        mt->multiMesh[i]->deleteWithFade(ofRandom(300,1000));
    }
}

void eLive::F6(){ // Add mirror ||
    j->F3();
    j->mirrors.back()->speed = ofRandom(2,3);
    j->mirrors.back()->move_up = true;
}

void eLive::F7(){ // Change Mirror moving ||
    j->F6();
}

void eLive::F8(){ // Hori lines||
    mt->F6();
    JNoise* n = (JNoise*)v->getLast();
    n->linesAmount = ofMap(v->busses[1]->value, 0., 1., 1, 100);
    n->setEnvelope(10,10,ofMap(v->busses[2]->value, 0., 1., 10, 800));
    if(SPLIT){
        n->size = ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight());
        n->loc = ofVec2f(ofGetWindowWidth()/2., 0);
    }
}

void eLive::F9(){ // Verti lines||
    mt->F7();
    JNoise* n = (JNoise*)v->getLast();
    n->linesAmount = ofMap(v->busses[1]->value, 0., 1., 1, 100);
    n->setEnvelope(10,10,ofMap(v->busses[2]->value, 0., 1., 10, 800));
    if(SPLIT){
        n->size = ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight());
        n->loc = ofVec2f(ofGetWindowWidth()/2., 0);
    }
}

void eLive::F10(){ // Clap! ||
    v->addEvent(
                new jRectangle(
                               8010,
                               ofVec2f(0,0),
                               ofGetWindowSize(),
                               ofColor(255),
                               10,
                               8000,
                               ofVec2f(0,0),
                               false
                               ), 2
                );
    v->getLast()->setAlpha(200);
}

void eLive::F11(){ // ||
    
}

void eLive::F12(){ // ||
    
}

void eLive::F13(){ // ||
    
}

void eLive::F14(){ // Fade2 Red||
    if(SPLIT)
        fade2->colors[0].r = 100;
}

void eLive::F15(){ // Fit fadeScreen ||
    v->makeFit(ofGetWindowSize());
    
    if(SPLIT){
        fade1->loc = ofVec2f(0,0);
        fade1->size = ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight());
        
        fade2->loc = ofVec2f(ofGetWindowWidth()/2.,0);
        fade2->size = ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight());
    }
}

void eLive::C0(int val){ // ||
    if(!ps)
        return;
    float speed = ofMap(val, 0, 127, 0.0005, 0.03);
//    cout << speed << endl;
//    ps->centerForce = speed;
//    ps->resetSpeedDiv = ofMap(val, 0, 127, 9, 3);
}

void eLive::C1(int val){ // Sets lineAmount||
    // Sets lineAmount
}

void eLive::C2(int val){ // Sets release Lines ||
    
}

void eLive::C3(int val){ // Set the color of the ps||
    if(!ps)
        return;
    ofFloatColor color = ps->color;
    color.g = ofMap(val, 0, 127, 0., 1.);
    color.b = ofMap(val, 0, 127, 0., 1.);
    ps->color = color;
}

void eLive::C4(int val){ // Speed of mirrors||
    for(int i=0; i<j->mirrors.size(); i++){
        j->mirrors[i]->speed = ofMap(val, 0, 127, 1., 3.);
    }
}

void eLive::C5(int val){ // ||
    if(SPLIT)
        fade1->colors[0].a = ofMap(val, 127, 0, 0, 255);
}

void eLive::C6(int val){ // ||
    if(SPLIT)
        fade2->colors[0].a = ofMap(val, 127, 0, 0, 255);
}

#endif // #ifndef TARGET_RASPBERRY_PI

