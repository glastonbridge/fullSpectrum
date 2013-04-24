//
//  CineOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 18/02/2013.
//
//

#ifndef fullSpectrumAnalyser_CineOverlay_h
#define fullSpectrumAnalyser_CineOverlay_h

#include "Overlay.h"
#include "CineFilter.h"

class CineOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
protected:
    
    CineFilter cineFilter;
};

#endif
