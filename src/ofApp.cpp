#include "ofApp.h"

#define FULLSCREEN  false

#define FBO_STRETCH_SCREEN  false
#define USE_SERVER  true
#define FBO_DRAW_MIDDLE_ONLY true

//--------------------------------------------------------------
void ofApp::setup() {
    if(bUseFbo){
        left.allocate(size.x, size.y, 3);
//        right.allocate(1280, 800, 3);
        
        ofFbo::Settings fs; // For export quality
        fs.numSamples = 8;
        fs.width = size.x * 2; // Weird to do this here...
        fs.height = size.y;
        fs.internalformat = GL_RGB;
        fs.useStencil = true;
        f.allocate(fs);
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
//        size.x *= 0.5; // TEST (window size is smaller
        texCoords = {glm::vec2(0,0), glm::vec2(size.x, 0), glm::vec2(size.x, size.y), glm::vec2(0, size.y)};
        meshVertices = {glm::vec3(0, 0, 0), glm::vec3(size.x, 0, 0), glm::vec3(size.x, size.y, 0), glm::vec3(0, size.y, 0)};
        for(char i=0; i<4; i++){
            mesh.addTexCoord(texCoords[i] + glm::vec2(size.x, 0)); // Center piece
            mesh.addVertex(meshVertices[i]);
        }
//        size.x *= 2; // TEST
    }

    if(!FULLSCREEN)
        ofSetWindowShape(size.x, size.y); // TEST

    ofSetCircleResolution(360);
    ofSetFullscreen(FULLSCREEN);
    ofBackground(0);
//    ofHideCursor();
    
//    ofSetBackgroundAuto(false);
//    ofSetVerticalSync(true);
    ofSetFrameRate(frameRate);
//    ofEnableSmoothing(); // CAUSES FRAMERATE DROPS
    ofEnableAlphaBlending();
    
    visualizer = new Visualizer();
    visualizer->fitFadeScreen(size); // Also on window-resize!?
    parser = new MsgParser(visualizer);
    
    GUIreceiver.setup(6060);
    SCreceiver.setup(6061);
    spaceNavReceiver.setup(8609);
    visualizer->receiver.setup(4040);
    parser->SCsender = &SCsender;
    visualizer->SCsender = &SCsender;
    
    ofxOscMessage m = visualizer->getAllEvents();
    cout << m.getNumArgs() / 2 << " events" << endl;
    
//    loadSong("CounterParts");
//    visualizer->addEvent((Event*)new JVecField());

//    particleSystem* ps = (particleSystem*)visualizer->addEvent(new particleSystem(2000000), NON_CAM_FRONT);
//
//    JVecField* vecField = (JVecField*)visualizer->addEvent(new JVecField(), NON_CAM_FRONT);
//    vecField->speed = 0.01;
//    vecField->setSize(ofVec3f(1280, 800, 0)); // Should be adjustable!!! (Check particleSystem class)
//    vecField->setDensity(ofVec2f(128, 80));
//    vecField->drawMode = VECFIELD_MODE::HIDE;
//    vecField->mode = VECFIELD_MODE::UNDERLAYING;
//    vecField->complexity = 50;
//    vecField->setColor(ofColor(0, 0, 0, 0)); // Transparant

//    ps->setVecField(vecField);
    
//    JVideoPlayer* v = new JVideoPlayer();
//    v->load("video/mc4.mp4");
//    visualizer->addEvent((Event*)v, NON_CAM_BACK);
    
//    IFLogo* e = new IFLogo(ofVec2f(1280 - 200, 200), ofVec2f(400, 400));
    
//    JShaderTest* e = new JShaderTest(ofVec2f(2560, 800));
//    visualizer->addEvent((Event*)e);
//    e = new JShaderTest(ofVec2f(2560, 800));
//    e->loc = ofVec2f(100, 0);
//    visualizer->addEvent((Event*)e);
}


