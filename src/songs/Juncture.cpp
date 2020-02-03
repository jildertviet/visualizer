//
//  Juncture.cpp
//  Bas
//
//  Created by Jildert Viet on 06-04-16.
//
//

#include "Juncture.hpp"

Juncture::Juncture(Visualizer* v){
    setName("Juncture");
    this->v = v;
    v->alphaScreen->bGradient = false;
    colors.push_back(ofColor::white);
    colors.push_back(ofColor::white);
    colors.push_back(ofColor::white);
}

void Juncture::stop(){
    for(int i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(1000);
    }
    for(int i=0; i<mirrors.size(); i++){
        mirrors[i]->active = true;
    }
}

void Juncture::F0(){ // Square 1||
    makeSquare(1);
}

void Juncture::F1(){ // Square 2||
    makeSquare(2);
}

void Juncture::F2(){ // Square 3||
    makeSquare(3);
}

void Juncture::F3(){ // Make Mirror||
    if(mirrors.size() < maxMirrors){
        int randomAdd = ofRandom(100);
        int size = 100 + randomAdd;
        Event* m = new JMirror(ofVec2f(size,size), ofVec2f(ofRandom(ofGetWindowWidth()-size), ofGetWindowHeight()-size));
        m->setColor(ofColor(255,200));
        addEvent(m);
        mirrors.push_back(((JMirror*)getLast()));
        numMirrors++;
    }
    
    
    
}

void Juncture::F4(){ // Switch Mirror Visible||
    switchMirrorVisibility();
}

void Juncture::F5(){ // Mirror Angle||
    randomMizeMirrorAngle(-45,45);
}

void Juncture::F6(){ // Mirror Move On/Off||
    switchMirrorMovement();
}

void Juncture::F7(){ // Jump All||
    jumpAllForward(-50,50);
}

void Juncture::F8(){ // Kill All||
    fadeOutAllSquares();
}

void Juncture::F9(){ // Double time||
    doubleTime();
}

void Juncture::F10(){ // Half time||
    halfTime();
}

void Juncture::makeSquare(int type){
    jRectangle* r;
    switch(type){
        case 1:{
            if(numSquares1 < maxSquares1){
                r = new jRectangle(
                                   ofVec3f(ofGetWindowWidth()-100,50+ofRandom(ofGetWindowHeight()-50), ofRandom(200)),
                                   ofVec3f(100,50,2)
                                   );
                addEvent(r);
                squares1[numSquares1] = allSquares[numSquares] = r;
                r->speed = ofRandom(0.5,1.0);
                r->bMove = true;
                ofColor c = colors[0];
                c.a = ofRandom(155) + 100;
                r->setColor(c);
                numSquares1++; numSquares++;
            }
        }
            break;
        case 2:{
            if(numSquares2 < maxSquares2){
                r = new jRectangle(
                                   ofVec2f(ofGetWindowWidth()-5,200),
                                   ofVec2f(5,400)
                                   );
                addEvent(r);
                squares2[numSquares2] = allSquares[numSquares] = r;
                r->speed = 1.5+ofRandom(0.1);
                 r->bMove = true;
                ofColor c = colors[1];
                c.a = ofRandom(155) + 100;
                r->setColor(c);
                numSquares2++; numSquares++;
            }
        }
            break;
        case 3:{
            r = new jRectangle(
                               ofVec2f(ofGetWindowWidth()-20,ofGetWindowHeight()-200),
                               ofVec2f(20,200)
                               );
                addEvent(r);
                r->speed = ofRandom(2.5,3.0);
             r->bMove = true;
                ofColor c = colors[2];
                c.a = ofRandom(155) + 100;
                r->colors[0] = c;
                r->deleteWithFade(3000);
        }
            break;
    }
}

void Juncture::randomMizeMirrorAngle(int min, int max, int index){ // -45, 45
    if(index==99){ // Do for all
        for(int i=0; i<mirrors.size(); i++)
            mirrors[i]->angle = ofRandom(min,max);
        return;
    } else{ // Do specific index
        mirrors[index]->angle = ofRandom(min,max);
    }
}

void Juncture::randomMizeSquareSpeed(float min, float max, int index){ // 1.0, 2.0
    if(index==99){ // Do for all
        for(short i=0; i<numSquares; i++)
            allSquares[i]->speed = ofRandom(min, max);
        return;
    } else{ // Do specific index
        allSquares[index]->speed = ofRandom(min, max);
    }
}

void Juncture::switchMirrorMovement(){
    for(char i=0; i<mirrors.size(); i++)
        mirrors[i]->bMove = !mirrors[i]->bMove;
}

void Juncture::deleteAllSquares(){
    for(short i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(1);
        allSquares[i] = nullptr;
        numSquares--;
    }
}

void Juncture::makeRandomMirror(){

}

void Juncture::switchMirrorVisibility(){
    for(int i=0; i<mirrors.size(); i++){
        cout << i << endl;
        mirrors[i]->bDisplayMirror = !(mirrors[i]->bDisplayMirror);
//        mirrors[i]->type;
//        mirrors[i]->draw_sides = true;
    }
}

void Juncture::fadeOutAllSquares(){
    for(int i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(500);
    }
    numSquares = numSquares1 = numSquares2 = numSquares3 = 0;
}

void Juncture::jumpForWard(int index, int amount){
    allSquares[index]->loc.x += amount;
}

void Juncture::jumpAllForward(int min, int max){
    for(int i=0; i<numSquares; i++){
        jumpForWard(i, ofRandom(min,max));
    }
}

void Juncture::deleteHalfSquares(){
    for(int i=numSquares-1; i>numSquares/2; i--){
        allSquares[i]->deleteWithFade(1000);
        allSquares[i] = nullptr;
        numSquares--;
    }
}

void Juncture::halfTime(){
    for(int i=0; i<numSquares; i++)
        allSquares[i]->speed = allSquares[i]->speed/2.;
}
void Juncture::doubleTime(){
    for(int i=0; i<numSquares; i++)
        allSquares[i]->speed = allSquares[i]->speed*2;
}

void Juncture::exit(){
    for(int i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(10000);
    }
    for(int i=0; i<mirrors.size(); i++){
        mirrors[i]->active = true;
    }
}
