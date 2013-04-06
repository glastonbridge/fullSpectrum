//
//  PlaySoundOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 06/04/2013.
//
//

#ifndef fullSpectrumAnalyser_PlaySoundOverlay_h
#define fullSpectrumAnalyser_PlaySoundOverlay_h

#include "Overlay.h"

class PlaySoundOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    PlaySoundOverlay();
};

#endif
