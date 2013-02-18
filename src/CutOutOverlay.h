//
//  CutOutOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/02/2013.
//
//

#ifndef fullSpectrumAnalyser_CutOutOverlay_h
#define fullSpectrumAnalyser_CutOutOverlay_h

#include "Overlay.h"

class CutOutOverlay : public Overlay
{
    
public:
    static const std::string NAME;
    virtual std::string getName();
    
    CutOutOverlay();
    
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    
private:
    ofTexture displayImage;
    
	unsigned char * pixels ;
};

#endif
