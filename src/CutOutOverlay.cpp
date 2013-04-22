//
//  CutOutOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/02/2013.
//
//

#include "CutOutOverlay.h"
#include "DancerBlobSensor.h"

#include "ImageUtils.h"

const std::string CutOutOverlay::NAME = "cut out overlay";
std::string CutOutOverlay::getName() { return NAME; }

CutOutOverlay::CutOutOverlay()
{
    
}

void CutOutOverlay::update(ofxCvColorImage* input)
{
    
    DancerBlobSensor* blobSensor = dynamic_cast<DancerBlobSensor*> (sensors[0]);
    
    if (!displayImage.isAllocated())
    {
        int width = input->getWidth(), height = input->getHeight();
        displayImage.allocate(width, height ,OF_IMAGE_COLOR_ALPHA);
        pixels = new unsigned char[width*height*4];
    }
    setAlphaImage(displayImage, *input, blobSensor->dancerArea, pixels);
    
    //darnser = *input; uncomment to do GL alphaing
}

void CutOutOverlay::draw()
{
    DancerBlobSensor* blobSensor = dynamic_cast<DancerBlobSensor*> (sensors[0]);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    
    
    glDisable( GL_DEPTH_TEST );
    displayImage.draw(0,0);
    glDisable(GL_BLEND);
    glEnable( GL_DEPTH_TEST );
    
    return;
    // Attempt to use GL to process alpha channel...
    
    glEnable ( GL_BLEND);
    glDisable (GL_DEPTH_TEST);
    
//    glBlendFunc(GL_DST_COLOR, GL_ZERO);
   // glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ZERO);
    //blobSensor->dancerArea.invert();
    blobSensor->dancerArea.draw(0,0);
    

    glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    darnser.draw(0,0);
    glEnable(GL_DEPTH_TEST);
    glDisable (GL_BLEND);
}

void CutOutOverlay::setup(float width, float height)
{
    darnser.allocate(width, height);
}
