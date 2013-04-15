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

/**
 * Represents a thing that regularly looks for an input, either from the camera
 * or from another source such as a network.
 * 
 * There is not (yet?) any standard for getting information out of a sensor, an Overlay
 * must know what kind of sensor it is associated with and cast accordingly.
 *
 * Sensor lifecycle:
 *   Construction: create the data structure and register params but do not allocate image buffers etc. 
 *   setup: construct/load any runtime data like image buffers.
 *   analyse: look at the provided camera input, or any other inputs.
 *
 * TODO: add cleanup to lifecycle
 */
class Sensor : public Parameterisable
{
public:
    virtual void setup(float width, float height) = 0;
    
    virtual void analyse(ofxCvColorImage*) = 0;
    
    virtual bool isPersistent();
};

#endif
