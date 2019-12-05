//
//  jRectangle
//
//  Created by Jildert Viet on 24-01-16.
//
//

#include "jRectangle.hpp"

jRectangle::jRectangle(){
    setType("jRectangle");
}

jRectangle::jRectangle(float millisTime, ofVec2f loc, ofVec2f size, ofColor color, float attack, float release, ofVec2f direction, bool move){
    setType("jRectangle");
    setEndTime(millisTime);
    this->loc = loc; this->size = size;
    colors.clear();
    colors.push_back(color);
    active=true;
//    setEnvelope(attack, millisTime-attack-release,release);
    addEnvAlpha(vector<float>{0, (float)colors[0].a, (float)colors[0].a, 0}, vector<float>{attack, millisTime-attack-release,release});
    this->direction = direction;
    speed = 1;
    bMove = move;
}

jRectangle::jRectangle(ofVec3f loc, ofVec3f size){
    setType("jRectangle");
    this->loc = loc; this->size = size; active=false;
    bMove = true;
    direction = ofVec2f(-1,0);
    speed = 1;
}

void jRectangle::ownDtor(){
    removeFromVector();
}

void jRectangle::display(){
    ofSetColor(colors[0]);
    if(bFill){
        ofFill();
    } else{
        ofNoFill();
    }
    
    ofPushMatrix();
    
    ofTranslate(loc);
    ofTranslate(-size*0.5);
    ofRotateZDeg(rotation.z);
    
//    ofTranslate(-loc);
    ofTranslate(size*0.5);
    
    if(!size.z){
        ofDrawRectangle(0, 0, size.x, size.y);
    } else{
        ofDrawBox(0, 0, 0, size.x, size.y, size.z);
    }
    

    ofPopMatrix();
    
    ofFill();
}

void jRectangle::specificFunction(){
    move();
    imageFloating(); // virtual
}

void jRectangle::move(){
    if(bMove){
        checkBorders();
        loc += direction*speed;
    }
}

void jRectangle::jump(ofVec2f distance){
    loc += distance;
}

void jRectangle::noDank(){
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

void jRectangle::addPtr(jRectangle** p){
    toClear.push_back((Event**)p);
}

void jRectangle::addVector(vector<jRectangle*>* v){
    this->v = v;
}

void jRectangle::divide(){
    
    ofVec2f newSize = size/2.;
    ofColor color = colors[(int)ofRandom(colors.size())];
    color.a = ofRandom(100)+100;
    for(int i=0; i<2; i++){
        ofVec2f newLoc = loc+ofVec2f(i*newSize.x, i*newSize.y);
        if(newLoc.x<ofGetWindowWidth() && newLoc.y<ofGetWindowHeight()){
            children.push_back(new jRectangle(newSize, newLoc));
            numChildren++;
            jRectangle* c = children.back();
            if(c->bMove){
                c->bMove = true;
            } else{
                c->bMove = false;
            }
            c->speed = speed;
            c->colors[0] = color;
        }
        
        
        
        newLoc = ofVec2f(newSize.x*2,0)+loc+ofVec2f(i*newSize.x, i*newSize.y);
        if(newLoc.x<ofGetWindowWidth() && newLoc.y<ofGetWindowHeight()){
            children.push_back(new jRectangle(newSize, newLoc));
            numChildren++;
            jRectangle* c = children.back();
            if(c->bMove){
                c->bMove = true;
            } else{
                c->bMove = false;
            }
            c->speed = speed;
            c->colors[0] = color;
        }
        
        newLoc = ofVec2f(0, newSize.y*2)+loc+ofVec2f(i*newSize.x, i*newSize.y);
        if(newLoc.x<ofGetWindowWidth() && newLoc.y<ofGetWindowHeight()){
            children.push_back(new jRectangle(newSize, newLoc));
            numChildren++;
            jRectangle* c = children.back();
            if(c->bMove){
                c->bMove = true;
            } else{
                c->bMove = false;
            }
            c->speed = speed;
            c->colors[0] = color;
        }
    }
    
    
    
    cout << "Num children: " << children.size() << endl;
}

jRectangle* jRectangle::getChild(){
    if(numChildren){
        return children.back();
        children.pop_back();
        numChildren--;
    } else{
        return nullptr;
    }
}

void jRectangle::removeFromVector(){
    if(v){
        for(int i=0; i<v->size(); i++){
            if(v->at(i) == this){
                v->at(i) = nullptr; // Later remove the nullptrs in vec
                cout << "Found self!" << endl;
                return;
            }
        }
    }
}

void jRectangle::setHeight(int height){ size.y = height; }
void jRectangle::setWidth(int width){ size.x = width; }
