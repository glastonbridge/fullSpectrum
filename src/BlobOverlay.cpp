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
    ColouredBlobSensor* sensor = dynamic_cast<ColouredBlobSensor*>(sensors[0]);

    if (getBoolValue(0)) sensor->contours.draw();
    else if (getBoolValue(1)) sensor->hue.draw(0,0);
    else if (getBoolValue(2)) sensor->sat.draw(0,0);
    else if (getBoolValue(3)) sensor->val.draw(0,0);
}

std::string BlobOverlay::getName()
{
    return NAME;
}
