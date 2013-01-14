//
//  ColourShiftOverlay.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "ColourShiftOverlay.h"

#include "ofMain.h"

const std::string ColourShiftOverlay::NAME="colourshiftoverlay";

void ColourShiftOverlay::setup(float width, float height)
{
    shiftImage.allocate(width, height);
}

void ColourShiftOverlay::update(ofxCvColorImage *input)
{
    shiftImage = *input;
    shiftImage.invert();
}

void ColourShiftOverlay::draw()
{
    shiftImage.draw(0,0);
}
