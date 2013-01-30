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
#include "PaddleSensor.h"

void SensorLibrary::onEnterFrame(ofxCvColorImage *input)
{   
    for(int i = 0; i < activeSensors.size(); ++i)
        activeSensors[i]->analyse(input);
}

Sensor* SensorLibrary::activate(const std::string &id, float width, float height)
{
    activeSensors.push_back(sensors[id]);
    sensors[id]->setup(width, height);
    return sensors[id];
}

Sensor* SensorLibrary::addSensor(const std::string& id, const std::string& type)
{
    Sensor* newSensor;
    
    if (type == ColouredBlobSensor::NAME)
    {
        newSensor = new ColouredBlobSensor;
    }
    else if (type == PerspectiveQuadSensor::NAME)
    {
        newSensor = new PerspectiveQuadSensor;
    }
    else if (type == PaddleSensor::NAME)
    {
        newSensor = new PaddleSensor;
    }
    
    sensors[id] = newSensor;
    return newSensor;
}

std::vector<Sensor*> SensorLibrary::getActiveSensors()
{
    return activeSensors;
}
