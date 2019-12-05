//
//  Event.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Mapper.hpp"
#include "ofxOsc.h"
#include "Env.hpp"

class Event{
public:
    Event();
    ~Event();
    // ----------------------------------------------------------------------------------------------------
    bool active = false;
    virtual void update();
        void updateMain();

    virtual void display(){};
        void displayMain();
    
    virtual void test();
    virtual void ownDtor(){};
    unsigned int startTime = 0;
    unsigned int endTime = 1000;
    
    void deleteNext();
    
    void deleteWithFade(short int releaseTime);
    // ----------------------------------------------------------------------------------------------------
    int* numEventsPtr = nullptr;
    void setType(string type);
    string type = "Event";
    unsigned int id = 0;
    
    Event* getEvent(int index);
    
    virtual void setLoc(ofVec3f loc);
    ofVec3f size, loc, direction;
    vector<ofColor> colors;
    float speed = 1.;
    bool bMove = false;

    Event* next = nullptr;
    Event* previous = nullptr;
  
    virtual void specificFunction(){ return; };
    
    void addEvent(Event* toAdd);
    void addEventAsFirst(Event* toAdd);
    
    Event* getLast();
    
    // Envelope-stuff
    short getNumEnv();
    Env* getLastEnv();
    static bool checkIfEnvIsDone(Env* e);
    bool checkIfEnvExists(char id);
    void loopLastEnv();
    void clearEnv();
    vector<Env*> env;
    
    void setEndTime(float duration);

    void setEnvelope(int attack, int sustain, int release, ofVec2f range = ofVec2f(0,255));
    void setEnvelope(int attack, int sustain, int release, int* value, ofVec2f range);
    void setEnvelope(int attack, int sustain, int release, float* value, ofVec2f range, int id=0, bool bSetEndTime=true);
    
    void addEnvAlpha(float a, float s, float r, float alpha=255);
    void addEnvAlpha(vector<float> levels, vector<float> times, char curve=0);
    Env* addEnv(Env* e);
    Env* addEnv(vector<float> levels, vector<float> times, float* f, char curve=0);
    Env* addEnv(vector<float> levels, vector<float> times, int* i, char curve=0);
    Env* addEnv(vector<float> levels, vector<float> times, ofColor* c, char curve=0);
    
    
    bool bCheckBordersH = true;
    bool bCheckBordersV = true;
    void checkBorders();
    
    void setAlpha(int alpha);
    virtual void setColor(ofColor color, int index=0);
    
    void makeLinkTap(string name, float* floatPtr, ofVec2f range);
    void makeLinkTap(string name, int* intPtr, ofVec2f range);
    void makeLinkTap(string name, ofColor* colorPtr, ofVec2f range=ofVec2f(0,255));

    void printLinkTaps();
    vector<linkTap*> linkTaps;
    linkTap* getLinkTap(string name);
    vector<Mapper*> mappers;
    vector<Mapper*>* mappersParent = nullptr;
    
    // To clear references made to this object
    vector<Event**> toClear;
    Event** lastPtr = nullptr;
    virtual void addPtr(Event** p);

    vector<Event*>* parentContainer = nullptr;
    
    bool bFill = true;
    
    virtual void setSize(ofVec3f s);
    virtual void customOne(){};
    virtual void customTwo(){};
    virtual void customThree(){};
    virtual void customFour(){};
    virtual void customFive(){};
    float customOneArguments[5]; // Only use ptr?
    float customTwoArguments[5];
    Event** events = nullptr;
    
    virtual void setMode(char m);
    char mode = 0;
    ofVec3f rotation = ofVec3f(0, 0, 0);
private:

};

#endif /* Event_hpp */
