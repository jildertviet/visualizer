//
//  Event.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#include "Event.hpp"

Event::Event(){
    colors.push_back(ofColor(255,0));
    startTime = ofGetElapsedTimeMillis();
    
//    makeLinkTap("alpha", &(colors[0]));
//    cout << "Event startTime: " << startTime << endl;
}

Event::~Event(){
    if(lastPtr){
        *lastPtr = nullptr;
    }
    
    if(numEventsPtr)
        *numEventsPtr = *numEventsPtr - 1;
    if(!next){
        if(previous)
            previous->next = nullptr;
    } else{
        previous->next = next;
        next->previous = previous;
    }
    
    if(events)
        events[id] = nullptr; // Only if it has this ptr! Child events (inside an Event) don't hve this set...
    
    vector<Env*>().swap(env); // Clear env vector

    cout << "Event '" << type << "', id: " << id << " deleted!" << endl;
}

void Event::deleteNext(){
    if(next)
        next->deleteNext();
    ownDtor();
    delete this;
}

void Event::update(){
    if(ofGetElapsedTimeMillis() > endTime && active){
        cout << "Event (id:"<<id<<") has passed!" << endl;
        ownDtor();
        
        // Remove from 'vector<Event*> events' in Visualizer (trying to remove, 05-03-19)
        if(parentContainer){
            for(int i=0; i<parentContainer->size(); i++){
                if(parentContainer->at(i) == this){
                    parentContainer->at(i) = nullptr;
                }
            }
        }
        
        
        cout << "Num mappers internal: " << mappers.size() << endl;
//        cout << "Num mappers external: " << 
        // Remove from 'vector<Mappers*> mappers' in Visualizer
        for(int i=0; i<mappers.size(); i++){
            for(int j=0; j<mappersParent->size(); j++){
                if(mappersParent->at(j) == mappers[i]) {
                    mappersParent->at(j) = nullptr;
                    cout << "Deleting one Mapper in delete @ Event" << endl;
                }
            }
        }
        
        delete this;
        return;
    }
    
    
    for(short i=0; i<env.size(); i++){
        if(!env[i]->process()){
            delete env[i]; // Call deconstruct, to free saveBuffer
            env[i] = nullptr;
        }
    }
    
    env.erase( std::remove_if( env.begin(), env.end(), Event::checkIfEnvIsDone ), env.end() );
}

void Event::updateMain(){
    if(next)
        next->updateMain();
    specificFunction();
    update();
}

void Event::displayMain(){
    if(next)
        next->displayMain();
    display();
}

void Event::setEnvelope(int attack, int sustain, int release, ofVec2f range){ // Link envelope to alpha of color & lifetime of object
    Env* e = new Env(vector<float>{range.x, range.y, range.y, range.x}, vector<float>{(float)attack, (float)sustain, (float)release}, &colors[0], 0);
    int totalTime = attack + sustain + release;
    setEndTime(totalTime);
    addEnv(e);
}

//
void Event::setEnvelope(int attack, int sustain, int release, int* value, ofVec2f range){ // Link envelope to int
    Env* e = new Env(vector<float>{range.x, range.y, range.y, range.x}, vector<float>{(float)attack, (float)sustain, (float)release}, value, 0);
    int totalTime = attack + sustain + release;
    setEndTime(totalTime);
    addEnv(e);
}

void Event::setEnvelope(int attack, int sustain, int release, float* value, ofVec2f range, int id, bool bSetEndTime){ // Link envelope to float
    Env* e = new Env(vector<float>{range.x, range.y, range.y, range.x}, vector<float>{(float)attack, (float)sustain, (float)release}, value, 0);
    int totalTime = attack + sustain + release;
    setEndTime(totalTime);
    addEnv(e);
}

void Event::checkBorders(){
    if(bCheckBordersH){
        if(loc.x < 0){
            loc.x = 0;
            direction.x *= -1;
        }
        if((loc.x+size.x) > ofGetViewportWidth()){
            loc.x = ofGetViewportWidth()-size.x;
            direction.x *= -1;
        }
    }
    if(bCheckBordersV){
        if((loc.y+size.y) > ofGetViewportHeight()){
            loc.y = ofGetViewportHeight()-size.y;
            direction.y *= -1;

        }
        if(loc.y < 0){
            loc.y = 0;
            direction.y *= -1;
        }
    }
}

