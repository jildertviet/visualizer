//
//  MsgParser.cpp
//  Visualizer_2_5
//
//  Created by Jildert Viet on 05-03-19.
//

#include "MsgParser.hpp"

MsgParser::MsgParser(Visualizer* v){
    this->v = v;
    vector<string> commandKeys = {
        "make",
        "setVal",
        "killAll",
        "addEnv",
        "addTo",
        "doFunc",
        "addConnection",
        "switchRadius",
        "changeAngleOffset",
        "getInfo",
        "linkVecField",
        "getFreePointers",
        "setMasterBrightness",
        "resetCam",
        "setAlpha",
        "setCircularMaskAlpha",
        "setCamEnabled"
    };
    for(short i=0; i<commandKeys.size(); i++){
        string key = "/";
        key += commandKeys[i];
        commands[key] = i + 1;
    }
        
    vector<string> typeKeys = {
        "jRectangle",
        "JVecField",
        "JMirror",
        "JEllipse",
        "JVorm",
        "JSpaceCube",
        "JMultiMesh",
        "JParticles",
        "JText",
        "JMesh",
        "JImage",
        "JDivisionGrid",
        "JVideoPlayer",
        "JShaderTest",
        "JNoise",
        "JLinesFalling",
        "JIFLogo",
        "JPhysarum"
    };
    for(short i=0; i<typeKeys.size(); i++)
        types[typeKeys[i]] = i + 1;
    
    vector<string> valueKeys = {
        "color",
        "loc",
        "size",
        "bMove",
        "speed",
        "direction",
        "lineLength",
        "complexity",
        "density",
        "angle",
        "customArg",
        "bForm",
        "maxSpeed",
        "lijnMax",
        "lineWidth",
        "mode",
        "text",
        "path",
        "rotation",
        "drawMode",
        "alpha",
        "quadColor",
        "sensorAngle",
        "sensorDistance",
        "turnAngle",
        "decay",
        "deposit",
        "balance"
    };
    for(short i=0; i<valueKeys.size(); i++)
        values[valueKeys[i]] = i + 1;
    
    vector<string> envValueKeys = {
        "width",
        "height",
        "brightness",
        "lijnMax",
        "x",
        "y",
        "speed",
        "z",
        "depth",
        "randomPoly",
        "selectedPoly"
    };
    for(short i=0; i<envValueKeys.size(); i++)
        envValues[envValueKeys[i]] = i + 1;
}

//void MsgParser::addEvent(Event* e){
//    v->addEvent(e);
//}

bool MsgParser::parseMsg(ofxOscMessage& m){
//    cout << m.getAddress() << endl;
    switch(commands[m.getAddress()]){
        case 1: // Make
            make(m);
        break;
        case 2: // setVal
            setVal(m);
        break;
        case 3: // killAll
            v->killAll();
            break;
        case 4: // addEnv
            addEnv(m);
            break;
        case 5: // addTo
            addTo(m);
            break;
        case 6:{ // doFunc
            Event* e = v->getEventById(m.getArgAsInt(0));
            if(!e)
                return false;
            switch(m.getArgAsInt(1)){
                case 0:
                    e->customOne();
                    break;
                case 1:
                    e->customTwo();
                    break;
                case 2:
                    e->customThree();
                    break;
                case 3:
                    e->customFour();
                    break;
                case 4:
                    e->customFive();
                    break;
            }
        }
            break;
        case 7:{ // addConnection
            Event* e = v->getEventById(m.getArgAsInt(0));
            if(e && e->type == "Vorm")
                ((Vorm*)e)->addConnection((Vorm*)v->getEventById(m.getArgAsInt(1)));
        }
            break;
        case 8:{ // switchRadius
            Event* e = v->getEventById(m.getArgAsInt(0));
            Event* b = v->getEventById(m.getArgAsInt(1));
            if(e && e->type == "Vorm")
                ((Vorm*)e)->switchRadiusses((Vorm*)b);
            if(m.getArgAsBool(2)){
                if(e)
                    ((Vorm*)e)->instantFormVorm();
                if(b)
                    ((Vorm*)b)->instantFormVorm();
            }
        }
            break;
        case 9:{ // changeAngleOffset
            Event* e = v->getEventById(m.getArgAsInt(0));
            if(e && e->type == "Vorm")
                ((Vorm*)e)->changeAngleOffset(m.getArgAsFloat(1));
        }
            break;
        case 10:{ // getInfo
            switch(m.getArgAsInt(0)){
                case 0: // Get all events
                    SCsender->sendMessage(v->getAllEvents());
                    break;
            }
        }
            break;
        case 11:{ // linkVecField
            Event* e = v->getEventById(m.getArgAsInt(0));
#ifndef TARGET_RASPBERRY_PI
            if(e){
                if(e->type == "particleSystem")
                    ((particleSystem*)e)->setVecField((JVecField*)v->getEventById(m.getArgAsInt(1)));
            }
#endif
        }
            break;
        case 12: // getFreePointers
            v->getFreePointers(); // Sends to 6063, w/ SCsender
            break;
        case 13: // setMasterBrightness
            v->setBrightness(m.getArgAsInt(0));
            break;
        case 14: // resetCam
            v->initCam();
            break;
        case 15: // setAlpha
            v->setAlpha(m.getArgAsInt(0));
            break;
        case 16: // setCircularMaskAlpha
            v->bDrawCirclularMask = m.getArgAsBool(0);
            break;
        case 17:
            v->bCam = m.getArgAsBool(0);
            break;
    }
    return false;
}

