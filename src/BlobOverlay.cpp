//
//  BlobOverlay.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "BlobOverlay.h"

#include "ColouredBlobSensor.h"

const std::string BlobOverlay::NAME="bloboverlay";

void BlobOverlay::setup(float width, float height)
{
    blobMarker.loadImage("smile.png");
    blobMarker.setImageType(OF_IMAGE_COLOR_ALPHA);
}

void BlobOverlay::update(ofxCvColorImage *input)
{
    
}

void BlobOverlay::draw()
{
    if((dynamic_cast<ColouredBlobSensor*>(sensors[0]))->contours.blobs.size()<1) return;
    ofPoint blobPoint = (dynamic_cast<ColouredBlobSensor*>(sensors[0]))->contours.blobs[0].pts[0]; //.draw(0,0);
    blobMarker.draw(blobPoint);
}
