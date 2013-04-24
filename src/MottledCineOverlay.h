//
//  MottledCineOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 23/04/2013.
//
//

#ifndef fullSpectrumAnalyser_MottledCineOverlay_h
#define fullSpectrumAnalyser_MottledCineOverlay_h

#include "CineOverlay.h"

class MottledCineOverlay : public CineOverlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
private:
    ofImage     alphaImage;
    ofPixels     alphaMask;
    ofPixels    pixelBuffer;
    unsigned char* tempPixelSpace;
    
    ofxCvGrayscaleImage maskImage;

};

#endif
