//
//  CutOutOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/02/2013.
//
//

#include "CutOutOverlay.h"
#include "ColouredBlobSensor.h"

#include "ImageUtils.h"

const std::string CutOutOverlay::NAME = "cut out overlay";
std::string CutOutOverlay::getName() { return NAME; }

CutOutOverlay::CutOutOverlay()
{
    
}

void CutOutOverlay::update(ofxCvColorImage* input)
{
    ColouredBlobSensor* blobSensor = dynamic_cast<ColouredBlobSensor*> (sensors[0]);
    
    if (!displayImage.isAllocated())
    {
        int width = input->getWidth(), height = input->getHeight();
        displayImage.allocate(width, height ,OF_IMAGE_COLOR_ALPHA);
        pixels = new unsigned char[width*height*4];
    }
    setAlphaImage(displayImage, *input, blobSensor->val, pixels);
}

void CutOutOverlay::draw()
{
    /*
    ColouredBlobSensor* blobSensor = dynamic_cast<ColouredBlobSensor*> (sensors[0]);
    glDisable(GL_BLEND);
    glColorMask(0, 0, 0, 1);
    blobSensor->hue.draw(0,0);
    
    glColorMask(1,1,1,0);
    glEnable(GL_BLEND);
    glBlendFunc( GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA );
    
    displayImage->draw(0,0);
     */

    displayImage.draw(0,0);
}

void CutOutOverlay::setup(float width, float height)
{
    
}
