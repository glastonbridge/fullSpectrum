//
//  ColourShiftOverlay.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_ColourShiftOverlay_h
#define fullSpectrum_ColourShiftOverlay_h

#include "Overlay.h"

class ColourShiftOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();  
    virtual void setup(float width, float height);
    virtual std::string getName();
private:
    ofxCvColorImage shiftImage;
};

#endif
