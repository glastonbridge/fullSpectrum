//
//  Pose2Sensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/04/2013.
//
//

#ifndef fullSpectrumAnalyser_Pose2Sensor_h
#define fullSpectrumAnalyser_Pose2Sensor_h

#include "ColouredBlobSensor.h"
#include <vector>

class Pose2Sensor : public ColouredBlobSensor
{
public:
    static const std::string NAME;
    
    Pose2Sensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
    
    std::vector<ofPoint> points;

    float averageDistanceShift;
};

#endif
