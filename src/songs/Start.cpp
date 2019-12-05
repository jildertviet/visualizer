#include "Start.hpp"

Start::Start(Visualizer* v){
    this->v = v;
    cout << "Song: Start" << endl;
    image = (JImage*)v->addEvent(new JImage("Batobe_startscherm.png"));
}

void Start::F0(){ // Test MIDI||
    
}

void Start::F1(){ // ||
    
}

void Start::F2(){ // ||
    
}

void Start::F3(){ // ||
    
}

void Start::F4(){ // ||
    
}

void Start::F5(){ // ||
    
}

void Start::F6(){ // ||
    
}

void Start::F7(){ // ||
    
}

void Start::F8(){ // ||
    
}

void Start::F9(){ // ||
    
}

void Start::F10(){ // ||
    
}

void Start::F11(){ // ||
    
}

void Start::F12(){ // ||
    
}

void Start::F13(){ // ||
    
}

void Start::F14(){ // ||
    
}

void Start::F15(){ // ||
    
}

void Start::C0(int val){ // LED L B||
    
}

void Start::C1(int val){ // LED M B||
    
}

void Start::C2(int val){ // LED R B||
    
}

void Start::C3(int val){ // ||
    
}

void Start::C4(int val){ // ||
    
}

void Start::C5(int val){ // ||
    
}

void Start::C6(int val){ // ||
    
}

void Start::exit(){
    if(image)
        image->deleteWithFade(5000);
}
