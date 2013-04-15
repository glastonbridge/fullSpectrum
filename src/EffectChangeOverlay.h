//
//  EffectChangeOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/02/2013.
//
//

#ifndef fullSpectrumAnalyser_EffectChangeOverlay_h
#define fullSpectrumAnalyser_EffectChangeOverlay_h

#include "Overlay.h"

class EffectChangeOverlay : public Overlay
{
    
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    EffectChangeOverlay();
    
private:
    float _width, _height;
};

#endif
