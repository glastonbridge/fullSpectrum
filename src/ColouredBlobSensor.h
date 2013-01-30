//
//  ColouredBlobSensor.h
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_ColouredBlobSensor_h
#define fullSpectrum_ColouredBlobSensor_h

#import "Sensor.h"

class ColouredBlobSensor : public Sensor
{
public:
    static const std::string NAME;
    
    ColouredBlobSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
    ofxCvContourFinder contours;    
    //ofxCvGrayscaleImage reds, greens, blues;
    ofxCvGrayscaleImage hue, huemax, sat, val;
    ofxCvColorImage hsv;
    
private:
};

#endif
