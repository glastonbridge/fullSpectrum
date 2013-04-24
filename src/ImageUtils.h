//
//  ImageUtils.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 19/02/2013.
//
//

#ifndef fullSpectrumAnalyser_ImageUtils_h
#define fullSpectrumAnalyser_ImageUtils_h

#include "ofMain.h"
#include "ofxCvMain.h"

void setAlphaImage(ofImage& displayImage, ofxCvColorImage& colourImage, ofxCvGrayscaleImage& alphaImage, unsigned char* pixels);
void setAlphaImage(ofImage& displayImage, ofPixels& colourImage, ofPixels& alphaImage, unsigned char* pixels);

#endif
