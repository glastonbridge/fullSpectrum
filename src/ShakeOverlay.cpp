//
//  ShakeOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#include "ShakeOverlay.h"

const std::string ShakeOverlay::NAME = "shake overlay";

std::string ShakeOverlay::getName()
{
    return NAME;
}

ShakeOverlay::ShakeOverlay()
{
    addFloatParam("xtension",1,0,4);
    addFloatParam("xdamping",0.02,0,4);
    addFloatParam("xoffset",0,-100,100);
    addFloatParam("xvelocity", 0, -10,10);
    addFloatParam("xscale",1,0,10);
}

void ShakeOverlay::setup(float width, float height)
{
    
}

void ShakeOverlay::update(ofxCvColorImage *input)
{
    overlayImage = input;
    float xtension = getFloatValue(0), xdamping = getFloatValue(1),
    xoffset = getFloatValue(2), xvelocity = getFloatValue(3);
    
    xtension *= xoffset * xdamping;
    xvelocity -= xtension;
    xoffset += xvelocity;
    float xscale = 1 + 2 * abs(xoffset) / input->getWidth();
    
    setFloatValue(2, xoffset);
    setFloatValue(3, xvelocity);
    setFloatValue(4, xscale);
}

void ShakeOverlay::draw()
{
    ofScale(getFloatValue(4), 1);
    overlayImage->draw(getFloatValue(2),0);
}