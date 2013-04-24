//
//  ImageUtils.c
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 19/02/2013.
//
//

#include "ImageUtils.h"

void setAlphaImage(ofImage& displayImage, ofxCvColorImage& colourImage, ofxCvGrayscaleImage& alphaImage, unsigned char* pixels)
{
    int width = displayImage.getWidth(), height = displayImage.getHeight();
    unsigned char* colourPixels = colourImage.getPixels();
    unsigned char* alphaPixels = alphaImage.getPixels();
    
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            int pos = (j * width + i);
            pixels[pos*4  ] = colourPixels[pos * 3];
            pixels[pos*4+1] = colourPixels[pos * 3+1];
            pixels[pos*4+2] = colourPixels[pos * 3+2];
            pixels[pos*4+3] = alphaPixels[pos];
        }
    }
    displayImage.setFromPixels(pixels, width, height, OF_IMAGE_COLOR_ALPHA);
}

void setAlphaImage(ofImage& displayImage, ofPixels& colourPixels, ofPixels& alphaPixels, unsigned char* pixels)
{
    
    int width = displayImage.getWidth(), height = displayImage.getHeight();
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            int pos = (j * width + i);
            pixels[pos*4  ] = colourPixels[pos * 3];
            pixels[pos*4+1] = colourPixels[pos * 3+1];
            pixels[pos*4+2] = colourPixels[pos * 3+2];
            pixels[pos*4+3] = alphaPixels[pos];
        }
    }
    displayImage.setFromPixels(pixels, width, height, OF_IMAGE_COLOR_ALPHA);
}

