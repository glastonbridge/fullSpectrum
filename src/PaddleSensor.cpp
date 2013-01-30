//
//  PaddleSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 28/01/2013.
//
//

#include "PaddleSensor.h"

const std::string PaddleSensor::NAME = "paddle sensor";

std::string PaddleSensor::getName()
{
    return NAME;
}

void PaddleSensor::analyse(ofxCvColorImage* input)
{
    ColouredBlobSensor::analyse(input);
    if (contours.blobs.size()!=2) return;
    
    if (contours.blobs[0].centroid.x<contours.blobs[1].centroid.x)
    {
        leftPaddle = contours.blobs[0].centroid.y;
        rightPaddle = contours.blobs[1].centroid.y;
    }
    else
    {
        leftPaddle = contours.blobs[1].centroid.y;
        rightPaddle = contours.blobs[0].centroid.y;
    }
}
