//
//  JParticles.cpp
//  Visualizer_2_5
//
//  Created by Jildert Viet on 17-04-19.
//

#include "JParticles.hpp"

JParticles::JParticles(){
    setSize(ofGetWindowSize());
    
    particleSize = 1.0f;
    timeStep = 0.005f;
    numParticles = 128000;
    
    
    //    vecTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST); // Smooooothness in vecField, forces get interpolated
    
    string shadersFolder;
    if(ofIsGLProgrammableRenderer()){
        shadersFolder="shaders_gl3";
    }else{
        shadersFolder="shaders";
    }
    
    // Loading the Shaders
    if(ofIsGLProgrammableRenderer()){
        updatePos.load(shadersFolder+"/passthru.vert", shadersFolder+"/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels
        updateVel.load(shadersFolder+"/passthru.vert", shadersFolder+"/velUpdate.frag");// shader for updating the texture that store the particles velocity on RG channels
    }else{
        updatePos.load("",shadersFolder+"/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels
        updateVel.load("",shadersFolder+"/velUpdate.frag");// shader for updating the texture that store the particles velocity on RG channels
    }
    
    // Frag, Vert and Geo shaders for the rendering process of the spark image
    updateRender.setGeometryInputType(GL_POINTS);
    updateRender.setGeometryOutputType(GL_POINTS);
    updateRender.setGeometryOutputCount(1);
    updateRender.load(shadersFolder+"/render.vert",shadersFolder+"/render.frag",shadersFolder+"/render.geom");
    
    // Seting the textures where the information ( position and velocity ) will be
    textureRes = (int)sqrt((float)numParticles);
    numParticles = textureRes * textureRes;
    
//    numParticles = textureRes * textureRes;
    
    // 1. Making arrays of float pixels with position information
    vector<float> pos(numParticles*3);
    for (int x = 0; x < textureRes; x++){
        for (int y = 0; y < textureRes; y++){
            int i = textureRes * y + x;
            pos[i*3 + 0] = ofRandom(1.0); //x*offset;
            pos[i*3 + 1] = ofRandom(1.0); //y*offset;
            pos[i*3 + 2] = ofRandom(0.3, 0.8); // Mass?
        }
    }
    // Load this information in to the FBO's texture
    posPingPong.allocate(textureRes, textureRes, GL_RGB32F);
    posPingPong.src->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
    posPingPong.dst->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
    
    // 2. Making arrays of float pixels with velocity information and the load it to a texture
    vector<float> vel(numParticles*3);
    for (unsigned long i = 0; i < numParticles; i++){
        vel[i*3 + 0] = ofRandom(-1.0,1.0);
        vel[i*3 + 1] = 0.;
        vel[i*3 + 2] = 1.0;
    }
    // Load this information in to the FBO's texture
    velPingPong.allocate(textureRes, textureRes, GL_RGB32F);
    velPingPong.src->getTexture().loadData(vel.data(), textureRes, textureRes, GL_RGB);
    velPingPong.dst->getTexture().loadData(vel.data(), textureRes, textureRes, GL_RGB);

    mesh.setMode(OF_PRIMITIVE_POINTS);
    for(int x = 0; x < textureRes; x++){
        for(int y = 0; y < textureRes; y++){
            mesh.addVertex(ofVec3f(x,y));
            mesh.addTexCoord(ofVec2f(x, y));
        }
    }
}

void JParticles::setSize(ofVec3f size){
    this->size = size;
    vecTex.allocate(size.x / 16, size.y / 16, GL_RGB32F);
    // Allocate the final
    renderFBO.allocate(size.x, size.y, GL_RGB32F);
    renderFBO.begin();
    ofClear(0, 0, 0, 255);
    renderFBO.end();
    p.allocate(vecTex.getWidth(), vecTex.getHeight(), 3);
}

void JParticles::display(){
    ofSetColor(255,255,255, 255);
    if(bDrawParticles)
        renderFBO.draw(0,0);
    
//    ofSetColor(255,255,255, 90);
//    if(bDrawTexture)
//    vecTex.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    //    velPingPong.src->getTexture().draw(0, 0, 400, 400);
    //    posPingPong.src->getTexture().draw(400, 0, 400, 400);
    //    vecTex.draw(0, 400, 400, 400);
    
    ofSetColor(255, 100);
    if(bDrawLines){
        ofVec2f start, end;
        for(int i=0; i<vecTex.getWidth(); i++){
            for(int j=0; j<vecTex.getHeight(); j++){
                start = ofVec2f(i, j);
                start *= 16;
                end = start;
                ofVec2f dir = getField(ofVec2f(i, j));
                //            dir.x = ofLerp(-1, 1, dir.x);
                //            dir.y = ofLerp(-1, 1, dir.y);
                end += dir * 10;
                ofDrawLine(start, end);
            }
        }
    }
    
    ofSetColor(255);
    
    if(bDebug){
        posPingPong.src->getTexture().draw(0, 0, ofGetWidth() * 0.5, ofGetHeight() * 0.5);
        velPingPong.src->getTexture().draw(ofGetWidth() * 0.5, 0, ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    }
}

void JParticles::specificFunction(){
    // Update vecField
    t = ofGetFrameNum() * timeSpeed;
    //    vector<float> vecs(vecField.getWidth() * vecField.getHeight() * 3);
    //    p.clear();
    
    for (int i = 0; i < vecTex.getWidth(); i++){
        for(int j=0; j<vecTex.getHeight(); j++){
            //            int index = i * vecField.getHeight() + j;
            //            index *= 3;
            //            float val = getField(ofVec2f(i, j)).x;
            //            vecs[index + 0] = getField(ofVec2f(i, j)).x;
            //            vecs[index + 1] = getField(ofVec2f(i, j)).y;
            //            vecs[index + 2] = 0;
            ofFloatColor c = ofColor::white;
            c.r = getField(ofVec2f(i, j)).x;
            c.g = getField(ofVec2f(i, j)).y;
            p.setColor(i, j, c);
        }
    }
    //    p.setColor(0, 0, ofFloatColor::white);
    
    //    vecField.clear();
    //    vecField.getTexture().loadData(vecs.data(), vecField.getWidth(), vecField.getHeight(), GL_RGB);
    vecTex.loadData(p);
    //    vecTex.loadData(vecs.data(), vecField.getWidth(), vecField.getHeight(), GL_RGB);
    
    
    // In each cycle it's going to update the velocity first and the the position
    // Each one one with a different shader and FBO.
    // Because on GPU you can't write over the texture that you are reading we are
    // using to pair of ofFbo attached together on what we call pingPongBuffer
    // Learn more about Ping-Pong at:
    //
    // http://www.comp.nus.edu/~ashwinna/docs/PingPong_FBO.pdf
    // http://www.seas.upenn.edu/~cis565/fbo.htm#setupgl4
    
    // Velocities PingPong
    //
    // It calculates the next frame and see if it's there any collition
    // then updates the velocity with that information
    //
    velPingPong.dst->begin();
    ofClear(0);
    updateVel.begin();
    updateVel.setUniformTexture("backbuffer", velPingPong.src->getTexture(), 0);   // passing the previus velocity information
    updateVel.setUniformTexture("posData", posPingPong.src->getTexture(), 1);  // passing the position information
    updateVel.setUniformTexture("vecField", vecTex, 2);  // passing the position information
    updateVel.setUniform1i("resolution", (int)textureRes);
    updateVel.setUniform2f("screen", (float)size.x, (float)size.y);
    updateVel.setUniform2f("vecFieldSize", (float)vecTex.getWidth(), (float)vecTex.getHeight());
    updateVel.setUniform1f("timestep", (float)timeStep);
    
    // draw the source velocity texture to be updated
    velPingPong.src->draw(0, 0);
    
    updateVel.end();
    velPingPong.dst->end();
    
    velPingPong.swap();
    
    
    // Positions PingPong
    //
    // With the velocity calculated updates the position
    //
    posPingPong.dst->begin();
    ofClear(0);
    updatePos.begin();
    updatePos.setUniformTexture("prevPosData", posPingPong.src->getTexture(), 0); // Previus position
    updatePos.setUniformTexture("velData", velPingPong.src->getTexture(), 1);  // Velocity
    updatePos.setUniform1f("timestep",(float) timeStep );
    
    // draw the source position texture to be updated
    posPingPong.src->draw(0, 0);
    
    updatePos.end();
    posPingPong.dst->end();
    
    posPingPong.swap();
    
    
    // Rendering
    //
    // 1.   Sending this vertex to the Vertex Shader.
    //      Each one it's draw exactly on the position that match where it's stored on both vel and pos textures
    //      So on the Vertex Shader (that's is first at the pipeline) can search for it information and move it
    //      to it right position.
    // 2.   Once it's in the right place the Geometry Shader make 6 more vertex in order to make a billboard
    // 3.   that then on the Fragment Shader is going to be filled with the pixels of sparkImg texture
    //
    renderFBO.begin();
    ofClear(0,0,0,0);
    updateRender.begin();
    updateRender.setUniformTexture("posTex", posPingPong.dst->getTexture(), 0);
    updateRender.setUniform1i("resolution", (float)textureRes);
    updateRender.setUniform2f("screen", (float)size.x, (float)size.y);
    updateRender.setUniform1f("size", (float)particleSize);
    
    ofPushStyle();
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    ofSetColor(255);
    
    mesh.draw();
    
    ofDisableBlendMode();
    glEnd();
    
    updateRender.end();
    renderFBO.end();
    ofPopStyle();
}

ofVec2f JParticles::getField(ofVec2f position) {
    float normx = ofNormalize(position.x, 0, size.x);
    float normy = ofNormalize(position.y, 0, size.y);
    float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
    float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);

    u = ofLerp(-1, 1, u);
    v = ofLerp(-1, 1, v);
    return ofVec2f(u, v);
}
//
////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//    switch(key){
//        case 'd':
//            bDebug = !bDebug;
//            break;
//        case 'r':{ // RESET
//            // 1. Making arrays of float pixels with position information
//            vector<float> pos(numParticles*3);
//            for (int x = 0; x < textureRes; x++){
//                for (int y = 0; y < textureRes; y++){
//                    int i = textureRes * y + x;
//
//                    pos[i*3 + 0] = ofRandom(1.0); //x*offset;
//                    pos[i*3 + 1] = ofRandom(1.0); //y*offset;
//                    pos[i*3 + 2] = ofRandom(0.3, 0.8);
//                }
//            }
//            // Load this information in to the FBO's texture
//            //            posPingPong.allocate(textureRes, textureRes, GL_RGB32F);
//            posPingPong.src->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
//            posPingPong.dst->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
//        }
//        case '0':
//            bDrawTexture = !bDrawTexture;
//            break;
//        case '1':
//            bDrawLines = !bDrawLines;
//            break;
//        case '2':
//            bDrawParticles = !bDrawParticles;
//            break;
//    }
//}
