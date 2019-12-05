#include "BendStraws.hpp"

BendStraws::BendStraws(Visualizer* v){
    setName("BendStraws");
    this->v = v;
    
    char preset = ofRandom(3);
//    preset = 2;
    switch (preset) {
            case 0:
            divisions = {2, 4, 6, 7, 2, 4, 6, 7, 2};
            radiuses = {90, 140, 230, 320, 130, 170, 260, 350, 110};
            shape = 6;
            break;
            
            case 1:
            divisions = {2, 4, 6, 7, 2, 4, 6, 7, 2};
            radiuses = {50, 140, 230, 320, 80, 170, 260, 350, 110};
            shape = 8;
            break;
            
            case 2:
            divisions = {2, 4, 6, 7, 2, 4, 6, 7, 2};
            radiuses = {50, 140, 230, 320, 80, 170, 260, 350, 110};
            for(char i=0; i<radiuses.size(); i++)
            radiuses[i] *= 1.3;
            shape = 9;
            break;
        default:
            break;
    }
//    cout << "Preset: " << (int)preset << endl;
    
    C2(127);
}

void BendStraws::stop(){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->active = true;
        vormen[i]->addEnvAlpha(1, 1, 3000);
    }
}

void BendStraws::addVorm(){
    if(vormen.size()<maxVorm){
        addEvent(new Vorm(shape, divisions[vormen.size()], radiuses[vormen.size()], ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight()/2.), false));
        Vorm* last = ((Vorm*)v->getLast());
        vormen.push_back(last);
        last->formVorm();
//        last->setZ(ofRandom(200));
    
        last->change_maxspeed(1.0*0.8, 1.5*0.5);
        last->alphaAdd = 10; // ?
//        v->addMapper(new Mapper(&(v->mappers), last, "/2", "lijnmax", last->getLinkTap("lijnmax")));
        
//        last->particlesVisible = true;
        last->lijnmax = pow(40.0, 2.0);
        last->lineWidth = 3;
        if(lastVorm)
            lastVorm->addConnection(last);
        lastVorm = last;
    } else{
        cout << "Max Vorm amount ("<<(int)maxVorm<<") reached"<<endl;
    }
}

void BendStraws::F0(){ // Add Vorm||
    addVorm();
}
void BendStraws::F1(){ // Switch radius||
    switchRadiusses(false);
}
void BendStraws::F2(){ // Switch radius instant||
    switchRadiusses(true);
}
void BendStraws::F3(){ // Switch radius instant + noise||
    switchRadiusses(false);
    addNoise();
}

void BendStraws::F4(){ // Rotate vorm||
    rotateVorm();
}

void BendStraws::F5(){ // Form all Vorms||
    formAllVorms();
}

void BendStraws::F6(){ // OneFrame||
    oneFrame();
}

void BendStraws::F7(){ // AddNoise||
    addNoise();
}

void BendStraws::F8(){ // Default LineMax||
    setLineMax(pow(40.0, 2.0));
}

void BendStraws::F9(){ // Random Line Max||
    randomLineMax(pow(40.0, 2.0), pow(110.0, 2.0));
}

void BendStraws::F10(){ // White gradient||
    v->alphaScreen->gradientColor = ofColor(180);
    v->alphaScreen->bGradient = !v->alphaScreen->bGradient;
}

void BendStraws::F11(){ // Free/Form Vorm||
    for(int i=0; i<vormen.size(); i++)
        vormen[i]->switchState();
}

void BendStraws::F12(){ // TRANSFORM ||
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->deleteWithFade(10);
    }
    vormen.clear();
    for(int i=0; i<5; i++){
        Vorm* vorm = (Vorm*)v->addEvent(new Vorm(4, 4+i, 400, ofGetWindowSize()/2., true));
        vorm->circleRatio = ofVec2f(1,1);
//        vorm->center += ofVec2f(0, ofGetWindowHeight()*0.5);
        vorm->makeCoordinates(4, 4+i, 200+(50*i));
        vorm->formVorm();
        vorm->change_maxspeed(25);
        vorm->instantFormVorm();
        vorm->lineWidth = 3;
        vormen.push_back(vorm);
//        if(vormen.size()>1)
//            vormen[vormen.size()-1]->addConnection(vormen[vormen.size()-2]);
    }
    for(int i=0; i<vormen.size(); i++){
        for(int j=i; j<vormen.size(); j++){
            vormen[i]->addConnection(vormen[j]);
        }
    }
}

void BendStraws::F13(){ // Env @ linemax ||
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->setEnvelope(10, 10, 800, &vormen[i]->lijnmax, ofVec2f(40*40, vormen[i]->lijnmax*2));
    }
}

void BendStraws::F14(){} // LED side||
void BendStraws::F15(){} // ||

void BendStraws::C0(int val){ // Line-speed||
    float speed = ofMap(val, 0, 127, 0.1, 14);
    for(int i=0; i<vormen.size(); i++)
        vormen[i]->change_maxspeed(speed);
//    for(int i=0; i<vormen.size(); i++){
//        for(int j=0; j<vormen[i]->linkTaps.size(); j++){
//            vormen[i]->linkTaps[j]->setWeight(ofMap(val, 0., 127., 0., 1.));
//        }
//    }
}

void BendStraws::C1(int val){ // Lijn-max ||
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->lijnmax = ofMap(val, 0, 127, pow(40, 2), pow(90, 2));
    }
}

void BendStraws::C2(int val){ // Rel time delete ||
    deleteFade = ofMap(val, 0, 127, 10000, 30000);
}

void BendStraws::addNoise(){
    for(int i=0; i<vormen.size(); i++){
        for(int j=0; j<vormen[i]->getNumParticles(); j++){
            vormen[i]->particles[j]->addNoise = true;
        }
    }
}

void BendStraws::randomLineMax(int min, int max){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->lijnmax = ofRandom(min, max);
    }
}

void BendStraws::setLineMax(int val){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->lijnmax = val;
    }
}

void BendStraws::switchRadiusses(bool instant){
    if(vormen.size()<2)
        return;
    int oneTemp = ofRandom(vormen.size());
    int twoTemp = ofRandom(vormen.size());
    while(oneTemp == twoTemp){
        twoTemp = ofRandom(vormen.size());
    }
    vormen[oneTemp]->switchRadiusses(vormen[twoTemp]);
    if(instant){
        vormen[oneTemp]->instantFormVorm();
        vormen[twoTemp]->instantFormVorm();
    }
}

void BendStraws::rotateVorm(){
    if(vormen.size()==0)
        return;
    int oneTemp = ofRandom(vormen.size());
    if(ofRandom(-1,1) > 0){
        vormen[oneTemp]->changeAngleOffset(15);
    } else{
        vormen[oneTemp]->changeAngleOffset(-15);
    }
}

void BendStraws::oneFrame(){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->showFrame = true;
    }
}

void BendStraws::formAllVorms(){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->instantFormVorm();
    }
}

void BendStraws::exit(){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->deleteWithFade(deleteFade);
    }
}
