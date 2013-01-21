//
//  PerspectiveObjectOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 18/01/2013.
//
//

#include "PerspectiveObjectOverlay.h"
#include "PerspectiveQuadSensor.h"

#include "homography.h"

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
    PerspectiveQuadSensor* quadSensor = dynamic_cast<PerspectiveQuadSensor*> (sensors[0]);
    
    
    ofSetColor(255, 255, 255, 255);
    
	//note we have to enable depth buffer in main.mm
	//see: window->enableDepthBuffer(); in main.mm
    
	glEnable(GL_DEPTH_TEST);
    
    dstPoints[0] = quadSensor->topLeft;
    dstPoints[1] = quadSensor->topRight;
    dstPoints[3] = quadSensor->bottomRight;
    dstPoints[2] = quadSensor->bottomLeft;
    
    // I found this approach works, but the one after the return statement in this function
    // does not for some reason.
    // original inspiration here : http://forum.openframeworks.cc/index.php?&topic=3121.0
    
    GLfloat matrix[16];
    findHomography(srcPoints,dstPoints,matrix);
    
    glPushMatrix();
    glMultMatrixf(matrix);
    glPushMatrix();
    model.drawFaces();
    glPopMatrix();
    glPopMatrix();
    return;
    
    ofMatrix4x4 transform = findHomography(srcPoints,dstPoints);
    
    ofPushMatrix();
    
    ofMultMatrix(transform);
    
    bob.draw(0,0);
    
    ofPushMatrix();
    
    //ofScale(10, 10);
    
    ofPopMatrix();
    
    ofPopMatrix();
}

void PerspectiveObjectOverlay::setup(float width, float height)
{
    
    srcPoints = new ofPoint[4];
    dstPoints = new ofPoint[4];
    
    // we need GL_TEXTURE_2D for our models coords.
    ofDisableArbTex();
    
    model.loadModel("astroBoy_walk.dae", true);
    model.setAnimation(0);
//    model.setPosition(ofGetWidth() / 2, (float)ofGetHeight() * 0.75 , 0);
    model.setPosition(0,8,0);
    //model.createLightsFromAiModel();
    //model.disableTextures();
    //model.disableMaterials();
    model.setScale(0.1, 0.1, 0.1);
    
    mesh = model.getMesh(0);
    position = model.getPosition();
    normScale = model.getNormalizedScale();
    scale = model.getScale();
    
    
    srcPoints[0].x = 0;
    srcPoints[0].y = 0;
    srcPoints[1].x = 10;
    srcPoints[1].y = 0;
    srcPoints[2].x = 10;
    srcPoints[2].y = 10;
    srcPoints[3].x = 0;
    srcPoints[3].y = 10;
    
    srcPoints[0] = model.getSceneMin();
    srcPoints[2] = model.getSceneMax();
    srcPoints[1].x = srcPoints[2].x;
    srcPoints[1].y = srcPoints[0].y;
    srcPoints[3].x = srcPoints[0].x;
    srcPoints[3].y = srcPoints[2].y;
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    //some model / light stuff
    glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();
    
    bob.loadImage("smile.png");
    
    
    srcPoints[0].x = 0;
    srcPoints[0].y = 0;
    srcPoints[1].x = bob.width;
    srcPoints[1].y = 0;
    srcPoints[3].x = bob.width;
    srcPoints[3].y = bob.height;
    srcPoints[2].x = 0;
    srcPoints[2].y = bob.height;
    
    
}

