//
//  OverlayLibrary.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_OverlayLibrary_h
#define fullSpectrum_OverlayLibrary_h

#import "ofxOpenCv.h"
#import <vector>
#import "Overlay.h"

class OverlayLibrary
{
public:
    void update(ofxCvColorImage* input);
    void draw();
    Overlay* addOverlay(const std::string& overlayName, float width, float height);
    std::vector<Overlay*> getActiveOverlays();
private:
    std::vector<Overlay*> overlays;
};

#endif
