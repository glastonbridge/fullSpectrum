//
//  EffectChangeOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/02/2013.
//
//

#include "EffectChangeOverlay.h"
#include "Trigger.h"


 const std::string EffectChangeOverlay::NAME="effect change";
void EffectChangeOverlay::update(ofxCvColorImage* input)
{
    if (dynamic_cast<Trigger*>(sensors[0])->triggered())
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
        std::string effectsToAdd = getStringValue(1);
        while (effectsToAdd.size() > 0)
        {
            std::string nextEffect;
            if (effectsToAdd.find(',')!=std::string::npos)
            {
                nextEffect = effectsToAdd.substr(0,effectsToAdd.find(","));
                effectsToAdd = effectsToAdd.substr(effectsToAdd.find(",")+1);
            }
            else
            {
                nextEffect = effectsToAdd;
                effectsToAdd = "";
            }
            choreography->activateEffect(nextEffect, _width, _height);
        }
    }
}

void EffectChangeOverlay::draw() {}
void EffectChangeOverlay::setup(float width, float height)
{
    _width = width; _height = height;
}

std::string EffectChangeOverlay::getName() {return NAME;}
EffectChangeOverlay::EffectChangeOverlay()
{
    addStringParam("to remove", "");
    addStringParam("to add", "");
}

