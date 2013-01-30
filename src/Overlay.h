//
//  Overlay.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_Overlay_h
#define fullSpectrum_Overlay_h

#include "ofxOpenCv.h"

#include "Sensor.h"
#include "Parameterisable.h"

/**
 * The interface which all Overlays must implement
 */
class Overlay : public Parameterisable
{
public:
    virtual void update(ofxCvColorImage* input) = 0;
    virtual void draw() = 0;
    virtual void setup(float width, float height) = 0;
    
    virtual void attachSensor(Sensor* toAttach);
protected:
    vector<Sensor*> sensors;
};

#endif
