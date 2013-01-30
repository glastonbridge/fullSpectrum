//
//  BlobOverlay.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "BlobOverlay.h"

#include "ColouredBlobSensor.h"

const std::string BlobOverlay::NAME="blob overlay";

BlobOverlay::BlobOverlay()
{
    addBoolParam("draw contours", true);
    addBoolParam("draw hue", false);
    addBoolParam("draw sat", false);
    addBoolParam("draw val", false);
}

void BlobOverlay::setup(float width, float height)
{
}

void BlobOverlay::update(ofxCvColorImage *input)
{
    
}

void BlobOverlay::draw()
{
    if (getBoolValue(0)) (dynamic_cast<ColouredBlobSensor*>(sensors[0]))->contours.draw();
    else if (getBoolValue(1)) (dynamic_cast<ColouredBlobSensor*>(sensors[0]))->hue.draw(0,0);
    else if (getBoolValue(2)) (dynamic_cast<ColouredBlobSensor*>(sensors[0]))->sat.draw(0,0);
    else if (getBoolValue(3)) (dynamic_cast<ColouredBlobSensor*>(sensors[0]))->val.draw(0,0);
    return;
    if((dynamic_cast<ColouredBlobSensor*>(sensors[0]))->contours.blobs.size()<1) return;
    ofPoint blobPoint = (dynamic_cast<ColouredBlobSensor*>(sensors[0]))->contours.blobs[0].pts[0]; //.draw(0,0);
    //blobMarker.draw(blobPoint);
}

std::string BlobOverlay::getName()
{
    return NAME;
}
