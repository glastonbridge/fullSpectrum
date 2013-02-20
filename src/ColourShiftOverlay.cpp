//
//  ColourShiftOverlay.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "ColourShiftOverlay.h"
#include "ImageUtils.h"

const std::string ColourShiftOverlay::NAME="colour shift overlay";

ColourShiftOverlay::ColourShiftOverlay()
{
    addIntParam("shift amount", 40, 0, 255);
    addIntParam("val threshold", 70, 0, 255);
}

void ColourShiftOverlay::setup(float width, float height)
{
    shiftImage.allocate(width, height);
    h.allocate(width, height);
    s.allocate(width, height);
    v.allocate(width, height);
    outImage.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    alphaImage.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    pixels = new unsigned char[(int)width*(int)height*4];
}

void ColourShiftOverlay::update(ofxCvColorImage *input)
{
    shiftImage = *input;
    shiftImage.convertRgbToHsv();
    shiftImage.convertToGrayscalePlanarImages(h,s,v);
    h.set( getIntValue(0));
    shiftImage.setFromGrayscalePlanarImages(h,s,v);
    shiftImage.convertHsvToRgb();
    v.threshold(getIntValue(1));
    v.invert();
//    setAlphaImage(alphaImage, shiftImage, v, pixels);
    
    int width = alphaImage.getWidth(), height = alphaImage.getHeight();
    unsigned char* colourPixels = shiftImage.getPixels();
    unsigned char* alphaPixels = v.getPixels();
    
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            int pos = (j * width + i);
            pixels[pos*4  ] = colourPixels[pos * 3];
            pixels[pos*4+1] = colourPixels[pos * 3+1];
            pixels[pos*4+2] = colourPixels[pos * 3+2];
            pixels[pos*4+3] = (j<70||i<100||i>540)?0:alphaPixels[pos];
        }
    }
    alphaImage.loadData(pixels, width, height, GL_RGBA);
    outImage.setFromPixels(pixels,(int)width, (int)height, OF_IMAGE_COLOR_ALPHA);
    int imageShiftValue = getIntValue(0);
    imageShiftValue += 2;
    imageShiftValue %= 255;
    setIntValue(0, imageShiftValue);
}

void ColourShiftOverlay::draw()
{
    ofColor(0,255,0);
    outImage.draw(0,0);
    //v.draw(0,0);
}

std::string ColourShiftOverlay::getName()
{
    return NAME;
}