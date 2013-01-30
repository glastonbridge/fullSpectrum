//
//  OverlayLibrary.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "OverlayLibrary.h"
#include "ColourShiftOverlay.h"
#include "BlobOverlay.h"
#include "PerspectiveImageOverlay.h"
#include "PerspectiveObjectOverlay.h"
#include "PongOverlay.h"

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

Overlay* OverlayLibrary::activate(const std::string &id, float width, float height)
{
    activeOverlays.push_back(overlays[id]);
    overlays[id]->setup(width, height);
    return overlays[id];
}

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
    if (!newOverlay) return 0; // TODO: exceptions!
    overlays[name] = newOverlay;
    return newOverlay;
}

std::vector<Overlay*> OverlayLibrary::getActiveOverlays()
{
    return activeOverlays;
}