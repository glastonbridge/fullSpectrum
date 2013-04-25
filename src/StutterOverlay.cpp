//
//  StutterOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/04/2013.
//
//

#include "StutterOverlay.h"

const std::string StutterOverlay::NAME = "stutter";
std::string StutterOverlay::getName() {return NAME;}

StutterOverlay::StutterOverlay() : state(STATE_OFF)
{
    
    addIntParam("loop length", 10, 1, 48);
}

void StutterOverlay::update(ofxCvColorImage* input)
{
    CineOverlay::update(input);
    if (state==STATE_FILLING)
    {
        loopImages[frame] = cineFilter.getImage();
        
        if (frame + 1>=numLoopImages)
        {
            state=STATE_STUTTERING;
        }
    }
    if (state==STATE_STUTTERING)
        *input = loopImages[frame % numLoopImages];
    ++frame;
    
}

void StutterOverlay::startAStutter(int numImages, float width, float height)
{
    numLoopImages = numImages+1;
    loopImages = new ofxCvColorImage[numLoopImages];
    for (int i = 0; i < numLoopImages; ++i)
        loopImages[i].allocate(width, height);
    state=STATE_FILLING;
    frame = 0;
}

void StutterOverlay::stopStuttering()
{
    state=STATE_OFF;
    delete[] loopImages; // This should do destruction, right?
}

void StutterOverlay::setup(float width, float height)
{
    CineOverlay::setup(width, height);
    startAStutter(getIntValue("loop length"), width, height);
}

void StutterOverlay::draw()
{
    if (state==STATE_STUTTERING)
    {
        loopImages[frame % numLoopImages].draw(0,0);
    }
    else
    {
        CineOverlay::draw();
    }
}

