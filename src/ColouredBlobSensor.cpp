//
//  ColouredBlobSensor.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "ColouredBlobSensor.h"

const std::string ColouredBlobSensor::NAME = "coloured blob sensor";

ColouredBlobSensor::ColouredBlobSensor()
{
    addIntParam("hue range", 30, 0, 255); // 0
    addIntParam("hue offset", 90, 0, 255);// 1
    addIntParam("sat threshold",150, -10, 255);// 2
    addIntParam("val threshold", 100, 0, 255); // 3
    
    addIntParam("min blob width", 6, 1, 400); // 4
    addIntParam("max blob width", 200, 5, 800); // 5
    addIntParam("num blobs", 1, 1, 16); // 6
    addBoolParam("val invert", false); // 7
    addBoolParam("sat invert", false); // 8
    addBoolParam("hue invert", false); // 9
    
    addBoolParam("contour on val", false); // 10
}

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
    int hueRange = getIntValue(0);
    int hueOffset = getIntValue(1);
    hue.threshold(hueOffset);
    huemax.threshold(hueOffset + hueRange);
    hue -= huemax;
    
    int valVal = getIntValue(3);
    val.threshold(valVal);
    bool valInv = getBoolValue(7);
    if (valInv) val.invert();
    
    sat.threshold(getIntValue(2));
    if (getBoolValue(8)) sat.invert();
    
    if (getBoolValue(9)) hue.invert();
    
    sat &= val;
    hue &= sat;
    
    
    int minBlob = getIntValue(4);
    int maxBlob = getIntValue(5);
    int numBlobs = getIntValue(6);
    contours.findContours(getBoolValue(10)?val:hue, minBlob*minBlob, maxBlob * maxBlob, numBlobs, false, true);
}

std::string ColouredBlobSensor::getName()
{
    return "coloured blob sensor";
}
