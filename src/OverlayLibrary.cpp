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

void OverlayLibrary::update(ofxCvColorImage *input)
{
    for(int i = 0; i < overlays.size(); ++i)
        overlays[i]->update(input);
}

void OverlayLibrary::draw()
{
    for(int i = 0; i < overlays.size(); ++i)
        overlays[i]->draw();
    
}

Overlay* OverlayLibrary::addOverlay(const std::string& overlayName, float width, float height)
{
    Overlay* newOverlay;
    if (overlayName.compare(ColourShiftOverlay::NAME)==0)
    {
        newOverlay = new ColourShiftOverlay;
    }
    else if (overlayName.compare(BlobOverlay::NAME) ==0)
    {
        newOverlay = new BlobOverlay;
    }
    else if (overlayName.compare(PerspectiveImageOverlay::NAME) ==0)
    {
        newOverlay = new PerspectiveImageOverlay;
    }
    else if (overlayName.compare(PerspectiveObjectOverlay::NAME) ==0)
    {
        newOverlay = new PerspectiveObjectOverlay;
    }
    if (!newOverlay) return 0; // TODO: exceptions!
    newOverlay->setup(width, height);
    overlays.push_back(newOverlay);
    return newOverlay;
}

std::vector<Overlay*> OverlayLibrary::getActiveOverlays()
{
    return overlays;
}