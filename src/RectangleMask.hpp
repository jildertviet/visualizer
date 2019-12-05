//
//  RectangleMask.hpp
//  Visualizer_1_4
//
//  Created by Jildert Viet on 15-01-17.
//
//

#ifndef RectangleMask_hpp
#define RectangleMask_hpp

#include <stdio.h>
#include "jRectangle.hpp"
#include "Event.hpp"

class RectangleMask: public Event{
public:
    RectangleMask();
    RectangleMask(jRectangle* rect);
    
    vector<jRectangle*> rects;
    void addRect(jRectangle* r);
    
    void specificFunction();
    void display();
    void addPtr(RectangleMask** p);
    
    vector<int> lefts;
    vector<int> rights;
    
    void randomizeSpeeds();
    void randomizeDirections();
    
    static bool checkIfNull(jRectangle* r);
    
    void findLeftAndRight();
};
#endif /* RectangleMask_hpp */