bool MsgParser::make(ofxOscMessage& m){
    cout << "Make " << m.getArgAsString(0) << " with ID: " << m.getArgAsInt(1) << endl;
    Event* e = nullptr;
    switch(types[m.getArgAsString(0)]){
        case 1: // jRectangle
            e = new jRectangle();
            break;
        case 2: // vecField
            e = new JVecField();
            ((JVecField*)e)->underlayer = &(v->fbo);
            break;
        case 3: // JMirror
            e = new JMirror();
            break;
        case 4: // JEllipse
            e = new JEllipse();
            break;
        case 5: // JVorm
            if(m.getNumArgs() > 3){
                // Specific constructor ?
                e = new Vorm();
            } else{
                e = new Vorm();
            }
            break;
        case 6: // JSpaceCube
            e = new SpaceCube();
            break;
        case 7: // JMultiMesh
            e = new MultiMesh();
            break;
        case 8:{ // JParticles
//            e = (Event*)new JParticles();
#ifndef TARGET_RASPBERRY_PI
            e = (Event*)new particleSystem(m.getArgAsInt(4), ofVec2f(m.getArgAsInt(5),m.getArgAsInt(6)), ofColor::white, m.getArgAsInt(7));
#endif
//            int idToFind = m.getArgAsInt(5);
//            ((particleSystem*)e)->setVecField((JVecField*)v->getEventById(m.getArgAsInt(5)));
        }
            break;
        case 9:
            e = new jText(&(v->verdana30));
            break;
        case 10:
            e = new JMesh();
            break;
        case 11:
            cout << m.getArgAsString(3) << endl;
            e = new JImage(m.getArgAsString(3));
            break;
        case 12:
            e = new JDivisionGrid();
            break;
        case 13:
            e = new JVideoPlayer();
            break;
        case 14:{
            glm::vec2 size = glm::vec2(m.getArgAsFloat(3), m.getArgAsFloat(4));
            cout << "Size: " << size << endl;
            e = new JShaderTest(size);
//            ((JShaderTest*)e)->mask = &(v->sharedFbo);
//            ((JShaderTest*)e)->src = &(v->sharedFbo2);
        }
            break;
        case 15:
            e = new JNoise();
            break;
        default:
        case 16:
            e = new MultiMeshMaybeTomorrow();
            break;
        case 17:
            e = new IFLogo();
            return false;
            break;
        case 18:
            glm::vec2 size = glm::vec2(m.getArgAsFloat(3), m.getArgAsFloat(4));
            cout << "Create JPhysarum w/ size: " << size << endl;
            e = new JPhysarum(glm::vec2(0, 0), size);
            break;
    }
    
    e->id = m.getArgAsInt(1);
    if(m.getNumArgs() > 2){
        if(m.getArgType(2) == ofxOscArgType::OFXOSC_TYPE_STRING){
            if(m.getArgAsString(2) == "nonCamFront"){
                cout << "Add to nonCamFront layer" << endl;
                v->addEvent(e, VisualizerLayer::NON_CAM_FRONT, e->id);
            } else if(m.getArgAsString(2) == "nonCamBack"){
                cout << "Add to nonCamBack layer" << endl;
                v->addEvent(e, VisualizerLayer::NON_CAM_BACK, e->id);
            }
        } else{
            cout << "Add to layer: " << m.getArgAsInt(2) << endl;
            v->addEvent(e, m.getArgAsInt(2), e->id); // Specific layer
        }
    } else{
        v->addEvent(e, 2, e->id);
    }
return false;
}

