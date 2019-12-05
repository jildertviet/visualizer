//
//  TimeForYou.cpp
//  Bas
//
//  Created by Jildert Viet on 23-03-16.
//
//

#include "TimeForYou.hpp"

TimeForYou::TimeForYou(Visualizer* visualizer){
    setName("TimeForYou");
    this->v = visualizer;
    v->bAddMirror = false;
    
    colors.push_back(ofFloatColor(0.6, 0.6, 0.6, 1));
    colors.push_back(ofFloatColor(0.97254901960784,0.7921568627451,0,1));
    colors.push_back(ofFloatColor(0.90980392156863,0.74901960784314,0.33725490196078, 1));
}

void TimeForYou::stop(){
    deleteChorusMeshes();
    deleteVerseMeshes();
}

void TimeForYou::F0(){ // Start ||
    if(bIsStarted)
        return;
    
    if(!bIsStarted)
        bIsStarted = true;

    v->addEvent(new MultiMesh(0));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    v->addEvent(new MultiMesh(0, ofFloatColor(colors[0])));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    v->addEvent(new MultiMesh(0, colors[1]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    v->addEvent(new MultiMesh(0, colors[2]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    for(int i=0; i<meshes.size(); i++){
        MultiMesh* m = meshes[i];
        m->bpm = 85;
        m->generateRandomMeshes(m->numMeshes, m->globalColor);
        m->clearEnv();
        m->addEnv(v->vec(0, 1), v->vec(12500), &m->globalAlpha);
    }
    
}

void TimeForYou::F1(){ // Add mesh to MultiMesh ||
    if(bIsStarted){
        MultiMesh* randomMesh = meshes[ofRandom(meshes.size())];
        int r = ofRandom(3)-1;
        ofFloatColor randomColor;
        if(r==0){
             randomColor = colors[0];
        } else if(r == 1){
                randomColor = colors[1];
            } else if(r == 2){
                randomColor = colors[2];
        }
        randomMesh->addRandomMesh(400.0, randomColor);
    }
}

void TimeForYou::F2(){ // Infinite grow (solo) ||
    F3(); F4(); F4();
//    v->setAlpha(100);
    for(int i=0; i<meshes.size(); i++)
        meshes[i]->bMoveOutVertext = true;
}

void TimeForYou::F3(){ // Chorus ||
    deleteChorusMeshes();
    generateChorusMeshes();
}

void TimeForYou::F4(){ // Move with pulse ||
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->bMoveWithPulse = not(meshes[i]->bMoveWithPulse);
    }
}

void TimeForYou::F5(){ // Delete chorus meshes ||
    deleteChorusMeshes();
}

void TimeForYou::F6(){ //  ||
//    deleteChorusMeshes();
//    bridgeWithoutCenterCircle();
}

void TimeForYou::F7(){ // Add radius ||
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->addRadius(100);
    }
}

void TimeForYou::F8(){ // Verse ||
    deleteVerseMeshes();
    generateVerseMeshes();
}

void TimeForYou::F9(){ // Change one MultiMesh ||
    int randomIndex = ofRandom(meshes.size());

    if(meshes[randomIndex]){
        MultiMesh* mm = meshes[randomIndex];
        int radiusTemp = mm->radius;
        int numMeshesTemp = mm->numMeshes;
        ofFloatColor colorTemp = mm->globalColor;

        mm->deleteWithFade(1);

        addEvent(new MultiMesh(numMeshesTemp, colorTemp));
        mm = nullptr;
        meshes[randomIndex] = (MultiMesh*)(v->getLast());

        meshes[randomIndex]->generateSymmetricMeshes(numMeshesTemp, colorTemp, radiusTemp);
        meshes[randomIndex]->clearEnv();
        meshes[randomIndex]->addEnvAlpha(v->vec(0,255), v->vec(250));

        meshes[randomIndex]->bpm = 85;
        meshes[randomIndex]->setFrequency(85/60, 0.5, 0.25, 0.125);
    }
}

void TimeForYou::F10(){ // Rotate vertices ||
    for(int i=0; i<meshes.size(); i++)
        meshes[i]->doMorph(ofRandom(360)/ofRandom(3000,5000), ofRandom(500,3000));
}

void TimeForYou::F11(){ // Double Time ||
    for(int i=0; i<meshes.size(); i++)
        meshes[i]->doubleTime();
}

void TimeForYou::F12(){ // Half time ||
    for(int i=0; i<meshes.size(); i++)
        meshes[i]->halfTime();
}

void TimeForYou::F13(){ // Change Mode ||
for(int i=0; i<meshes.size(); i++)
    meshes[i]->switchMode();
}



void TimeForYou::generateVerseMeshes(){
    meshes.clear();
    
    v->addEvent(new MultiMesh(4));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(5, ofFloatColor(0.6, 0.6, 0.6, 1)));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(6, colors[1]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(7, colors[2]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->generateRandomMeshes(meshes[i]->numMeshes, meshes[i]->globalColor);
        meshes[i]->clearEnv();
        meshes[i]->addEnv(v->vec(0,1), v->vec(300), &meshes[i]->globalAlpha);

    }
}

void TimeForYou::generateChorusMeshes(){
    meshes.clear();

    v->addEvent(new MultiMesh(24));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(25, ofFloatColor(colors[0])));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(16, colors[1]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(17, colors[2]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    for(int i=0; i<meshes.size(); i++){
        float radius = 350;
        meshes[i]->generateSymmetricMeshes(meshes[i]->numMeshes, meshes[i]->globalColor, radius);
        meshes[i]->clearEnv();
        meshes[i]->addEnv(v->vec(0,200), v->vec(300), &meshes[i]->colors[0]);

        
        meshes[i]->bpm = 85;
        float multipliers [3] = {0.5, 0.25, 0.125};
        meshes[i]->setFrequency(85/60, multipliers, 3);
    }
}

void TimeForYou::deleteVerseMeshes(){
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->deleteWithFade(1000);
        meshes[i] = nullptr;
    }
}

void TimeForYou::deleteChorusMeshes(){
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->bGrowRadius = true;
        meshes[i]->deleteWithFade(1000);
        meshes[i] = nullptr;
    }
    meshes.clear();
}

void TimeForYou::start(){
//    if(!bIsStarted){
//        bIsStarted = 1;
//        meshes.clear();
//    
//        v->addEvent(new MultiMesh(0));
//        meshes.push_back((MultiMesh*)(v->getLast()));
//        v->addEvent(new MultiMesh(0, ofFloatColor(0.6, 0.6, 0.6, 1)));
//        meshes.push_back((MultiMesh*)(v->getLast()));
//        v->addEvent(new MultiMesh(0, ofFloatColor(0.97254901960784,0.7921568627451,0,1)));
//        meshes.push_back((MultiMesh*)(v->getLast()));
//        v->addEvent(new MultiMesh(0, ofFloatColor(0.90980392156863,0.74901960784314,0.33725490196078, 1)));
//        meshes.push_back((MultiMesh*)(v->getLast()));
//    
//        for(int i=0; i<meshes.size(); i++){
//            meshes[i]->bpm = 85;
//            meshes[i]->generateRandomMeshes(meshes[i]->numMeshes, meshes[i]->globalColor);
//            meshes[i]->clearEnv();
//            meshes[i]->addEnv(v->vec(0,1), v->vec(12500), &meshes[i]->globalAlpha);
//        }
//    }
}

void TimeForYou::changeOneMultiMesh(){
    int randomIndex = ofRandom(meshes.size());
    if(meshes[randomIndex]){
        MultiMesh* mm = meshes[randomIndex];
        float radiusTemp = mm->radius;
        int numMeshesTemp = mm->numMeshes;
        ofFloatColor colorTemp = mm->globalColor;
        
        mm->deleteWithFade(1);

        v->addEvent(new MultiMesh(mm->numMeshes, mm->globalColor));
        mm = nullptr;
        meshes[randomIndex] = ((MultiMesh*)v->getLast());

        meshes[randomIndex]->generateSymmetricMeshes(numMeshesTemp, colorTemp, radiusTemp);
        meshes[randomIndex]->clearEnv();
        meshes[randomIndex]->addEnvAlpha(v->vec(0,255), v->vec(250));
        
        meshes[randomIndex]->bpm = 85;
        float multipliers [3] = {0.5, 0.25, 0.125};
        meshes[randomIndex]->setFrequency(85/60, multipliers, 3);
    }
}

void TimeForYou::infiteGrowRadius(){
    deleteChorusMeshes();
    generateChorusMeshes();
    
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->halfTime();
        meshes[i]->halfTime();
    }
    v->setAlpha(100);
    for(int i=0; i<meshes.size(); i++)
        meshes[i]->bMoveOutVertext = true;
}

void TimeForYou::bridgeWithoutCenterCircle(){
    meshes.clear();
    
    v->addEvent(new MultiMesh(24));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(25, colors[0]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(16, colors[1]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    v->addEvent(new MultiMesh(17, colors[2]));
    meshes.push_back((MultiMesh*)(v->getLast()));
    
    for(int i=0; i<meshes.size(); i++){
        float radius = 1;
        meshes[i]->generateSymmetricMeshes(meshes[i]->numMeshes, meshes[i]->globalColor, radius);
        for(int j=0 ; j<meshes[i]->numMeshes; j++){
            meshes[i]->locations[j][0] = ofGetWindowSize()/2.;
        }
        meshes[i]->clearEnv();
        meshes[i]->addEnvAlpha(v->vec(0,255), v->vec(250));
        
        meshes[i]->bpm = 85;
        float multipliers [3] = {0.5, 0.25, 0.125};
        meshes[i]->setFrequency(85/60, multipliers, 3);
    }
    
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->halfTime();
        meshes[i]->halfTime();
        meshes[i]->bMoveOutVertext = true;
    }
    v->setAlpha(100);
}

void TimeForYou::exit(){
    deleteChorusMeshes();
}
