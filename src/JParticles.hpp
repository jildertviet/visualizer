//
//  JParticles.hpp
//  Visualizer_2_5
//
//  Created by Jildert Viet on 17-04-19.
//

#ifndef JParticles_hpp
#define JParticles_hpp

#include <stdio.h>
#include "JVecField.hpp"
#include "Event.hpp"

struct pingPongBuffer {
public:
    void allocate( int _width, int _height, int _internalformat = GL_RGBA){
        // Allocate
        for(int i = 0; i < 2; i++){
            FBOs[i].allocate(_width,_height, _internalformat );
            FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        }
        
        //Assign
        src = &FBOs[0];
        dst = &FBOs[1];
        
        // Clean
        clear();
    }
    
    void swap(){
        std::swap(src,dst);
    }
    
    void clear(){
        for(int i = 0; i < 2; i++){
            FBOs[i].begin();
            ofClear(0,255);
            FBOs[i].end();
        }
    }
    
    ofFbo& operator[]( int n ){ return FBOs[n];}
    ofFbo   *src;       // Source       ->  Ping
    ofFbo   *dst;       // Destination  ->  Pong
    
private:
    ofFbo   FBOs[2];    // Real addresses of ping/pong FBO«s
};

class JParticles: public Event{
public:
    JParticles();
    
    void display() override;
    void specificFunction() override;
    void setSize(ofVec3f size) override;
    
    JVecField* vecField = nullptr;
    
    ofShader    updatePos;
    ofShader    updateVel;
    ofShader    updateRender;
    
    pingPongBuffer posPingPong;
    pingPongBuffer velPingPong;
    
    ofFbo   renderFBO;
    
    ofFloatPixels p;
    
    float   timeStep;
    float   particleSize;
    
    unsigned long numParticles;
    int textureRes;
    
    ofVboMesh mesh;
    
    ofTexture vecTex;
    ofVec2f getField(ofVec2f pos);
    
    bool bDebug = false;
    
    bool bDrawTexture = false;
    bool bDrawLines = false;
    bool bDrawParticles = true;
    
    float t;
    float complexity = 20; // wind complexity
    float timeSpeed = .005; // wind variation speed
    float phase = TWO_PI; // separate u-noise from v-noise
    bool debugMode = false;
};
#endif /* JParticles_hpp */
