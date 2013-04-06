//
//  PlaySoundOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 06/04/2013.
//
//

#include "PlaySoundOverlay.h"
#include "Trigger.h"
#include <string>

const std::string PlaySoundOverlay::NAME="play sound";

 void PlaySoundOverlay::update(ofxCvColorImage* input)
{
    if (dynamic_cast<Trigger*>(sensors[0])->triggered())
    {
        std::string soundToPlay = getStringValue(0);
        ofSoundPlayer sound;
        sound.loadSound(soundToPlay);
        sound.play();
    }
    
}

void PlaySoundOverlay::draw() {}

 void PlaySoundOverlay::setup(float width, float height)
{
    
}

std::string PlaySoundOverlay::getName() {return NAME;}

PlaySoundOverlay::PlaySoundOverlay()
{
    addStringParam("soundName", "");
}
