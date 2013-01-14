//
//  ColouredBlobSensor.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "ColouredBlobSensor.h"

const std::string ColouredBlobSensor::NAME = "colouredblobsensor";

void ColouredBlobSensor::setup(float width, float height)
{
    //blues.allocate(width,height);
    hsv.allocate(width,height);
    hue.allocate(width,height);
    huemax.allocate(width, height);
    sat.allocate(width,height);
    val.allocate(width,height);
}

void ColouredBlobSensor::analyse(ofxCvColorImage *input)
{
    hsv = *input;
    hsv.convertRgbToHsv();
    hsv.convertToGrayscalePlanarImages(hue,sat,val);
    huemax = hue;
    int hueRange = 30;
    int hueOffset = 90;
    hue.threshold(hueOffset);
    huemax.threshold(hueOffset + hueRange);
//    huemax.invert();
    hue -= huemax;
    sat.threshold(150);
    hue &= sat;
    //sat.adaptiveThreshold(40);
    val.threshold(100);
    //val.invert();
    hue &= val;
    
//    hue.invert();
//    hue.threshold(160);
//    hue.invert();
    //hsv.setFromGrayscalePlanarImages(hue, sat, val);
    //hsv.convertHsvToRgb();
    //blues.threshold(80);
    contours.findContours(hue, 30, 200*200, 1, false, true);
}
