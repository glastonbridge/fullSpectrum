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

#import "Parameterisable.h"

class Sensor : public Parameterisable
{
public:
    virtual void setup(float width, float height) = 0;
    
    virtual void analyse(ofxCvColorImage*) = 0;
    
};

#endif
