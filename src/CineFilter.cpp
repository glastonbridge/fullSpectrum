//
//  CineFilter.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 24/04/2013.
//
//

#include "CineFilter.h"

void CineFilter::allocate(float width, float height)
{
    cineImage.allocate(width,height);
    cineFbo.allocate(width,height,GL_RGBA);
    pixelBuffer.allocate(width, height, 4);
    cineImageWithFlickers.allocate(width, height);
}

CineFilter::CineFilter() {}

void CineFilter::update(ofxCvColorImage* input)
{
    cineImage = *input;
    ofEnableAlphaBlending();
    cineFbo.begin();
    ofClear(0,0,0,255);
    
    int cineImageHeight = 0;
    if ((random() & 7) ==0) cineImageHeight -= random() % 5;
    cineImage.draw(0,0);
    
    ofSetColor(10,10,10,255);
    for (int i = 0; i < 15; ++i)
    {
        int speckStartX = rand() % (int)(cineImage.width);
        int speckEndX = speckStartX + rand() % 14 - 5;
        int speckStartY = rand() % cineImage.height;
        int speckEndY = speckStartY + rand() % 14 - 5;
        ofLine(speckStartX, speckStartY, speckEndX, speckEndY);
    }
    ofSetColor(255,255,255,255);
    
    cineFbo.end();
    ofDisableAlphaBlending();
}

void CineFilter::draw()
{
    cineFbo.draw(0,0);
}

ofxCvColorImage& CineFilter::getImage()
{
    cineFbo.readToPixels(pixelBuffer);
    cineImageWithFlickers.setFromPixels(pixelBuffer);
    return cineImageWithFlickers;
}

ofFbo& CineFilter::getFbo()
{
    return cineFbo;
}


