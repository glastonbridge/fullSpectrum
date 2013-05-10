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
    
    float circleRad = getFloatValue("circle radius");
    for(auto circleCentre = circleCentres.begin(); circleCentre < circleCentres.end(); ++circleCentre)
    {
        ofCircle(*circleCentre, circleRad);
    }
    
    
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

    circleCentres.clear();
    circleCentres.push_back(ofPoint(700,200));
    circleCentres.push_back(ofPoint(50,350));
    circleCentres.push_back(ofPoint(400,300));
    circleCentres.push_back(ofPoint(300  ,0));
    circleCentres.push_back(ofPoint(750,700));
    circleCentres.push_back(ofPoint(500,600));
    circleCentres.push_back(ofPoint(200,700));
    circleCentres.push_back(ofPoint(800,1200));
    circleCentres.push_back(ofPoint(450,1100));
    circleCentres.push_back(ofPoint(0,1200));
//    ofCircle(100.0f,100.0f, 100);
//    ofCircle(200.0f,850.0f, 300);
//    ofCircle(600.0f,400.0f, 150);
}

MottledCineOverlay::MottledCineOverlay()
{
    addFloatParam("circle radius",150,100,400);
}

std::string MottledCineOverlay::getName() {return NAME;}
