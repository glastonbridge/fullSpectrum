//
//  CubeRainOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/04/2013.
//
//

#ifndef fullSpectrumAnalyser_CubeRainOverlay_h
#define fullSpectrumAnalyser_CubeRainOverlay_h

#include "GravityStageOverlay.h"

class CubeRainOverlay : public GravityStageOverlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void drawModel();
    virtual void setup(float width, float height);
    virtual std::string getName();
    CubeRainOverlay();
};

#endif
