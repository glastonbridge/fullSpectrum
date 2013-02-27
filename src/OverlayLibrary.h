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
#import <map>
#import <vector>
#import "Overlay.h"

class Choreography;

class OverlayLibrary
{
public:
    void update(ofxCvColorImage* input);
    void draw();
    Overlay* addOverlay(const std::string& id, const std::string& type);
    Overlay* activate(const std::string& id, float width, float height);
    std::vector<Overlay*> getActiveOverlays();
    Overlay*& operator[] (const std::string& index);
    void setChoreography(Choreography* newChoreography);
    void removeOverlay(const std::string& overlayName);
private:
    std::vector<Overlay*> activeOverlays;
    std::map<std::string, Overlay*> overlays;
    Choreography* choreography;
};

#endif
