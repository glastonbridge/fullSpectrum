//
//  DividedCine.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 24/04/2013.
//
//

#ifndef fullSpectrumAnalyser_DividedCine_h
#define fullSpectrumAnalyser_DividedCine_h

#include "LinesOverlay.h"
#include "CineFilter.h"
#include "ofxCvMain.h"

class DividedCine : public LinesOverlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    
    DividedCine();
private:
    CineFilter cineFilter;
};

#endif
