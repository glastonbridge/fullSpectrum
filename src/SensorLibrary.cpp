//
//  SensorLibrary.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "SensorLibrary.h"
#include "ColouredBlobSensor.h"
#include "PerspectiveQuadSensor.h"

void SensorLibrary::onEnterFrame(ofxCvColorImage *input)
{   
    for(int i = 0; i < sensors.size(); ++i)
        sensors[i]->analyse(input);
}

Sensor* SensorLibrary::addSensor(std::string id, float width, float height)
{
    Sensor* newSensor;
    
    if (id == ColouredBlobSensor::NAME)
    {
        newSensor = new ColouredBlobSensor;
    }
    else if (id == PerspectiveQuadSensor::NAME)
    {
        newSensor = new PerspectiveQuadSensor;
    }
    
    newSensor->setup(width, height);
    sensors.push_back(newSensor);
    return newSensor;
}

std::vector<Sensor*> SensorLibrary::getActiveSensors()
{
    return sensors;
}
