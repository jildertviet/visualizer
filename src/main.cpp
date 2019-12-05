#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"
#include "ofAppGLFWWindow.h"

//#define OPENCL  true

int main() {
    // PostProcessing
//    ofAppGlutWindow window;
//    ofSetupOpenGL(&window, 1280, 800, OF_WINDOW);			// <-------- setup the GL context

        // Normaal
//    if(!OPENCL)
//        ofSetupOpenGL(1280, 800, OF_WINDOW);            // <-------- setup the GL context // OUD
// 1920 x 1080
    
//    ofGLFWWindowSettings settings;
//    settings.multiMonitorFullScreen = true;
//    settings.windowMode = OF_FULLSCREEN;
//    ofCreateWindow(settings);
//    ofRunApp(new ofApp());
    
    
    ofGLFWWindowSettings settings; // Shader gedoe
    settings.setGLVersion(2, 1); //we define the OpenGL version we want to use (2, 1) for ofxMSAOpenCL :/
    settings.setSize(1280, 800);
//    settings.width = 1280;
//    settings.height = 800;
    ofCreateWindow(settings);
    
//    // Voor OpenCL
//    if(OPENCL){
//        ofAppGLFWWindow window;
////        ofSetupOpenGL(&window, 1280, 800, OF_FULLSCREEN);
////        window.setGlutDisplayString("rgba double samples>=4");
//        ofSetupOpenGL(&window, 1280, 800, OF_WINDOW);            // <-------- setup the GL context // OUD
////2880 x 1800
//        ofRunApp(new ofApp());
//        return;
//    }
    
    // this kicks off the running of my app
    ofRunApp(new ofApp());
}
