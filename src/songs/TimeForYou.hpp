//
//  TimeForYou.hpp
//  Bas
//
//  Created by Jildert Viet on 23-03-16.
//
//

#ifndef TimeForYou_hpp
#define TimeForYou_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "JImage.hpp"
#include "MultiMesh.hpp"

class TimeForYou: public Song{
public:
    TimeForYou(Visualizer* visualizer);
    
    vector<MultiMesh*> meshes;
    
    void stop();
    
    
    void F0(); void F1(); void F2(); void F3();
    void F4(); void F5(); void F6(); void F7();
    void F8(); void F9(); void F10(); void F11();
    void F12(); void F13();
    
    void generateVerseMeshes(); void deleteVerseMeshes();
    void generateChorusMeshes(); void deleteChorusMeshes();
    void infiteGrowRadius();
    
    void bridgeWithoutCenterCircle();
    
    void start(); bool bIsStarted = false;
    void changeOneMultiMesh();
    
    void MidiFunc(ofxMidiMessage msg);
    void exit();
};

#endif /* TimeForYou_hpp */
