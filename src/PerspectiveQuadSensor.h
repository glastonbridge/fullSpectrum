//
//  PerspectiveQuadSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 16/01/2013.
//
//

#ifndef fullSpectrumAnalyser_PerspectiveQuadSensor_h
#define fullSpectrumAnalyser_PerspectiveQuadSensor_h

#include "ColouredBlobSensor.h"

class PerspectiveQuadSensor : public ColouredBlobSensor
{
public:
    static const std::string NAME;
    virtual std::string getName();
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    
    ofMatrix3x3 warpMatrix;
    
    ofPoint topLeft, topRight, bottomLeft, bottomRight;
    
private:
    CvMat* cvWarpMatrix = cvCreateMat(3,3,CV_32FC1);
};

#endif
