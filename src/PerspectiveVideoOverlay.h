//
//  PerspectiveVideoOverlay.h
//  fullSpectrum
//
//  Created by Alex Shaw on 21/04/2013.
//
//

#ifndef fullSpectrum_PerspectiveVideoOverlay_h
#define fullSpectrum_PerspectiveVideoOverlay_h

#include "LinesOverlay.h"

class PerspectiveVideoOverlay : public LinesOverlay
{
    
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    //virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    
    PerspectiveVideoOverlay();
protected:
    virtual void drawModel();
    
private:
    ofVideoPlayer video;
    ofImage frame;
};

#endif
