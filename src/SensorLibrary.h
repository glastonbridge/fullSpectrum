//
//  SensorLibrary.h
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_SensorLibrary_h
#define fullSpectrum_SensorLibrary_h

#include "ofxOpenCv.h"
#include <vector>
#include "Sensor.h"


class SensorLibrary
{
public:
    void onEnterFrame(ofxCvColorImage* input);
    Sensor* addSensor(std::string id, float width, float height);
    std::vector<Sensor*> getActiveSensors();
    
private:
    std::vector<Sensor*> sensors;
};

#endif
