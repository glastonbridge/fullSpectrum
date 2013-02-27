//
//  ParticleStormOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/02/2013.
//
//

#ifndef fullSpectrumAnalyser_ParticleStormOverlay_h
#define fullSpectrumAnalyser_ParticleStormOverlay_h

#include "Overlay.h"

class ParticleStormOverlay : public Overlay
{
    
public:
    static const std::string NAME;
    virtual std::string getName();
    
    ParticleStormOverlay();
    
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);

private:
    std::vector<ofPoint> molecules;

    ofImage displayImage;
    unsigned char * pixels ;
};

#endif
