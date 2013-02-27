//
//  DancerBlobSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/02/2013.
//
//

#include "DancerBlobSensor.h"


const std::string DancerBlobSensor::NAME="dancer blob sensor";

DancerBlobSensor::DancerBlobSensor()
{
    setBoolValue(10,true);
};

void DancerBlobSensor::setup(float width, float height)
{
    ColouredBlobSensor::setup(width,height);
}

void DancerBlobSensor::analyse(ofxCvColorImage* input)
{
    ColouredBlobSensor::analyse(input);
    std::vector<ofxCvBlob> shortBlobs;
    for (int i=0; i<contours.blobs.size(); ++i)
    {
        if (contours.blobs[i].boundingRect.height < input->getHeight()/2)
        {
            shortBlobs.push_back(contours.blobs[i]);
        }
    }
    contours.blobs = shortBlobs;
}
std::string DancerBlobSensor::getName() {return NAME;}
