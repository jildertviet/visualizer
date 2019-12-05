//
//  Ghost.cpp
//  Bas
//
//  Created by Jildert Viet on 24-04-16.
//
//

#include "JustBefore.hpp"

JustBefore::JustBefore(Visualizer* v){
    setName("JustBefore");
    this->v = v;
    colors.push_back(ofColor::white);
}

void JustBefore::stop(){
    for(int i=0; i<spacecubes.size(); i++){
        spacecubes[i]->active = true;
        spacecubes[i]->setEnvelope(1,1,1000);
    }
}

void JustBefore::F0(){ // Switch Rotation ||
    switchRotation();
}

void JustBefore::F1(){  // Add or remove vertices ||
    addAndRemoveVertices();
}

void JustBefore::F2(){ // drawOneLine ||
    drawOneLine();
}

void JustBefore::F3(){ // slow ||
    slow();
}

void JustBefore::F4(){ // randomAngle ||
    randomAngle();
}

void JustBefore::F5(){ // Env @ speed||
    for(int i=0; i<spacecubes.size(); i++){
        SpaceCube* s = spacecubes[i];
        if(s->getNumEnv()==0){
//            s->setEnvelope(10, 10, 400, &(s->rotation_speed), ofVec2f(s->rotation_speed, s->rotation_speed*4));
            s->addEnv(v->vec(
                             s->rotation_speed,
                             s->rotation_speed*4,
                             s->rotation_speed),
                      v->vec(10, 400),
                      &(s->rotation_speed));
        }
    }
}

void JustBefore::F6(){ // fadeOut ...  ||
    fadeOut();
}

void JustBefore::F7(){ // Blink ||
    blink();
}

void JustBefore::F8(){ // 40x + and - vertices ||
    for(int i=0; i<40; i++)
        addAndRemoveVertices();
}

void JustBefore::F9(){ // Lines vs Triangles ||
    for(int i=0; i<spacecubes.size(); i++){
        if(spacecubes[i]->mode == 0){
            spacecubes[i]->setMode(1);
        } else{
            spacecubes[i]->setMode(0);
        }
    }
}

void JustBefore::F10(){ // transform ||
    transform();
}

void JustBefore::F11(){ // doubleTime ||
    doubleTime();
}

void JustBefore::F12(){ // halfTime ||
    halfTime();
}

void JustBefore::F13(){ // All to lines||
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->setMode(0);
}

void JustBefore::F14(){ // Make object ||
    makeNewSpaceCube(1);
}

void JustBefore::makeNewSpaceCube(int amount_){
    if(spacecubes.size() >= maxObjects)
        return;

    for(int i=0; i<amount_; i++){
        int size = ofGetWindowHeight()*0.9;
        v->addEvent(
                    new SpaceCube(
                                  ofVec3f((ofGetWindowWidth()-ofGetWindowHeight())/2.,0,0),
                                  ofVec3f(size, size,-size),
                                  ofRandom(5,7),
                                  6
                                  )
                    );
        
        spacecubes.push_back((SpaceCube*)v->getLast());
        
        int dir;
        if(ofRandom(-1, 1) > 0){
            dir = 1;
        } else{
            dir = -1;
        }
        spacecubes.back()->radius = 500 + ofRandom((ofGetWindowWidth()/2.)-200);
        spacecubes.back()->rotation_direction = dir;
        ofColor c = colors[ofRandom(colors.size())];
        c.a = 10;
        spacecubes.back()->setColor(ofFloatColor(c));
    }
}

void JustBefore::switchRotation(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->rotateRotationSpeed();
}

void JustBefore::addAndRemoveVertices(){
    SpaceCube* scTemp = spacecubes[(int)ofRandom(spacecubes.size())];
    if(ofRandom(-1,1) > 0){
        if(scTemp->mesh.getNumVertices() < 7)
            scTemp->placeNewPoint(ofVec3f(), true);
    } else{
        if(scTemp->mesh.getNumVertices() > 3)
            scTemp->removeLastVertex();
    }
}

void JustBefore::drawOneLine(){
    int index = (int)ofRandom(spacecubes.size());
//    cout << index << endl;
    spacecubes[index]->draw_line = true;
}

void JustBefore::slow(){
    for(int i=0; i<spacecubes.size(); i++){
        spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed/4.;
    }
}

void JustBefore::setAlpha(int alpha){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->setAlpha(10);
}

void JustBefore::randomAngle(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->randomChooseRotXorRotY();
}

void JustBefore::convertToSphere(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->convert_to_sphere = true;
}

void JustBefore::blink(){
    spacecubes[(int)ofRandom(spacecubes.size())]->blink();
}

void JustBefore::transform(){
    for(int i=0; i<spacecubes.size(); i++){
        spacecubes[i]->colors[0].a = 0.4;
        if(i > 0){
            spacecubes[i]->setMode(0);
            spacecubes[i]->getBigger(9);
        } else{
            spacecubes[0]->setMode(0);
//            spacecubes[0]->setAlpha(5);
        }
    }
}

void JustBefore::fadeOut(){
    for(int i=0; i<spacecubes.size(); i++){
        spacecubes[i]->active = true;
        spacecubes[i]->setEndTime(3000);
//        spacecubes[i]->setEnvelope(1,1,3000);
//        spacecubes[i]->addEnv(v->vec(spacecubes[i]->colors[0].a, 0), v->vec(3000), &(spacecubes[i]->colors[0].a));
    }
    spacecubes.clear();
}

void JustBefore::halfTime(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed/2.;
}

void JustBefore::doubleTime(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed*2;
}

void JustBefore::exit(){
    for(int i=0; i<spacecubes.size(); i++){
        // Fade out
        SpaceCube* s = spacecubes[i];
        int fadeTime = 10000;
//        float* alpha = &(s->colors[0].a);
//        s->setEnvelope(fadeTime, 0, 0, alpha, ofVec2f(*alpha, 0.0));
//        s->addEnv(v->vec(s->colors[0].a, 0), v->vec(fadeTime), &(s->colors[0].a));
        // Set delete time
        s->setEndTime(fadeTime); s->active = true;
    }
    spacecubes.clear();
//    ofDisableLighting();
//    delete light; delete lightTwo;
}
