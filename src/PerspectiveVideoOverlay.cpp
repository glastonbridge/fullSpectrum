//
//  PerspectiveVideoOverlay.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 21/04/2013.
//
//

#include "PerspectiveVideoOverlay.h"

 const std::string PerspectiveVideoOverlay::NAME = "perspective video";
//virtual void update(ofxCvColorImage* input);

 void PerspectiveVideoOverlay::setup(float width, float height)
{
    isPlaying = false;
    video.loadMovie(getStringValue("video file"));
    video.setLoopState(OF_LOOP_NORMAL);
    video.setUseTexture(true);
    video.play();
    frame.allocate(width, height, OF_IMAGE_COLOR);
    
}

std::string PerspectiveVideoOverlay::getName() {return NAME;}
PerspectiveVideoOverlay::PerspectiveVideoOverlay()
{
    addStringParam("video file", "");
}

void PerspectiveVideoOverlay::update(ofxCvColorImage *input)
{
    LinesOverlay::update(input);
    video.update();
    if (video.isFrameNew())
    {
        isPlaying = true;
        frame.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
    }
}

 void PerspectiveVideoOverlay::drawModel()
{
    if (!isPlaying) return;
    ofSetHexColor(0xffffff);
    ofPushMatrix();
    float scale = getFloatValue(4);
    
    glTranslatef(getFloatValue(1), getFloatValue(2), getFloatValue(3));
    
    glRotatef (getFloatValue(6), 1.0f, 0,0);
    glRotatef (getFloatValue(7), 0, 1.0f, 0);
    glRotatef (getFloatValue(8), 0,0, 1.0f);
    
    glScalef(scale, scale, scale);
    if (getStringValue("video file").find("2.m4v")!=std::string::npos) // fkin hack for those cropped vids
    {
        frame.drawSubsection(0, 0, 140, 280, 480, 210);
    }
    else
    {
        frame.drawSubsection(0, 0, 180, 280, 710, 190);
    }
    ofPopMatrix();
}

void PerspectiveVideoOverlay::teardown()
{
    video.stop();
    //video.close();
}

