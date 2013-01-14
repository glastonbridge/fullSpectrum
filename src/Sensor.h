//
//  Sensor.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_Sensor_h
#define fullSpectrum_Sensor_h

#import "ofxOpenCv.h"

class Sensor
{
public:
    virtual void setup(float width, float height) = 0;
    
    virtual void analyse(ofxCvColorImage*) = 0;
};

#endif
