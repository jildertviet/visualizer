#pragma once

#include "ofMain.h"
#include "Visualizer.hpp"
#include "ofxOsc.h"
#include "Song.hpp"
#include "ofxJSON.h"

#include "Figgie.hpp"
#include "TimeForYou.hpp"
#include "Faith.hpp"
#include "MamaOtis.hpp"
#include "MaybeTomorrow.hpp"
#include "Juncture.hpp"
#include "JustBefore.hpp"
#include "TeachMe.hpp"
#include "BendStraws.hpp"
#include "CounterParts.hpp"
#include "Trying.hpp"
#include "eLive.hpp"
#include "Laura.hpp"
#include "Start.hpp"
#include "NewOpener.hpp"
#include "OnlyYours.hpp"
#include "GlassHouse.hpp"
#include "videoBars.hpp"
#include "Spheres.hpp"
#include "verses.hpp"
#include "model.hpp"
#include "imageFloat.hpp"
#include "jTxt.hpp"
#include "MsgParser.hpp"

class ofApp : public ofBaseApp {

	public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    Visualizer* visualizer = nullptr;
    ofxOscReceiver GUIreceiver;
    ofxOscReceiver SCreceiver;
    ofxOscReceiver spaceNavReceiver;
    ofxOscSender GUIsender;
    ofxOscSender SCsender;
    ofxOscMessage msg;
    
    ofMesh mesh;
    ofVec2f texCoords[4] = {ofVec2f(0,0), ofVec2f(1280, 0), ofVec2f(1280, 800), ofVec2f(0, 800)};
    ofVec3f meshVertices[4] = {ofVec3f(0, 0, 0), ofVec3f(1280, 0, 0), ofVec3f(1280, 800, 0), ofVec3f(0, 800, 0)};
    bool bEditMode = false;
    char fboDisplayMode = 0;
    bool bSaveFbo = false;
    
    void receive(ofxOscMessage m);
    void receiveSpaceNav(ofxOscMessage m);
    bool bTemp = false;
    MsgParser* parser;
    
//    ofxSyphonServer syphonServerLeft, syphonServerRight;
    
    ofFbo left, right, f;
private:
    Song* song;
    void loadSong(string name);
    vector<string> songs = {
        "Faith",
        "Figgie",
        "Juncture",
        "MamaOtis",
        "MaybeTomorrow",
        "TimeForYou",
        "JustBefore",
        "BendStraws",
        "TeachMe",
        "CounterParts",
        "Trying",
        "eLive",
        "Laura",
        "Start",
        "NewOpener",
        "OnlyYours",
        "GlassHouse",
        "videoBars",
        "Spheres",
        "verses",
        "model"
    };
};
