//
//  ShakeOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#ifndef fullSpectrumAnalyser_ShakeOverlay_h
#define fullSpectrumAnalyser_ShakeOverlay_h

#include "Overlay.h"

class ShakeOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual std::string getName();

    ShakeOverlay();
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
private:
    ofxCvColorImage* overlayImage;
};

#endif
