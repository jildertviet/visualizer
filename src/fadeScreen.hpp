//
//  fadeScreen.hpp
//  Visualizer
//
//  Created by Jildert Viet on 13-11-16.
//
//

#ifndef fadeScreen_hpp
#define fadeScreen_hpp

#include <stdio.h>
#include "jRectangle.hpp"
#include "ofMain.h"

class fadeScreen: public jRectangle{
public:
    fadeScreen();
    void display();
    void setBrightness(int alpha);
};
#endif /* fadeScreen_hpp */