//--------------------------------------------------------------
void ofApp::update() {
    if(!FULLSCREEN)
        ofSetWindowTitle(ofToString((int)ofGetFrameRate()));

    while(SCreceiver.hasWaitingMessages()){
        msg.clear();
        SCreceiver.getNextMessage(msg);
        if(!bSCClientSet){
            SCsender.setup(msg.getRemoteHost(), 6063);
            bSCClientSet = true;
        }
        parser->parseMsg(msg);
        receive(msg);
    }
    while(GUIreceiver.hasWaitingMessages()){
        msg.clear();
        GUIreceiver.getNextMessage(msg);
        if(!bGUIClientSet){
            GUIsender.setup(msg.getRemoteHost(), 6062);
            bGUIClientSet = true;
        }
        receive(msg);
    }
    while(spaceNavReceiver.hasWaitingMessages()){
        msg.clear();
        spaceNavReceiver.getNextMessage(msg);
        receiveSpaceNav(msg);
    }
    
    if(song)
        song->update();
    
    if(!bUseFbo)
        visualizer->update();

    if(bUseFbo){
        f.begin();
    
        ofClear(0);
        visualizer->update();
        visualizer->display();
        ofNoFill();
        ofSetLineWidth(10);
        ofSetColor(255);
        
//        ofDrawRectangle(0, 0, f.getWidth() * (1/3.) - 5, f.getHeight() - 5);
//        ofDrawRectangle(f.getWidth() * (1/3.), 0, f.getWidth() * (2/3.) - 5, f.getHeight() - 5);
//        ofDrawRectangle(f.getWidth() * (2/3.), 0, f.getWidth() * (3/3.) - 5, f.getHeight() - 5);
//        ofNoFill();
//        ofDrawRectangle(0, 0, f.getWidth() / 3, f.getHeight());
//        ofDrawRectangle((f.getWidth() / 3), 0, f.getWidth() / 3, f.getHeight());
        
        f.end();
        
//        left.begin();
//            f.getTexture().drawSubsection(0, 0, 1280, 800, 0, 0);
//        left.end();
        
//        right.begin();
//            f.getTexture().drawSubsection(0, 0, 1280, 800, 1280*2, 0);
//        right.end();
        
        if(bSaveFbo){
            ofImage i;
            ofPixels p;
            f.readToPixels(p);
            i.setFromPixels(p);
            string t = "frames/";
            t += ofToString(ofGetFrameNum());
            t += ".png";
            i.save(t);
    //        ofSaveFrame();
    //        ofSaveScreen("a.png");
            bSaveFbo = false;
        } else{
    //        ofClear(0);
    //        ofEnableSmoothing();
    //        visualizer->display();
        }
    }
    //if(USE_SERVER && bUseFbo){
  //      syphonServerLeft.publishTexture(&left.getTexture());
//        syphonServerRight.publishTexture(&right.getTexture());
   // }
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    if(bUseFbo){
        switch(fboDisplayMode){
            case 0:
                f.getTexture().bind();
                mesh.draw();
                f.getTexture().unbind();
                if(bEditMode){
                    for(char i=0; i<4; i++)
                        ofDrawCircle(meshVertices[i], 10);
                }
                break;
            case 1: // Stretch
                f.draw(0, 0, ofGetWidth(), ofGetHeight());
                break;
            case 2: //
                f.draw(0, ofGetHeight() * 0.5 - (0.5 * (ofGetHeight() / (f.getWidth() / ofGetWidth()))), ofGetWidth(), ofGetHeight() / (f.getWidth() / ofGetWidth()));
                break;
        }
    } else{
        visualizer->display();
    }
    if(bTemp)
        ofSaveFrame();
}

