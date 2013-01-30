//
//  PongOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 28/01/2013.
//
//

#ifndef fullSpectrumAnalyser_PongOverlay_h
#define fullSpectrumAnalyser_PongOverlay_h

#include "Overlay.h"

class PongOverlay : public Overlay
{
public:
    static const std::string NAME;
    std::string getName();
    
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    
private:
    ofPoint _ballPos;
    ofPoint _ballVel;
    float _width, _height;
    
    void resetBall();
};

#endif
