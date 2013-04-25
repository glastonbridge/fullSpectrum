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
    
    ofEnableAlphaBlending();
    cineFilter.getFbo().begin();
    
	glColorMask(0, 0, 0, 1);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
    ofSetColor(0,0,0,255);
    
    ofCircle(100.0f,100.0f, 100);
    ofCircle(200.0f,850.0f, 300);
    ofCircle(600.0f,400.0f, 150);
    
    ofSetColor(0,0,0,255);
    
    
    
    
    glColorMask(1, 1, 1, 1);
    ofSetColor(255,255,255,255);
    cineFilter.getFbo().end();
    ofDisableAlphaBlending();
}

void MottledCineOverlay::draw()
{
    ofEnableAlphaBlending();
    cineFilter.draw();
    ofDisableAlphaBlending();
}

void MottledCineOverlay::setup(float width, float height)
{
    CineOverlay::setup(width, height);
    }

std::string MottledCineOverlay::getName() {return NAME;}
