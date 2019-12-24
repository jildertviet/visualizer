#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"
#include "JFboWindow.hpp"

// ./visualizer width height framerate numWindows
int main(int argc, char *argv[]){
    shared_ptr<ofApp> app(new ofApp()); // Arguments stuff (for passing ip and UDP-port)
    app->arguments = vector<string>(argv, argv + argc);
    for(int i=0; i<app->arguments.size(); i++)
        cout << "arg[" << i << "]: " << app->arguments[i] << endl;

    
    if(app->arguments.size() > 1){
        if(app->arguments[2] != "YES"){ // arguments[2] is YES when ran from XCode
            app->size = glm::vec2(ofToInt(app->arguments[1]), ofToInt(app->arguments[2]));
            app->frameRate = ofToFloat(app->arguments[3]);
        } // else: default size is set in ofApp.h
    }
    
    ofGLFWWindowSettings mainSettings;
    mainSettings.setGLVersion(2, 1); // (2, 1) for ofxMSAOpenCL
    
    bool bDualWindow = false;
    if(app->arguments.size() >= 5){
        if(ofToInt(app->arguments[4]) == 2)
            bDualWindow = true;
    }
    
    if(bDualWindow){
        cout << "Dual window" << endl;
        shared_ptr<JFboWindow> fboWindow(new JFboWindow());
        ofGLFWWindowSettings secondWindowSettings;
        secondWindowSettings.setGLVersion(2, 1);

        app->size.x *= 0.5;
        app->bUseFbo = true;
        mainSettings.setSize(app->size.x, app->size.y);
        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSettings);
        ofRunApp(mainWindow, app);
        
        secondWindowSettings.setSize(app->size.x, app->size.y);
        secondWindowSettings.resizable = true;
        secondWindowSettings.shareContextWith = mainWindow;
        shared_ptr<ofAppBaseWindow> secondWindow = ofCreateWindow(secondWindowSettings);
        fboWindow->fbo = &(app->f);
        fboWindow->frameRate = ofToFloat(app->arguments[3]);
        ofRunApp(secondWindow, fboWindow);
    } else{
        cout << "Single window" << endl;
        mainSettings.setSize(app->size.x, app->size.y);
        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSettings);
        ofRunApp(mainWindow, app);
    }
    ofRunMainLoop();
}
