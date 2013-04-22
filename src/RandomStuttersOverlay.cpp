//
//  RandomStuttersOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/04/2013.
//
//

#include "RandomStuttersOverlay.h"

 const std::string RandomStuttersOverlay::NAME="random stutters";
std::string RandomStuttersOverlay::getName() {return NAME;};

RandomStuttersOverlay::RandomStuttersOverlay()
{
    addIntParam("max wait frames", 60,1,200);
    addIntParam("max stutter length", 60, 1, 200);
}

 void RandomStuttersOverlay::update(ofxCvColorImage* input)
{
    StutterOverlay::update(input);
    if (--nextEventCountdown<=0)
    {
        if (state==STATE_OFF)
        {
            startAStutter(ofRandom(getIntValue("max stutter length")), input->getWidth(), input->getHeight());
            nextEventCountdown = getIntValue("max stutter length");
        }
        else if (state==STATE_STUTTERING)
        {
            stopStuttering();
            nextEventCountdown = ofRandom(getIntValue("max wait frames"));
        }
    }
}

 void RandomStuttersOverlay::setup(float width, float height)
{
    // don't call through to super, as that just triggers a stutter
    nextEventCountdown = getIntValue("max wait frames");
}

