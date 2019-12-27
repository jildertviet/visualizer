//  Created by Jildert Viet on 24-01-16.

#ifndef Visualizer_hpp
#define Visualizer_hpp

#define NUMLAYERS   7
#define MAX_EVENTS_PTRS 512
#define USE_PP  false // ofxPostProcessing

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxPostProcessing.h"

#include "Event.hpp"
#include "Vorm.h"
#include "JNoise.hpp"
#include "JImage.hpp"
#include "SpaceCube.h"
#include "particleSystem.hpp"
#include "JMirror.h"
#include "MultiMesh.hpp"
#include "MultiMeshMaybeTomorrow.hpp"
#include "JEllipse.h"
#include "jRectangle.hpp"
#include "RectangleMask.hpp"

#include "AlphaBlackScreen.hpp"
#include "fadeScreen.hpp"
#include "Mapper.hpp"
#include "Colors.hpp"
#include "Wavetables.hpp"
#include "Env.hpp"
#include "cameraController.hpp"

enum VisualizerLayer {
    NON_CAM_BACK,
    NON_CAM_FRONT,
    DEFAULT
};

class Bus;

class Visualizer{
public:
typedef unsigned char uint8;
    Visualizer(glm::vec2 size);
    ~Visualizer();
    ofFbo fbo;
    void deconstructor();
    void update();
    void display();
    
    void setAlpha(int alpha, bool bDo = true);
    void setBrightness(unsigned char b);
    
    void killAll();

    int numEvents = 0;
//    unsigned int numEventsAdded = 0;
    Event* last;
    ofxOscMessage getAllEvents();
    
    Event* events[MAX_EVENTS_PTRS];
    void getFreePointers();
    unsigned short numEventsAdded = 0;
    
    Event* addEvent(Event* e, int layerIndex=2, unsigned short index = 0);
    Event* addEvent(Event* e, VisualizerLayer l, unsigned short index = 0);
    
    Event* getLast(){return last;}
    Event* getEventById(int id);
    
    static bool checkIfNull(Event* e);
    static bool checkIfNullM(Mapper* m);
    
    bool bMirror = false;
    bool bAddMirror = false;

    void fitFadeScreen(glm::vec2 size = glm::vec2(0, 0));
    
    fadeScreen* fade = nullptr;
    AlphaBlackScreen* alphaScreen = nullptr;
    
    vector<Mapper*> mappers;
    void addMapper(Mapper* m);
    
    vector<Bus*> busses;
    
    // PostProcessing
#if USE_PP
    ofxPostProcessing post;
    ContrastPass::Ptr contrastPP = nullptr;
    ZoomBlurPass::Ptr zoomPP = nullptr;
    RGBShiftPass::Ptr rgbPP = nullptr;
    FxaaPass::Ptr fxaaPP = nullptr;
    NoiseWarpPass::Ptr noisePP = nullptr;
    
    bool bPostProcessing = false;
#endif
    
    bool bRotate = false;
    float rotationAngle = 0;
    float rotationAngleIcrement = 0.1;
    
    ofxOscSender* SCsender;
    ofxOscReceiver receiver;
    
//    vector<Pointer*> receivingPointers;
    vector<float> vec(float a);
    vector<float> vec(float a, float b);
    vector<float> vec(float a, float b, float c);
    vector<float> vec(float a, float b, float c, float d);
    vector<float> vec(float a, float b, float c, float d, float e);

    Wavetables wavetable;
    
    bool bMask = false;
//    Image* mask;
    ofImage mask;
    unsigned char maskBrightness = 0;
    ofEasyCam cam;
    void initCam();
    
    ofTrueTypeFont verdana30;
    cameraController* camController;
//    ofFbo sharedFbo, sharedFbo2;
    ofFbo circularMask;
    bool bDrawCirclularMask = true;
    void initCircularMaskFbo(glm::vec2 size, int num=1);
private:
    void loadLastMaskFile();
    vector<Event*> layers; // linked list, use AddEvent to add
//    ofShader mirror;
};

class Bus{
public:
    Bus(){
        tap = new linkTap("value", &value, ofVec2f(0., 1.0));
    }
    float value = 0.5;
    linkTap* tap;
};

#endif /* Visualizer_hpp */
