//
//  VideoSource.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#import "VideoSource.h"

#include "ofxOpenCv.h"

void VideoSource::allocateCamera(float width, float height)
{
    if (videoInput.get()) return;
    
    cameraInput = auto_ptr<ofVideoGrabber>(new ofVideoGrabber);
    
    (*cameraInput).initGrabber(width, height);
}

void VideoSource::allocateVideo(float width, float height, std::string videoFile)
{
    if (cameraInput.get()) return;
    
    videoInput = auto_ptr<ofVideoPlayer>(new ofVideoPlayer);
    
    (*videoInput).loadMovie(videoFile);
    (*videoInput).setLoopState(OF_LOOP_NORMAL);
    (*videoInput).play();
}

void VideoSource::update()
{
    if (videoInput.get()) (*videoInput).update();
    if (cameraInput.get()) (*cameraInput).update();
}

float VideoSource::getWidth()
{
    if (videoInput.get()) return (*videoInput).getWidth();
    if (cameraInput.get()) return (*cameraInput).getWidth();
    return -1;
}

float VideoSource::getHeight()
{
    if (videoInput.get()) return (*videoInput).getHeight();
    if (cameraInput.get()) return (*cameraInput).getHeight();
    return -1;
}

bool VideoSource::isFrameNew()
{
    if (videoInput.get()) return (*videoInput).isFrameNew();
    if (cameraInput.get()) return (*cameraInput).isFrameNew();
    return false;
}

unsigned char* VideoSource::getPixels()
{
    if (videoInput.get()) return (*videoInput).getPixels();
    if (cameraInput.get()) return (*cameraInput).getPixels();
    return NULL;
}

void VideoSource::stop()
{
    if(cameraInput.get()) (*cameraInput).close();
}


