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
    
    /*if (!displayImage.isAllocated())
    {
        int width = input->getWidth(), height = input->getHeight();
        displayImage.allocate(width, height ,OF_IMAGE_COLOR_ALPHA);
        pixels = new unsigned char[width*height*4];
    }
    setAlphaImage(displayImage, *input, blobSensor->dancerArea, pixels);
    */
    ofEnableAlphaBlending();
    dancerFbo.begin();
    ofClear(0,0,0,0);
    if (blobSensor->dancerVector.size()>10)
    {
        input->draw(0,0);
        
        glColorMask(0, 0, 0, 1);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ofSetColor(0,0,0,255);
        
        //blobSensor->dancerArea.draw(0,0);
        
        ofPath dancerPath;
        dancerPath.setFillColor(ofColor(0,0,0,255));
        dancerPath.setStrokeColor(ofColor(0,0,0,128));
        dancerPath.setStrokeWidth(2);
        
        auto point = blobSensor->dancerVector.begin();
        dancerPath.moveTo(*point);
        ++point;
        for (;point<blobSensor->dancerVector.end(); ++point)
        {
            dancerPath.lineTo(*point);
        }
        dancerPath.close();
        dancerPath.draw(0,0);
        
        
        
        glColorMask(1, 1, 1, 1);
    }
    ofSetColor(255,255,255,255);
    

    dancerFbo.end();
    ofDisableAlphaBlending();
}

void CutOutOverlay::draw()
{
    glDisable(GL_DEPTH_TEST);
    ofEnableAlphaBlending();
    dancerFbo.draw(0,0);
    ofDisableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    return;
    // Attempt to use GL to process alpha channel...
    
    glEnable ( GL_BLEND);
    glDisable (GL_DEPTH_TEST);
    
//    glBlendFunc(GL_DST_COLOR, GL_ZERO);
   // glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ZERO);
    //blobSensor->dancerArea.invert();
    //blobSensor->dancerArea.draw(0,0);

    glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    darnser.draw(0,0);
    glEnable(GL_DEPTH_TEST);
    glDisable (GL_BLEND);
}

void CutOutOverlay::setup(float width, float height)
{
    darnser.allocate(width, height);
    dancerFbo.allocate(width,height,GL_RGBA);
}
