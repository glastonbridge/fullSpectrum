//
//  TeleportOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 27/02/2013.
//
//

#include "TeleportOverlay.h"

static const unsigned int SKIP_COUNT = 4;
static const unsigned int BUFFER_DEPTH = 40;

const std::string TeleportOverlay::NAME = "teleport";

void TeleportOverlay::update(ofxCvColorImage* input)
{
    if (recPos < BUFFER_DEPTH)
    {
        fifo[recPos++] = *input;
    }
}

void TeleportOverlay::draw()
{
    if (playPos>=BUFFER_DEPTH -1) return;
    if(++skips>=SKIP_COUNT)
    {
        skips = 0;
        ++playPos;
    }
    fifo[playPos].draw(0,0);
}

void TeleportOverlay::setup(float width, float height)
{
    recPos = 0; playPos=0; skips = 0;
    //if (fifo) return;
    fifo = new ofxCvColorImage[BUFFER_DEPTH];
}

std::string TeleportOverlay::getName() { return NAME; }
TeleportOverlay::TeleportOverlay() {}