//
//  OverlayLibrary.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include <algorithm>

#include "OverlayLibrary.h"
#include "ColourShiftOverlay.h"
#include "BlobOverlay.h"
#include "PerspectiveImageOverlay.h"
#include "PerspectiveObjectOverlay.h"
#include "PongOverlay.h"
#include "StageObjectOverlay.h"
#include "ShakeOverlay.h"
#include "CutOutOverlay.h"
#include "CineOverlay.h"
#include "ParticleStormOverlay.h"
#include "EffectChangeOverlay.h"
#include "TeleportOverlay.h"
#include "LinesOverlay.h"
#include "GravityStageOverlay.h"
#include "PerspectiveVideoOverlay.h"

Overlay* OverlayLibrary::addOverlay(const std::string& name, const std::string& type)
{
    Overlay* newOverlay;
    if (type.compare(ColourShiftOverlay::NAME)==0)
    {
        newOverlay = new ColourShiftOverlay;
    }
    else if (type.compare(BlobOverlay::NAME) ==0)
    {
        newOverlay = new BlobOverlay;
    }
    else if (type.compare(PerspectiveImageOverlay::NAME) ==0)
    {
        newOverlay = new PerspectiveImageOverlay;
    }
    else if (type.compare(PerspectiveObjectOverlay::NAME) ==0)
    {
        newOverlay = new PerspectiveObjectOverlay;
    }
    else if (type.compare(PongOverlay::NAME) ==0)
    {
        newOverlay = new PongOverlay;
    }
    else if (type.compare(StageObjectOverlay::NAME) ==0)
    {
        newOverlay = new StageObjectOverlay;
    }
    else if (type.compare(ShakeOverlay::NAME) ==0)
    {
        newOverlay = new ShakeOverlay;
    }
    else if (type.compare(CutOutOverlay::NAME) ==0)
    {
        newOverlay = new CutOutOverlay;
    }
    else if (type.compare(CineOverlay::NAME) ==0)
    {
        newOverlay = new CineOverlay;
    }
    else if (type.compare(ParticleStormOverlay::NAME) ==0)
    {
        newOverlay = new ParticleStormOverlay;
    }
    else if (type.compare(EffectChangeOverlay::NAME) ==0)
    {
        newOverlay = new EffectChangeOverlay;
    }
    else if (type.compare(TeleportOverlay::NAME) ==0)
    {
        newOverlay = new TeleportOverlay;
    }
    else if (type.compare(LinesOverlay::NAME) ==0)
    {
        newOverlay = new LinesOverlay;
    }
    else if (type.compare(GravityStageOverlay::NAME) ==0)
    {
        newOverlay = new GravityStageOverlay;
    }
    else if (type.compare(PerspectiveVideoOverlay::NAME) ==0)
    {
        newOverlay = new PerspectiveVideoOverlay;
    }
    if (!newOverlay) return 0; // TODO: exceptions!
    newOverlay->setInstanceName(name);
    newOverlay->setChoreography(choreography);
    overlays[name] = newOverlay;
    return newOverlay;
}

void OverlayLibrary::update(ofxCvColorImage *input)
{
    for(int i = 0; i < activeOverlays.size(); ++i)
        activeOverlays[i]->update(input);
}

void OverlayLibrary::draw()
{
    for(int i = 0; i < activeOverlays.size(); ++i)
        activeOverlays[i]->draw();
    
}

Overlay*& OverlayLibrary::operator[] (const std::string& index)
{
    return overlays[index];
}

Overlay* OverlayLibrary::activate(const std::string &id, float width, float height)
{
    if (std::find(activeOverlays.begin(), activeOverlays.end(), overlays[id])!=activeOverlays.end()) return 0;
    activeOverlays.push_back(overlays[id]);
    overlays[id]->setup(width, height);
    return overlays[id];
}

std::vector<Overlay*> OverlayLibrary::getActiveOverlays()
{
    return activeOverlays;
}

void OverlayLibrary::setChoreography(Choreography* newChoreography)
{
    choreography = newChoreography;
    std::map<std::string,Overlay*>::const_iterator overlay = overlays.begin();

    for (;
         overlay != overlays.end();
         ++overlay)
    {
        (*overlay).second->setChoreography(choreography);
    }
}

void OverlayLibrary::removeOverlay(const std::string& overlay)
{
    activeOverlays.erase(std::find(activeOverlays.begin(), activeOverlays.end(), overlays[overlay]));
}

