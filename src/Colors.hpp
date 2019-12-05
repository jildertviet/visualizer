//
//  Colors.hpp
//  Visualizer
//
//  Created by Jildert Viet on 29-10-16.
//
//

#ifndef Colors_hpp
#define Colors_hpp

#include <stdio.h>
#include "ofMain.h"

class Palette{
public:
    Palette(vector<ofColor> v, string n){
        vec = v;
        name = n;
    }
    vector<ofColor> vec;
    string name = "";
};

class Colors{
public:
    Colors(){
        availableColors.push_back("figgieDakota");
        availableColors.push_back("firstPalette");
        availableColors.push_back("figgieMisch");
        availableColors.push_back("BatobeTeachMe");
        availableColors.push_back("TeachMeBlue");

        
        cout << "Colors made" << endl;
        vector<ofColor> colors1 {
                ofColor(231,71,72),
                ofColor(230,132,53),
                ofColor(243,207,34),
                ofColor(237,229,116),
                ofColor(225,245,196)
        };
        
        Palette firstPalette(colors1, "firstPalette");
        colors.push_back(firstPalette);
        
        vector<ofColor> colors4 {
            ofColor(232,221,203),
            ofColor(205,179,128),
            ofColor(3,101,100),
            ofColor(3,54,73),
            ofColor(3,22,52)
        };
        
        colors.push_back(
                         Palette(
                         vector<ofColor>{
                             ofColor(232,243,248),
                             ofColor(219,230,236),
                             ofColor(194,203,206),
                             ofColor(164,188,194),
                             ofColor(129,168,184)
                         },
                         "TeachMeBlue"
                        )
        );

        
//        Palette secondPalette(colors4, "BatobeTeachMe");
        colors.push_back(Palette(colors4, "BatobeTeachMe"));

        
        vector<int> hexValues { // Figgie / Dakota
            0xFFD756,
            0xFC794C,
            0x9B3D70,
            0x7E48D1,
            0x5330B2,
            0x41608C
        };
        
        
        vector<int> figgieMisch { // Figgie / Dakota
            0x402E58,
            0x5C23BB,
            0xB9737F,
            0x8C5B6A,
            0x112F6A,
            0xB87180,
            0x556485,
            0xF2918B,
            0x3C303D,
            0x83C0B6,
            0x0E0026,
            0xCF7967,
            0x0B857C,
            0x887393,
            0x337D77,
            0xD28259,
            0xE063D5,
            0xB99375,
            0x70E0CF,
            0x6DD498,
            0x6FB120,
            0x33C886,
            0x935B4A,
            0x34D2BF,
            0x33CD89,
            0x213032
        };
        vector<ofColor> colors2;
        vector<ofColor> colors3;
        setFromHexColors(&colors2, hexValues);
        setFromHexColors(&colors3, figgieMisch);
        
//        cout << "colors3 size: " << colors3.size() << endl;
        
        Palette p(colors2, "figgieDakota");
        Palette pa(colors3, "figgieMisch");

        colors.push_back(p);
        colors.push_back(pa);
        
    }
    
    vector<string> availableColors;
    vector<Palette> colors;
    
    void setFromHexColors(vector<ofColor>* vec, vector<int> hex){
        for(int i=0; i<hex.size(); i++){
            ofColor c;
            c.setHex(hex[i]);
            vec->push_back(c);
        }
    }
    
    Palette getByName(string name){
        for(int i=0; i<colors.size(); i++){
            if(colors[i].name == name){
                return colors[i];
            }
        }
        return Palette(vector<ofColor>{ofColor(255)}, "empty");
    }
    
    ofColor getRandomColor(string name){
//        p = getByName(name);
        ofColor c = ofColor(255);
        if(getByName(name).name != "empty"){
//            cout << "Vector size: " << (getByName(name).vector).size() << endl;
//            cout << "Vector name: " << getByName(name).name << endl;
            int index = ofRandom((getByName(name).vec).size()-1);
            c = getByName(name).vec[index];
        }
        return c;
    }
};
#endif /* Colors_hpp */