void MsgParser::setVal(ofxOscMessage& m){ // Default: /setVal, 0, "size", 100, 200
    Event* e = v->getEventById(m.getArgAsInt(0));
    if(e){
        cout << "Event found, id: " << m.getArgAsInt(0) << ", addr: " << e << endl;
        switch (values[m.getArgAsString(1)]) {
            case 1: // color
                cout << "setColor" << endl;
                if(m.getNumArgs() == 6){ // Set first, global, color
                    e->setColor(ofColor(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4), m.getArgAsInt(5)));
                } else if (m.getNumArgs() == 7){ // Set color @ index of event
                    e->setColor(ofColor(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4), m.getArgAsInt(5)), m.getArgAsInt(6));
                }
            break;
            case 2: // loc
                if(m.getNumArgs() == 4){ // 2D
                    e->setLoc(ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), 0));
                } else if(m.getNumArgs() == 5){ // 3D
                    e->setLoc(ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4)));
                }
                break;
            case 3: // size
                if(m.getNumArgs() == 4){ // 2D
                    e->setSize(ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), 0));
                } else if(m.getNumArgs() == 5){ // 3D
                    e->setSize(ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4)));
                }
                break;
            case 4: // bMove
                e->bMove = m.getArgAsBool(2);
                break;
            case 5: // Speed
//                cout << "Set speed: " << m.getArgAsFloat(2) << endl;
                e->speed = m.getArgAsFloat(2);
                break;
            case 6: // Direction
                e->direction = ofVec2f(m.getArgAsFloat(2), m.getArgAsFloat(3));
                break;
            case 7:{ // lineLength
                // JVecField?
                if(m.getArgAsString(2) == "JVecField"){
                    ((JVecField*)e)->lineLength = m.getArgAsFloat(3);
                }
            }
                break;
            case 8:{ // complexity
                if(m.getArgAsString(2) == "JVecField")
                    ((JVecField*)e)->complexity = m.getArgAsFloat(3);
            }
                break;
            case 9:{ // density
                if(m.getArgAsString(2) == "JVecField") 
                    ((JVecField*)e)->setDensity(glm::vec2(m.getArgAsInt(3), m.getArgAsInt(4)));
            }
                break;
            case 10:{ // angle
                if(m.getArgAsString(2) == "JMirror")
                    ((JMirror*)e)->angle = m.getArgAsInt(3);
            }
                break;
            case 11:{ // customArg
                e->customOneArguments[m.getArgAsInt(2)] = m.getArgAsFloat(3);
            }
                break;
            case 12:{ // bForm
                if(m.getArgAsString(2) == "JVorm")
                    ((Vorm*)e)->setState(m.getArgAsBool(3));
            }
                break;
            case 13:{ // maxSpeed
                if(m.getArgAsString(2) == "JVorm")
                    ((Vorm*)e)->change_maxspeed(m.getArgAsFloat(3), m.getArgAsFloat(4));
            }
            
            case 14:{ // lijnMax
                if(e->type == "Vorm")
                    ((Vorm*)e)->lijnmax = m.getArgAsFloat(2);
            }
                break;
            case 15:{ // lineWidth
                if(e->type == "Vorm"){
                    ((Vorm*)e)->lineWidth = m.getArgAsFloat(2);
                } else if(e->type == "JVecField"){
                    ((JVecField*)e)->lineWidth = m.getArgAsFloat(2);
                }
            }
                break;
            case 16: // mode
                e->setMode(m.getArgAsInt(2));
                break;
            case 17: // text
                ((jText*)e)->setText(m.getArgAsString(2));
                break;
            case 18: // path
                ((JVideoPlayer*)e)->path = m.getArgAsString(2);
                break;
            case 19: // rotation
                e->rotation = ofVec3f(m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4));
                break;
            case 20:{ // drawMode
                if(e->type == "JVecField")
                    ((JVecField*)e)->drawMode = m.getArgAsInt(2);
            }
                break;
            case 21:
                e->setAlpha(m.getArgAsInt(2));
                break;
            case 22:
                if(e->type == "jRectangle"){
                    cout << "setQuadColor" << endl;
                    ofColor a = ofColor(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4));
                    cout << "a: " << a << endl;
                    ((jRectangle*)e)->setQuadColor(
                                    a,
                                    ofColor(m.getArgAsInt(5), m.getArgAsInt(6), m.getArgAsInt(7)),
                                    ofColor(m.getArgAsInt(8), m.getArgAsInt(9), m.getArgAsInt(10)),
                                    ofColor(m.getArgAsInt(11), m.getArgAsInt(12), m.getArgAsInt(13))
                                                   );
                    ((jRectangle*)e)->setAlpha(m.getArgAsInt(14));
                }
            case 23:
                if(e->type == "JPhysarum")
                    ((JPhysarum*)e)->sensorAngle = m.getArgAsFloat(2);
                break;
            case 24:
                if(e->type == "JPhysarum")
                    ((JPhysarum*)e)->sensorDistance = m.getArgAsFloat(2);
                break;
            case 25:
                if(e->type == "JPhysarum")
                    ((JPhysarum*)e)->turnAngle = m.getArgAsFloat(2);
                break;
            case 26:
                if(e->type == "JPhysarum")
                    ((JPhysarum*)e)->decay = m.getArgAsFloat(2);
                break;
            case 27:
                if(e->type == "JPhysarum")
                    ((JPhysarum*)e)->depositAmount = m.getArgAsFloat(2);
                break;
            case 28:
                if(e->type == "JPhysarum")
                    ((JPhysarum*)e)->balance = m.getArgAsFloat(2);
                break;
        }
    } else{
        cout << "Event not found, id: " << m.getArgAsInt(0) << endl;
    }
}

