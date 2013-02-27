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
#include "Choreography.h"

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
    
    
    /** 
     * Geometry exists because the Full Spectrum Analyser struggles to set the correct perspective from
     * a shrunk GL viewport.  If we could consistently change the viewport centre without mucking up
     * image scaling, we could do away with this information.
     *
     * It should not have any bearing on the iPad app, which is always fullscreen
     */
    static const int ORTHO = 1;
    static const int PERSPECTIVE = 2;
    virtual int getGeometry();
    
    /**
     * The overlay can interact with the choreographic model
     */
    virtual void setChoreography(Choreography* newChoreography);
    
protected:
    vector<Sensor*> sensors;
    Choreography* choreography;
};

#endif
