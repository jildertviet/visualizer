//
//  Spheres.cpp
//  Visualizer_1_4
//
//  Created by Jildert Viet on 20-01-17.
//
//

#include "Spheres.hpp"

Spheres::Spheres(Visualizer* v){
    this->v = v;
    setName("Spheres");
    
    for(char i=0; i<8; i++){
        dotsBlob* d = new dotsBlob();
        blobs.push_back(d);
        d->loc = ofVec3f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(100));
        d->range = 100;
        d->blobs = &blobs;
        d->bOnlyLines = false;
        d->bDrawSphere = false;
        d->setColor(ofColor::white);
        addEvent(d);
    }
}

void Spheres::F0(){ // ||
    
}

void Spheres::F1(){ // ||
    
}

void Spheres::F2(){ // ||
    
}

void Spheres::F3(){ // ||
    
}

void Spheres::F4(){ // ||
    
}

void Spheres::F5(){ // ||
    
}

void Spheres::F6(){ // ||
    
}

void Spheres::F7(){ // ||
    
}

void Spheres::F8(){ // ||
    
}

void Spheres::F9(){ // ||
    
}

void Spheres::F10(){ // ||
    
}

void Spheres::F11(){ // ||
    
}

void Spheres::F12(){ // ||
    
}

void Spheres::F13(){ // ||
    
}

void Spheres::F14(){ // ||
    
}

void Spheres::F15(){ // ||
    
}

void Spheres::C0(int val){ // Range ||
    range = ofMap(val, 0, 127, 1, 1000);
    for(char i=0; i<blobs.size(); i++)
        blobs[i]->range = range;
}

void Spheres::C1(int val){ // ||
    
}

void Spheres::C2(int val){ // ||
    
}

void Spheres::C3(int val){ // ||
    
}

void Spheres::C4(int val){ // ||
    
}

void Spheres::C5(int val){ // ||
    
}

void Spheres::C6(int val){ // ||
    
}

void Spheres::exit(){
    
}

void Spheres::update(){
    setConnections();
}

bool sortFunction (float* a,float* b) { return (a[0]<b[0]); }

void Spheres::setConnections(){
    vector<float*> distances;
    for(uint16 i=0; i<blobs.size(); i++){
        blobs.at(i)->connections.clear();
        blobs.at(i)->distances.clear();
        blobs.at(i)->numConnections = 0;
        
        for(uint16 j=i+1; j<blobs.size(); j++){
            float d = blobs.at(i)->loc.distance(blobs.at(j)->loc);
            if(d < blobs.at(j)->range){
                distances.push_back(new float[3]);
                distances.back()[0] = d;
                distances.back()[1] = i;
                distances.back()[2] = j;
            }
        }
    }
    std::sort (distances.begin(), distances.end(), sortFunction); // Sort them by distance
    
    for(uint16 i=0; i<distances.size(); i++){
        dotsBlob* blobA = blobs.at(distances[i][1]);
        dotsBlob* blobB = blobs.at(distances[i][2]);
        if(blobA->numConnections <= blobA->maxConnections && blobB->numConnections <= blobB->maxConnections ){
            blobA->connections.push_back(blobB);
            blobA->distances.push_back(distances[i][0]);
            blobA->numConnections++;
            blobB->numConnections++;
        } else{
            
        }
    }
}
