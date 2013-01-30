//
//  PerspectiveImageOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 16/01/2013.
//
//

#include "PerspectiveImageOverlay.h"

#include "PerspectiveQuadSensor.h"

#include <string>

const std::string PerspectiveImageOverlay::NAME="perspective image overlay";

std::string PerspectiveImageOverlay::getName()
{
    return NAME;
}

void PerspectiveImageOverlay::setup(float width, float height)
{
    addBoolParam("show centroids", false);
    
    ofImage loader;
    loader.loadImage("smile.gif");
    loader.setImageType(OF_IMAGE_COLOR);
    
    overlayImage.allocate(loader.width, loader.height);

    displayImage.allocate(width,height);
    translatedImage.allocate(width,height);
    
    overlayImage.setFromPixels(loader.getPixels(), loader.width,loader.height);
    
    srcPoints = new ofPoint[4];
    dstPoints = new ofPoint[4];
    srcPoints[0].x = 0;
    srcPoints[0].y = 0;
    srcPoints[1].x = loader.width;
    srcPoints[1].y = 0;
    srcPoints[2].x = loader.width;
    srcPoints[2].y = loader.height;
    srcPoints[3].x = 0;
    srcPoints[3].y = loader.height;
}

void PerspectiveImageOverlay::update(ofxCvColorImage *input)
{
    displayImage.setFromPixels(input->getPixels(), displayImage.width, displayImage.height);
}

void PerspectiveImageOverlay::draw()
{
    PerspectiveQuadSensor* quadSensor = dynamic_cast<PerspectiveQuadSensor*> (sensors[0]);
    if (getBoolValue(0))
    {
        ofSetColor(255, 0, 0);
        ofCircle(quadSensor->topLeft, 10);
        ofSetColor(255, 255, 0);
        ofCircle(quadSensor->topRight, 10);
        ofSetColor(0, 255, 0);
        ofCircle(quadSensor->bottomLeft, 10);
        ofSetColor(0, 255, 255);
        ofCircle(quadSensor->bottomRight, 10);
        ofSetColor(255,255,255);
    }
    else
    {
        //overlayImage.warpPerspective(quadSensor->topLeft,
        //                             quadSensor->topRight,
        //                             quadSensor->bottomLeft,
        //                             quadSensor->bottomRight);
        
        dstPoints[0] = quadSensor->topLeft;
        dstPoints[1] = quadSensor->topRight;
        dstPoints[2] = quadSensor->bottomRight;
        dstPoints[3] = quadSensor->bottomLeft;
        
        translatedImage.warpIntoMe(overlayImage, srcPoints, dstPoints);
        displayImage += translatedImage;
        displayImage.draw(0,0);
        
        ofMesh bob;
        
        //overlayImage.translate(-quadSensor->topLeft.x, -quadSensor->topLeft.y);
        //overlayImage.draw(quadSensor->topLeft.x,quadSensor->topLeft.y);
    }
}
