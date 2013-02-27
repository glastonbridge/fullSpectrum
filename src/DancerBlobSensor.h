//
//  DancerBlobSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/02/2013.
//
//

#ifndef fullSpectrumAnalyser_DancerBlobSensor_h
#define fullSpectrumAnalyser_DancerBlobSensor_h

#include "ColouredBlobSensor.h"

class DancerBlobSensor : public ColouredBlobSensor
{
public:
    static const std::string NAME;
    
    DancerBlobSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
};

#endif
