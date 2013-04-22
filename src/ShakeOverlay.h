//
//  ShakeOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#ifndef fullSpectrumAnalyser_ShakeOverlay_h
#define fullSpectrumAnalyser_ShakeOverlay_h

#include "LinesOverlay.h"

class ShakeOverlay : public LinesOverlay
{
public:
    static const std::string NAME;
    virtual std::string getName();

    ShakeOverlay();
    virtual void update(ofxCvColorImage* input);
    virtual void setup(float width, float height);
    
    virtual void drawModel();
    
private:
    ofPoint displacement;
    ofPoint velocity;
    float acceleration;
    float damping;
};

#endif
