//
//  TeleportOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 27/02/2013.
//
//

#ifndef fullSpectrumAnalyser_TeleportOverlay_h
#define fullSpectrumAnalyser_TeleportOverlay_h

#include "Overlay.h"

class TeleportOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    TeleportOverlay();
private:
    ofxCvColorImage* fifo;
    unsigned int skips;
    unsigned int recPos, playPos;
};

#endif
