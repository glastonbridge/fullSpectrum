//
//  Choreography.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "Choreography.h"

#include "BlobOverlay.h"
#include "ColourShiftOverlay.h"

#include "ColouredBlobSensor.h"

void Choreography::setOverlayLibrary(OverlayLibrary* newOverlayLibrary)
{
    _overlayLibrary = newOverlayLibrary;
}

void Choreography::setSensorLibrary(SensorLibrary *newSensorLibrary)
{
    _sensorLibrary = newSensorLibrary;
}

void Choreography::onEnterFrame(float width, float height)
{
    static bool runonce = false;
    if ( runonce ) return;
    runonce = true;
    Overlay* newOverlay = _overlayLibrary->addOverlay(BlobOverlay::NAME, width, height);
    newOverlay->attachSensor(_sensorLibrary->addSensor(ColouredBlobSensor::NAME, width, height));
}
