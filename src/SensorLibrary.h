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
#include <map>
#include "Sensor.h"

class SensorLibrary
{
public:
    void onEnterFrame(ofxCvColorImage* input);
    Sensor* addSensor(const std::string& id, const std::string& type);
    /** getActiveSensors is used for debugging purposes in FullSpectrumAnalyser */
    std::vector<Sensor*> getActiveSensors();
    Sensor* activate(const std::string& id, float width, float height);
    
    Sensor*& operator[] (const std::string& index);
    
    void removeSensor(const std::string& id);
private:
    std::vector<Sensor*> activeSensors;
    std::map<std::string, Sensor*> sensors;
    
};

#endif
