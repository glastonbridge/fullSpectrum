//
//  PaddleSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 28/01/2013.
//
//

#ifndef fullSpectrumAnalyser_PaddleSensor_h
#define fullSpectrumAnalyser_PaddleSensor_h

#include "ColouredBlobSensor.h"

class PaddleSensor : public ColouredBlobSensor
{
public:
    static const std::string NAME;
    virtual std::string getName();
    
    virtual void analyse(ofxCvColorImage* input);
    int leftPaddle, rightPaddle;
};

#endif
