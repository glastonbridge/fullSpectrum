//
//  MottledCineOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 23/04/2013.
//
//

#include "MottledCineOverlay.h"

#include "ImageUtils.h"

const std::string MottledCineOverlay::NAME = "mottled cine";
void MottledCineOverlay::update(ofxCvColorImage* input)
{
    CineOverlay::update(input);
    cineFbo.readToPixels(pixelBuffer);
    ofxCvColorImage cineImageWithFlickers;
    cineImageWithFlickers.allocate(input->getWidth(), input->getHeight());
    cineImageWithFlickers.setFromPixels(pixelBuffer);
    setAlphaImage(alphaImage, cineImageWithFlickers, maskImage, tempPixelSpace);
}

void MottledCineOverlay::draw()
{
    ofEnableAlphaBlending();
    alphaImage.draw(0,0);
    //ofImage toast;
    //toast.allocate(alphaImage.getWidth(), alphaImage.getHeight(), OF_IMAGE_GRAYSCALE);
    //toast.setFromPixels(alphaMask.getPixels(), alphaImage.getWidth(), alphaImage.getHeight(), OF_IMAGE_GRAYSCALE);
    //toast.draw(0,0);
    ofDisableAlphaBlending();
}

void MottledCineOverlay::setup(float width, float height)
{
    CineOverlay::setup(width, height);
    
    alphaImage.allocate(width,height,OF_IMAGE_COLOR_ALPHA);
    alphaMask.allocate(width, height, 1);
    pixelBuffer.allocate(width, height, 3);
    tempPixelSpace = new unsigned char[(int)(4*width*height)];
    maskImage.allocate(width, height);
    maskImage.set(0);
    cvCircle(maskImage.getCvImage(), cvPoint(100.0f,100.0f), 100, cvScalar(255),CV_FILLED);
    cvCircle(maskImage.getCvImage(), cvPoint(200.0f,850.0f), 300, cvScalar(255),CV_FILLED);
    cvCircle(maskImage.getCvImage(), cvPoint(600.0f,400.0f), 150, cvScalar(255), CV_FILLED);
}

std::string MottledCineOverlay::getName() {return NAME;}