void MsgParser::addTo(ofxOscMessage& m){
    Event* e = v->getEventById(m.getArgAsInt(0));
    if(e){
        switch (values[m.getArgAsString(1)]) {
            case 1:{ // color
                ofColor c = e->colors[0];
                c += ofColor(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4), m.getArgAsInt(5));
                e->setColor(c);
            }
                break;
            case 2:{ // loc
                if(m.getNumArgs() == 4){ // 2d
                    e->setLoc(e->loc + ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), 0));
                } else if(m.getNumArgs() == 5){ // 3d
                    e->setLoc(e->loc + ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4)));
                }
            }
                break;
            case 3: // size
                if(m.getNumArgs() == 4){ // 2d
                    e->size = e->size + ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), 0);
                } else if(m.getNumArgs() == 5){ // 3d
                    e->size = e->size + ofVec3f(m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4));
                }
                break;
        }
    }
}

void MsgParser::addEnv(ofxOscMessage& m){
    Event* e = v->getEventById(m.getArgAsInt(0));
    if(!e)
        return;
    vector<float> times = {m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4)};
    vector<float> values = {m.getArgAsFloat(5), m.getArgAsFloat(6), m.getArgAsFloat(7), m.getArgAsFloat(8)};
    bool bSave = m.getArgAsBool(10); // 9 is killArg
    switch(envValues[m.getArgAsString(1)]){
        case 1: // Width
            e->addEnv(values, times, &(e->size.x));
            break;
        case 2: // Height
            e->addEnv(values, times, &e->size.y);
            break;
        case 3:{ // Brightness
            e->addEnvAlpha(values, times);
            if(m.getArgAsBool(9)){
                e->setEndTime(times[0] + times[1] + times[2] + 1);
                e->active = true;
            }
        }
            break;
        case 4:{ // lijnMax
            if(e->type == "Vorm")
                ((Vorm*)e)->addEnv(values, times, &((Vorm*)e)->lijnmax);
        }
            break;
        case 5: // x
            e->addEnv(values, times, &(e->loc.x));
            break;
        case 6: // y
            e->addEnv(values, times, &(e->loc.y));
            break;
        case 7: // speed
            e->addEnv(values, times, &(e->speed));
            break;
        case 8: // z
            e->addEnv(values, times, &(e->loc.z));
            break;
        case 9: // depth
            e->addEnv(values, times, &(e->size.z));
            break;
        case 10:{ // randomPoly for JDivisonGrid
            Env* envTemp = ((JDivisionGrid*)e)->addEnvRandomPoly(values, times);
            if(bSave) // Saves the envelope as a txt file when done.
                envTemp->setSave();
        }
            return;
            break;
        case 11: {// selectedPoly
            Env* envTemp = ((JDivisionGrid*)e)->addEnvSelectedPoly(values, times);
            if(bSave) // Saves the envelope as a txt file when done.
                envTemp->setSave();
        }
            return;
            break;
    }
    if(bSave){ // Saves the envelope as a txt file when done.
        if(e->getLastEnv())
            e->getLastEnv()->setSave();
    }
}