//--------------------------------------------------------------
void ofApp::exit() {}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    if(visualizer)
        visualizer->fitFadeScreen(glm::vec2(w, h));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch(key) {
//        case 'm':
////            visualizer->bMask = !visualizer->bMask;
//            break;
//        case 's':
//            bSaveFbo = true;
//            bTemp = !bTemp;
//            break;
        case 'r':{
            ofxOscMessage m;
            m.setAddress("/allEvents");
            m.addIntArg(3);
            SCsender.sendMessage(m);
        }
            
            break;
        case 'q':
            fboDisplayMode = 0;
            break;
        case 'w':
            fboDisplayMode = 1;
            break;
        case 'e':
            fboDisplayMode = 2;
            break;
        case 'a':
            bEditMode = !bEditMode;
            break;
        case 'f':{
            mesh.clearVertices();
            vector<ofVec3f> meshVertices(4);
            meshVertices[0] = ofVec3f(0,0);
            meshVertices[1] = ofVec3f(ofGetScreenWidth(), 0);
            meshVertices[2] = ofVec3f(ofGetScreenWidth(), ofGetScreenHeight());
            meshVertices[3] = ofVec3f(0, ofGetScreenHeight());
            for(char i=0; i<4; i++)
                mesh.addVertex(meshVertices[i]);
        }
            break;
	}
    if(song)
        song->key(key);
    if(key == OF_KEY_UP){
        visualizer->cam.setPosition(visualizer->cam.getPosition() - ofVec3f(10, 0, 0));
    } else if(key == OF_KEY_DOWN){
        
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(bEditMode){
        unsigned char indexOfClosest = 0;
        float minDistance = 99999999;
        for(char i=0; i<4; i++){
            if(ofVec2f(x, y).distance(meshVertices[i]) < minDistance){
                minDistance = ofVec2f(x, y).distance(meshVertices[i]);
                indexOfClosest = i;
            }
        }
        cout << "Selected: " << (int)indexOfClosest << endl;
        meshVertices[indexOfClosest] = glm::vec3(x, y, 0);
        mesh.clear();
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        for(char i=0; i<4; i++){
            mesh.addTexCoord(texCoords[i] + ofVec2f(1280, 0)); // Center piece
            mesh.addVertex(meshVertices[i]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::loadSong(string name){
    cout << "Load song: " << name << endl;
    
    bool bStop = true;
    for(int i=0; i<songs.size(); i++){
        if(name==songs[i]){
            bStop = false;
        }
    }
    if(bStop){
        cout << "Song not found" << endl;
        return;
    }
    
    if(song){
        song->exit();
        visualizer->initCam();
        delete song;
    }

    if(name=="Faith"){
        song = new Faith(visualizer);
    } else if(name=="Figgie"){
        song = new Figgie(visualizer);
    } else if(name=="Juncture"){
        song = new Juncture(visualizer);
    } else if(name=="MamaOtis"){
        song = new MamaOtis(visualizer);
    } else if(name=="MaybeTomorrow"){
        song = new MaybeTomorrow(visualizer);
    } else if(name=="TimeForYou"){
        song = new TimeForYou(visualizer);
    } else if(name=="JustBefore"){
        song = new JustBefore(visualizer);
    } else if(name=="BendStraws"){
        song = new BendStraws(visualizer);
    } else if(name=="TeachMe"){
        song = new TeachMe(visualizer);
    } else if(name=="CounterParts"){
        song = new CounterParts(visualizer);
    } else if(name=="Trying"){
        song = new Trying(visualizer);
    } else if(name=="Laura"){
        song = new Laura(visualizer);
    } else if(name=="Start"){
        song = new Start(visualizer);
    } else if(name=="NewOpener"){
        song = new NewOpener(visualizer);
    } else if(name=="OnlyYours"){
        song = new OnlyYours(visualizer);
    } else if(name=="GlassHouse"){
        song = new GlassHouse(visualizer);
    } else if(name =="videoBars"){
        song = new videoBars(visualizer);
    } else if(name == "Spheres"){
        song = new Spheres(visualizer);
    } else if(name == "verses"){
        song = new verses(visualizer);
    } else if(name == "model"){
        song = new model(visualizer);
    }
    ofSetWindowShape(ofGetWidth(), ofGetHeight());
}

void ofApp::receive(ofxOscMessage m){
    cout << "r" << endl;
    string a = m.getAddress();
    if(a == "/DeviceNote" || a == "/GUI"){
        if(song)
            song->doFunc(m.getArgAsInt(0)); // func(int)
    } else if (a == "/DeviceControl"){
        if(song)
            song->doControlFunc(m.getArgAsInt(0), m.getArgAsInt(1));
    } else if(a == "/loadSong"){
        loadSong(m.getArgAsString(0));
    } else if(a == "/setFade"){
        visualizer->fade->setBrightness(m.getArgAsInt(0));
    } else if(a == "/killAll"){
        visualizer->killAll();
    } else if(a == "/bMirror"){
        visualizer->bAddMirror = !(visualizer->bAddMirror);
    } else if(a == "/requestColors"){
        if(song){
            cout << "Received /requestColors" << endl;
            ofxOscMessage m;
            m = song->getColorsAsOSC();
            m.setAddress("/fromVisualizer");
//            m.addStringArg(song->getColorsAsJson().getRawString());
            GUIsender.sendMessage(m, false);
        }
    } else if(a == "/setColor"){
        cout << "setColor" << endl;
        int index = m.getArgAsInt(0);
        ofColor color = ofColor(m.getArgAsInt(1), m.getArgAsInt(2), m.getArgAsInt(3), m.getArgAsInt(4));
        if(song)
            song->setColor(index, color);
    } else if(a == "/setBackground"){
        ofColor c = ofColor(m.getArgAsInt(0), m.getArgAsInt(1), m.getArgAsInt(2));
        visualizer->alphaScreen->setColor(c);
        visualizer->alphaScreen->setActiveness(true);
    } else if(a == "/setMaskBrightness"){
//        cout << m.getArgAsInt(0) << endl;
        unsigned char b = m.getArgAsInt(0);
        if(b == 0){
            visualizer->bMask = false;
        } else{
            if(!visualizer->bMask){
                visualizer->bMask = true;
            }
            visualizer->maskBrightness = b;
        }
    } else if(a == "/loadMask"){
        visualizer->mask.load(m.getArgAsString(0));
        ofFile f;
        f.open("./maskFile.txt", ofFile::Mode::WriteOnly); // Save the path as a default for next start-up :)
        f.clear();
        ofBuffer b;
        b.set(m.getArgAsString(0));
        cout << "Load mask: " << m.getArgAsString(0) << endl;
        f.writeFromBuffer(b);
        f.close();
    } else if(a == "/cmd"){
        if(m.getArgAsString(0) == "make"){
            if(m.getArgAsString(1) == "imageFloat"){
                Event* iF;
                iF = new imageFloat(m.getArgAsString(2));
                visualizer->addEvent(iF);
            } else if(m.getArgAsString(1) == "imageFloaterH" || m.getArgAsString(1) == "imageFloaterV"){
                if(m.getNumArgs() > 5){
                    imageFloater* img;
                    imageFloat* src = (imageFloat*)visualizer->getEventById(m.getArgAsInt(2));
                    bool bHorizontal = false;
                    if(m.getArgAsString(1) == "imageFloaterH")
                        bHorizontal = true;
                    if(src){
                        img = new imageFloater(src);
                        img->loc = ofVec3f(m.getArgAsFloat(3), m.getArgAsFloat(4), m.getArgAsFloat(5));
                        img->size = ofVec3f(m.getArgAsFloat(6), m.getArgAsFloat(7), 0);
                        img->addEnvAlpha(visualizer->vec(0, m.getArgAsFloat(11), 0), visualizer->vec(m.getArgAsFloat(8), m.getArgAsFloat(9), m.getArgAsFloat(10)),  0);
                        img->direction = ofVec3f(m.getArgAsFloat(12), m.getArgAsFloat(13), 0);
                        img->speed = m.getArgAsFloat(14);
                        if(bHorizontal){
                            img->roiSpeed = ofVec2f(ofRandom(0.1, 1.0) - 0.5, 0.);
                            img->roi = ofVec2f(ofRandom(src->getWidth() - img->size.x), 0.); //
                        } else{
                            img->roiSpeed = ofVec2f(0, ofRandom(0.1, 1.0) - 0.5);
                            img->roi = ofVec2f(0., ofRandom(src->getHeight() - img->size.y)); //
                        }
                        visualizer->addEvent((Event*)img);
                    } else{
                        cout << "Img src is nullptr" << endl;
                    }
                }
            } else if(m.getArgAsString(1) == "jText"){
                jText* txt = new jText(&visualizer->verdana30);
                txt->txt = m.getArgAsString(2);
                txt->loc = ofVec2f(m.getArgAsFloat(3), m.getArgAsFloat(4));
                txt->addEnvAlpha(visualizer->vec(0, m.getArgAsFloat(8), 0), visualizer->vec(m.getArgAsFloat(5), m.getArgAsFloat(6), m.getArgAsFloat(7)),  0);
                txt->setColor(ofColor(m.getArgAsFloat(9), m.getArgAsFloat(10), m.getArgAsFloat(11)));
                visualizer->addEvent((Event*)txt);
            }
        } else if(m.getArgAsString(0) == "/camRotEnv"){
            float dur = m.getArgAsFloat(1);
            dur *= 0.5;
            float max = m.getArgAsFloat(2);
            vector<float> values = {0., max, 0.};
            vector<float> times = {dur, dur};
            visualizer->camController->addEnv(values, times, &(visualizer->camController->rotationSpeed.x), 0);
        } else if(m.getArgAsString(0) == "/camBoomEnv"){
            float dur = m.getArgAsFloat(1);
            dur *= 0.5;
            float max = m.getArgAsFloat(2);
            vector<float> values = {0., max, 0.};
            vector<float> times = {dur, dur};
            visualizer->camController->addEnv(values, times, &(visualizer->camController->boomSpeed), 0);
        } else if(m.getArgAsString(0) == "/camTruckEnv"){
            float dur = m.getArgAsFloat(1);
            dur *= 0.5;
            float max = m.getArgAsFloat(2);
            vector<float> values = {0., max, 0.};
            vector<float> times = {dur, dur};
            visualizer->camController->addEnv(values, times, &(visualizer->camController->truckSpeed), 0);
        } else if(m.getArgAsString(0) == "/camDollyEnv"){
            float dur = m.getArgAsFloat(1);
            dur *= 0.5;
            float max = m.getArgAsFloat(2);
            vector<float> values = {0., max, 0.};
            vector<float> times = {dur, dur};
            visualizer->camController->addEnv(values, times, &(visualizer->camController->dollySpeed), 0);
        }
    } else if(a == "/getAllEvents"){
        ofxOscMessage m = visualizer->getAllEvents(); // '/allEvents'
        GUIsender.sendMessage(m);
    }
}

void ofApp::receiveSpaceNav(ofxOscMessage m){
    if(m.getArgAsBool(6))
        visualizer->initCam();

    visualizer->cam.truck(m.getArgAsFloat(0));
    visualizer->cam.dolly(m.getArgAsFloat(1));
    visualizer->cam.boom(m.getArgAsFloat(2));
    
    visualizer->cam.rotate(m.getArgAsFloat(3), ofVec3f(1, 0, 0));
    visualizer->cam.rotate(m.getArgAsFloat(4), ofVec3f(0, 1, 0));
    visualizer->cam.rotate(m.getArgAsFloat(5), ofVec3f(0, 0, 1));
}
