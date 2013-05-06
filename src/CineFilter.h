//
//  CineFilter.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 24/04/2013.
//
//

#ifndef fullSpectrumAnalyser_CineFilter_h
#define fullSpectrumAnalyser_CineFilter_h

#include "ofMain.h"
#include "ofxCvMain.h"

class CineFilter
{
public:

    CineFilter();
    void allocate(float width, float height);
    void update(ofxCvColorImage* input);
    void draw();
    ofImage& getImage();
    ofFbo& getFbo();
private:
    ofFbo cineFbo;
    ofxCvGrayscaleImage cineImage;
    ofImage cineImageWithFlickers;
    ofPixels pixelBuffer;
};

#endif
