//
//  CutOutOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/02/2013.
//
//

#include "CutOutOverlay.h"
#include "ColouredBlobSensor.h"

const std::string CutOutOverlay::NAME = "cut out overlay";
std::string CutOutOverlay::getName() { return NAME; }

CutOutOverlay::CutOutOverlay()
{
    
}

void CutOutOverlay::update(ofxCvColorImage* input)
{
    int width = input->getWidth(), height = input->getHeight();
    ColouredBlobSensor* blobSensor = dynamic_cast<ColouredBlobSensor*> (sensors[0]);
    unsigned char* alphaPixels = blobSensor->val.getPixels();
    unsigned char* colourPixels = input->getPixels();
    if (!displayImage.isAllocated())
    {
        displayImage.allocate(width, height ,GL_RGBA);
        pixels = new unsigned char[width*height*4];
    }
    for (int i = 0; i < width; ++i){
		for (int j = 0; j < height; ++j){
			int pos = (j * width + i);
			pixels[pos*4  ] = colourPixels[pos * 3];
			pixels[pos*4+1] = colourPixels[pos * 3+1];
			pixels[pos*4+2] = colourPixels[pos * 3+2];
			pixels[pos*4+3] = alphaPixels[pos];
		}
    }
    displayImage.loadData(pixels, width, height, GL_RGBA);
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
    glDisable(GL_DEPTH_TEST);
    float width = displayImage.getWidth();
    float height = displayImage.getHeight();
    float scalex = ofGetWidth()/width;
    float scaley = ofGetHeight()/height;
    ofPushMatrix();
    ofScale(scalex, scaley);
    displayImage.draw(0,0);
    ofPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

void CutOutOverlay::setup(float width, float height)
{
    
}
