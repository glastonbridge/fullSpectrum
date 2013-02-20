//
//  ImageUtils.c
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 19/02/2013.
//
//

#include "ImageUtils.h"

void setAlphaImage(ofTexture& displayImage, ofxCvColorImage& colourImage, ofxCvGrayscaleImage& alphaImage, unsigned char* pixels)
{
    int width = displayImage.getWidth(), height = displayImage.getHeight();
    unsigned char* colourPixels = colourImage.getPixels();
    unsigned char* alphaPixels = alphaImage.getPixels();
    
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            int pos = (j * width + i);
            pixels[pos*4  ] = 0xFF;//colourPixels[pos * 3];
            pixels[pos*4+1] = 0;//colourPixels[pos * 3+1];
            pixels[pos*4+2] = 0;//colourPixels[pos * 3+2];
            pixels[pos*4+3] = 0xFF;//alphaPixels[pos];
        }
    }
    displayImage.loadData(pixels, width, height, GL_RGBA);
}

