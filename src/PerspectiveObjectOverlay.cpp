//
//  PerspectiveObjectOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 18/01/2013.
//
//

#include "PerspectiveObjectOverlay.h"

const std::string PerspectiveObjectOverlay::NAME = "perspective object overlay";

std::string PerspectiveObjectOverlay::getName()
{
    return NAME;
}

void PerspectiveObjectOverlay::update(ofxCvColorImage* input)
{
    
}

void PerspectiveObjectOverlay::draw()
{
    ofBackground(50, 50, 50, 0);
    ofSetColor(255, 255, 255, 255);
    
	//note we have to enable depth buffer in main.mm
	//see: window->enableDepthBuffer(); in main.mm
    
	glEnable(GL_DEPTH_TEST);
    ofPushMatrix();
    
    model.drawFaces();
    ofPopMatrix();
}

void PerspectiveObjectOverlay::setup(float width, float height)
{
    // we need GL_TEXTURE_2D for our models coords.
    ofDisableArbTex();
    
    if(model.loadModel("astroBoy_walk.dae", true)){
    	model.setAnimation(0);
    	model.setPosition(ofGetWidth() / 2, (float)ofGetHeight() * 0.75 , 0);
    	//model.createLightsFromAiModel();
    	//model.disableTextures();
    	//model.disableMaterials();
        
    	mesh = model.getMesh(0);
    	position = model.getPosition();
    	normScale = model.getNormalizedScale();
    	scale = model.getScale();
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    //some model / light stuff
    glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();
    
}
