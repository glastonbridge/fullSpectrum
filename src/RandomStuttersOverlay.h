//
//  RandomStuttersOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/04/2013.
//
//

#ifndef fullSpectrumAnalyser_RandomStuttersOverlay_h
#define fullSpectrumAnalyser_RandomStuttersOverlay_h

#include "StutterOverlay.h"

class RandomStuttersOverlay : public StutterOverlay
{
public:
    static const std::string NAME;
    virtual std::string getName();
    
    RandomStuttersOverlay();
    virtual void update(ofxCvColorImage* input);
    virtual void setup(float width, float height);

private:
    int nextEventCountdown;
    
};


#endif
