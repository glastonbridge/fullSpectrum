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
    input->convertToGrayscalePlanarImage(cineImage, 0);
}
void CineOverlay::draw()
{
    cineImage.setROI(cineImage.width/2, 0,cineImage.width/2, cineImage.height);
    int cineImageHeight = 0;
    if ((random() & 7) ==0) cineImageHeight -= random() % 5;
    cineImage.drawROI(cineImage.width/2, cineImageHeight);
    cineImage.setROI(0, 0,cineImage.width, cineImage.height);
    
    ofSetColor(10,10,10);
    for (int i = 0; i < 5; ++i)
    {
        int speckStartX = (cineImage.width /2) + random() % (cineImage.width /2);
        int speckEndX = speckStartX + random() % 14 - 5;
        int speckStartY = random() % cineImage.height;
        int speckEndY = speckStartY + random() % 14 - 5;
        ofLine(speckStartX, speckStartY, speckEndX, speckEndY);
    }
    ofSetColor(0xFF, 0xFF, 0xFF);
}
void CineOverlay::setup(float width, float height)
{
}
std::string CineOverlay::getName() { return NAME; }
