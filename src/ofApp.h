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
    // Settings
    vector<string> arguments;
    glm::vec2 size = glm::vec2(1280, 800);
    float frameRate = 60;
    bool bUseFbo = false;
    bool bFullScreen = true;
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);

    Visualizer* visualizer = nullptr;
    ofxOscReceiver GUIreceiver;
    ofxOscReceiver SCreceiver;
    ofxOscReceiver spaceNavReceiver;
    ofxOscSender GUIsender;
    ofxOscSender SCsender;
    ofxOscMessage msg;
    bool bSCClientSet = false;
    bool bGUIClientSet = false;
    
    vector<glm::vec3> meshVertices;
    vector<glm::vec2> texCoords;
    ofMesh mesh;
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
