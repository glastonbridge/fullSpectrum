//
//  DuplicationOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 10/04/2013.
//
//

#include "DuplicationOverlay.h"
#include "DancerBlobSensor.h"

/**
 */
 const std::string NAME = "duplication";
 void DuplicationOverlay::update(ofxCvColorImage* input)
{
    LinesOverlay::update(input);
    DancerBlobSensor* sensor = dynamic_cast<DancerBlobSensor *>(sensors[0]);
    // guess dancer position in 2d
    if (sensor->contours.blobs.size() >=1)
    {
        
    }
}
 void DuplicationOverlay::draw()
{
    LinesOverlay::draw();
}
 void DuplicationOverlay::setup(float width, float height)
{
    LinesOverlay::setup(width, height);
}
std::string DuplicationOverlay::getName() {return NAME;};

DuplicationOverlay::DuplicationOverlay()
{
    
}