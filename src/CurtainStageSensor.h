//
//  CurtainStageSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#ifndef fullSpectrumAnalyser_CurtainStageSensor_h
#define fullSpectrumAnalyser_CurtainStageSensor_h

#import "Sensor.h"

class CurtainStageSensor : public Sensor
{
public: 
    static const std::string NAME;
    
    CurtainStageSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
};

#endif
