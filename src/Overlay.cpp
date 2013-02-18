//
//  Overlay.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "Overlay.h"

void Overlay::attachSensor(Sensor *toAttach)
{
    sensors.push_back(toAttach);
}

int Overlay::getGeometry()
{
    return ORTHO;
}
