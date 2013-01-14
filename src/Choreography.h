//
//  Choreography.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_Choreography_h
#define fullSpectrum_Choreography_h

#include "OverlayLibrary.h"
#include "SensorLibrary.h"

class Choreography
{
public:
    void setOverlayLibrary(OverlayLibrary* newOverlayLibrary);
    void setSensorLibrary(SensorLibrary* newSensorLibrary);
    void onEnterFrame(float width, float height);
    
private:
    OverlayLibrary* _overlayLibrary;
    SensorLibrary* _sensorLibrary;
};

#endif
