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
    if (!newOverlay) return 0; // TODO: exceptions!
    newOverlay->setup(width, height);
    overlays.push_back(newOverlay);
    return newOverlay;
}
