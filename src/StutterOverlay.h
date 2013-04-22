//
//  StutterOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/04/2013.
//
//

#ifndef fullSpectrumAnalyser_StutterOverlay_h
#define fullSpectrumAnalyser_StutterOverlay_h

#include "Overlay.h"

class StutterOverlay : public Overlay
{
public: 
    static const std::string NAME;
    virtual std::string getName();
    
    StutterOverlay();
    virtual void update(ofxCvColorImage* input);
    virtual void setup(float width, float height);
    virtual void draw();
    
protected:
    enum {STATE_OFF, STATE_FILLING, STATE_STUTTERING};
    int state;
    void startAStutter(int numFrames, float width, float height);
    void stopStuttering();
private:
    ofxCvColorImage* loopImages;
    unsigned int numLoopImages;
    unsigned int frame;
};

#endif
