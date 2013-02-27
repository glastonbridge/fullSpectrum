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
#include "CurtainStageSensor.h"
#include "DancerBlobSensor.h"
#include "KeypressSensor.h"

#include <algorithm>

void SensorLibrary::onEnterFrame(ofxCvColorImage *input)
{   
    for(int i = 0; i < activeSensors.size(); ++i)
        activeSensors[i]->analyse(input);
}

Sensor* SensorLibrary::activate(const std::string &id, float width, float height)
{
    bool alreadyActive(false);
    for (std::vector<Sensor*>::const_iterator s = activeSensors.begin();
         s < activeSensors.end();
         ++s)
    {
        if ( (*s)->getInstanceName() == id)
        {
            alreadyActive = true;
            break;
        }
    }
    if (!alreadyActive)
    {
        activeSensors.push_back(sensors[id]);
        sensors[id]->setup(width, height);
    }
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
    else if (type == CurtainStageSensor::NAME)
    {
        newSensor = new CurtainStageSensor;
    }
    else if (type == DancerBlobSensor::NAME)
    {
        newSensor = new DancerBlobSensor;
    }
    else if (type == KeypressSensor::NAME)
    {
        newSensor = new KeypressSensor;
    }
    newSensor->setInstanceName(id);
    sensors[id] = newSensor;
    return newSensor;
}

Sensor*& SensorLibrary::operator[] (const std::string& index)
{
    return sensors[index];
}

std::vector<Sensor*> SensorLibrary::getActiveSensors()
{
    return activeSensors;
}

void SensorLibrary::removeSensor(const std::string& id)
{
    std::vector<Sensor *>::iterator sensorToRemove = std::find(activeSensors.begin(), activeSensors.end(), sensors[id]);
    if (sensorToRemove != activeSensors.end()) activeSensors.erase(sensorToRemove);
}