void Event::setType(string type){
    this->type=type;
    cout<<"Made an event of type: " << type << endl;;
};

void Event::test(){
        cout << "Event test()" << endl;
}

Event* Event::getEvent(int index){
    Event* event = this;
    for(int i=0; i<index; i++){
        if(event->next){
            event = event->next;
        }
    }
    return event;
}

void Event::addEvent(Event* toAdd){
    if(!next){
        next = toAdd;
        toAdd->previous = this;
    } else{
        next->addEvent(toAdd);
    }
//    if(next)
//        next->id = id+1;
}

Event* Event::getLast(){
    // Als een Event geen 'next' heeft, returned ie zichzelf, omdat ie de laatste is
    if(next){
        return next->getLast();
    } else{
        return this;
    }
}

void Event::setEndTime(float duration){
    startTime = ofGetElapsedTimeMillis();
    endTime = startTime + duration;
}

void Event::addEventAsFirst(Event* toAdd){
    if(next)
        next->previous = toAdd;
    next = toAdd;
}

void Event::deleteWithFade(short int releaseTime){
    addEnvAlpha(vector<float>{(float)colors[0].a, 0}, vector<float>{(float)releaseTime});
    endTime = ofGetElapsedTimeMillis() + releaseTime;
    active = true;
}

void Event::setColor(ofColor color, int index){
    colors[index] = color;
//    cout << (int)index << " " << color << endl;
}

void Event::makeLinkTap(string name, float* floatPtr, ofVec2f range){
    linkTaps.push_back(new linkTap(name, floatPtr, range));
}

void Event::makeLinkTap(string name, int* intPtr, ofVec2f range){
    linkTaps.push_back(new linkTap(name, intPtr, range));
}

void Event::makeLinkTap(string name, ofColor* colorPtr, ofVec2f range){
    linkTaps.push_back(new linkTap(name, colorPtr, range));
}

linkTap* Event::getLinkTap(string name){
    for(int i=0; i<linkTaps.size(); i++){
        if(linkTaps[i]->name == name){
            return linkTaps[i];
        }
    }
    return nullptr;
}

void Event::addPtr(Event** p){
    toClear.push_back(p);
}

void Event::setAlpha(unsigned char alpha){
    colors[0].a = alpha;
}

bool Event::checkIfEnvIsDone(Env* e){
    if(e == nullptr){
//        cout << "Delete env: done" << endl;
        return true;
    } else{
        return false;
    }
}

void Event::printLinkTaps(){
    for(int i=0; i<linkTaps.size(); i++){
        cout << linkTaps[i]->name << endl;
    }
}

Env* Event::addEnv(Env* e){
    env.push_back(e);
    e->id = env.size();
    e->parentID = &id;
    return e;
}

Env* Event::addEnv(vector<float> levels, vector<float> times, float* f, char curve){
    Env* e = new Env(levels, times, f, curve);
    addEnv(e);
    return e;
}
Env* Event::addEnv(vector<float> levels, vector<float> times, int* i, char curve){
    Env* e = new Env(levels, times, i, curve);
    addEnv(e);
    return e;
}
Env* Event::addEnv(vector<float> levels, vector<float> times, ofColor* c, char curve){
    Env* e = new Env(levels, times, c, curve);
    addEnv(e);
    return e;
}

void Event::loopLastEnv(){
    env.back()->setLoop(true);
}

void Event::addEnvAlpha(vector<float> levels, vector<float> times, char curve){
    Env* e = new Env(levels, times, &colors[0], curve);
    addEnv(e);
}

void Event::addEnvAlpha(float a, float s, float r, float alpha){
    Env* e = new Env(
                     vector<float>{0, (float)colors[0].a, (float)colors[0].a, 0},
                     vector<float>{a, s, r},
                     &colors[0], 0);
    addEnv(e);
}

short Event::getNumEnv(){
    return env.size();
}

Env* Event::getLastEnv(){
    if(env.size()){
        return env.back();
    } else{
        return nullptr;
    }
}

void Event::clearEnv(){
    vector<Env*>().swap(env);
}

bool Event::checkIfEnvExists(char id){
    for(char i=0; i<env.size(); i++){
        if(env[i]->id == id){
            return true;
        }
    }
    return false;
}

void Event::setSize(ofVec3f s){size = s;}
void Event::setMode(char m){ mode = m; }
void Event::setLoc(ofVec3f loc){this->loc = loc;}
