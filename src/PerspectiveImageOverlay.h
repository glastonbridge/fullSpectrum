//
//  PerspectiveImageOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 16/01/2013.
//
//

#ifndef fullSpectrumAnalyser_PerspectiveImageOverlay_h
#define fullSpectrumAnalyser_PerspectiveImageOverlay_h

#import "Overlay.h"

class PerspectiveImageOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual std::string getName();

    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);

private:
    ofxCvColorImage overlayImage, translatedImage, displayImage;
    
    ofPoint* srcPoints, * dstPoints;
};

#endif
