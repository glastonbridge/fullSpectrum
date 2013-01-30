//
//  BlobOverlay.h
//  fullSpectrum
//
//  Created by Alex Shaw on 09/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_BlobOverlay_h
#define fullSpectrum_BlobOverlay_h

#include "Overlay.h"

class BlobOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();  
    virtual void setup(float width, float height);
    virtual std::string getName();
    BlobOverlay();
private:
    ofImage blobMarker;
};

#endif
