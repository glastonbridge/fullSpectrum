//
//  DuplicationOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 10/04/2013.
//
//

#ifndef fullSpectrumAnalyser_DuplicationOverlay_h
#define fullSpectrumAnalyser_DuplicationOverlay_h

#include "LinesOverlay.h"

class DuplicationOverlay : public LinesOverlay
{
    
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    
    DuplicationOverlay();
};

#endif
