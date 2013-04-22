//
//  ShakeOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#include "ShakeOverlay.h"

const std::string ShakeOverlay::NAME = "shake object";

std::string ShakeOverlay::getName()
{
    return NAME;
}

ShakeOverlay::ShakeOverlay()
{
    addFloatParam("k", 10, 0, 10);
    addFloatParam("m",1,0,10);
    addFloatParam("damping",0,0,1);
    addFloatParam("tick size",1.0/24.0,0,1);
    addFloatParam("initial acceleration", 1,0,10);
}

void ShakeOverlay::setup(float width, float height)
{
    LinesOverlay::setup(width, height);
    displacement.set(0,0,0);
    velocity.set(0,0,0);
    acceleration = getFloatValue("initial acceleration");
}

// F = -kx
// a = F/m
// a = -kx/m
// x = -ma/k
// x/a = -m/k
void ShakeOverlay::update(ofxCvColorImage *input)
{
    LinesOverlay::update(input);
    
    float tickSize = 0.2;//getFloatValue("tick size");
    float dv = acceleration*tickSize;
    for (int i = 0; i < 3; ++i)
    {
        if (displacement[i]<0) displacement[i] += ofRandom(dv);
        else displacement[i] -= ofRandom(dv);
    }
    
    /*
    // update the position based on the velocity, then update the velocity,
    // finally update acceleration
    
    float tickSize = getFloatValue("tick size");
    ofPoint dx = velocity * tickSize * (1 - getFloatValue("damping"));
    displacement += dx;
    
    float dv = acceleration*tickSize;
    for (int i = 0; i < 3; ++i)
    {
        if (displacement[i]>0) velocity[i] += dv;
        else velocity[i] -= dv;
    }
    
    // because x is calculated as a positive displacement and k, m, are positive, a is always negative by a = -kx/m
    float k = getFloatValue("k");
    float m = getFloatValue("m");
    float x = abs(displacement.distance(ofPoint(0,0,0)));
    acceleration = -k*x/m;*/
}

void ShakeOverlay::drawModel()
{
    ofPushMatrix();
    ofTranslate(displacement);
    LinesOverlay::drawModel();
    ofPopMatrix();
}

