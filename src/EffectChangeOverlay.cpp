//
//  EffectChangeOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/02/2013.
//
//

#include "EffectChangeOverlay.h"
#include "KeypressSensor.h"


 const std::string EffectChangeOverlay::NAME="effect change";
void EffectChangeOverlay::update(ofxCvColorImage* input)
{
    if (dynamic_cast<KeypressSensor*>(sensors[0])->triggered())
    {
        std::string effectsToRemove = getStringValue(0);
        while (effectsToRemove.size() > 0)
        {
            std::string nextEffect;
            if (effectsToRemove.find(',')!=std::string::npos)
            {
                nextEffect = effectsToRemove.substr(0,effectsToRemove.find(","));
                effectsToRemove = effectsToRemove.substr(effectsToRemove.find(",")+1);
            }
            else
            {
                nextEffect = effectsToRemove;
                effectsToRemove = "";
            }
            choreography->removeEffect(nextEffect);
        }
    }
}

void EffectChangeOverlay::draw() {}
void EffectChangeOverlay::setup(float width, float height) {}
std::string EffectChangeOverlay::getName() {return NAME;}
EffectChangeOverlay::EffectChangeOverlay()
{
    addStringParam("to remove", "");
    addStringParam("to add", "");
}

