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
    cineImage = *input;
    
    cineFbo.begin();
    ofClear(0,0,0,255);
    
    int cineImageHeight = 0;
    if ((random() & 7) ==0) cineImageHeight -= random() % 5;
    cineImage.draw(0,0);
    
    ofSetColor(10,10,10);
    for (int i = 0; i < 5; ++i)
    {
        int speckStartX = rand() % (int)(cineImage.width);
        int speckEndX = speckStartX + rand() % 14 - 5;
        int speckStartY = rand() % cineImage.height;
        int speckEndY = speckStartY + rand() % 14 - 5;
        ofLine(speckStartX, speckStartY, speckEndX, speckEndY);
    }
    ofSetColor(0xFF, 0xFF, 0xFF);
    
    cineFbo.end();
    
}
void CineOverlay::draw()
{
    cineFbo.draw(0,0);
}
void CineOverlay::setup(float width, float height)
{
    cineImage.allocate(width,height);
    cineFbo.allocate(width,height,GL_RGB);
    cineFbo.begin();
    ofClear(0,0,0,255);
    cineFbo.end();
}
std::string CineOverlay::getName() { return NAME; }
