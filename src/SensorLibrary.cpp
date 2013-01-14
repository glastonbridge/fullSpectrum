//
//  SensorLibrary.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "SensorLibrary.h"
#include "ColouredBlobSensor.h"

void SensorLibrary::onEnterFrame(ofxCvColorImage *input)
{   
    for(int i = 0; i < sensors.size(); ++i)
        sensors[i]->analyse(input);
}

Sensor* SensorLibrary::addSensor(std::string id, float width, float height)
{
    ColouredBlobSensor* newSensor = new ColouredBlobSensor;
    
    newSensor->setup(width, height);
    sensors.push_back(newSensor);
    return newSensor;
}
