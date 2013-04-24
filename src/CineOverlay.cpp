//
//  CineOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 18/02/2013.
//
//

#include "CineOverlay.h"

const std::string CineOverlay::NAME = "cine overlay";

void CineOverlay::update(ofxCvColorImage* input)
{
    cineFilter.update(input);
}

void CineOverlay::draw()
{
    cineFilter.draw();
}

void CineOverlay::setup(float width, float height)
{
    cineFilter.allocate(width, height);
}
std::string CineOverlay::getName() { return NAME; }
