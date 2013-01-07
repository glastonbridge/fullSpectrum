//
//  VideoSource.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_VideoSource_h
#define fullSpectrum_VideoSource_h

#import <memory>

#include "ofxOpenCv.h"

/**
 * Wrap ofVideoGrabber (camera) and ofVideoPlayer (pre-rolled video) so 
 * that we can switch between them seamlessly.
 */
class VideoSource
{
public:
    void allocateCamera(float width, float height);
    void allocateVideo(float width, float height, std::string videoFile);
    void update();
    bool isFrameNew();
    unsigned char* getPixels();
    float getWidth();
    float getHeight();
    void stop();
    
private:
    /**
     * Only one of these is ever used in a single instance of this class
     */
    std::auto_ptr<ofVideoGrabber> cameraInput;
    std::auto_ptr<ofVideoPlayer> videoInput;
};

#endif
