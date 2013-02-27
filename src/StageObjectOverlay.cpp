//
//  StageObjectOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#include "StageObjectOverlay.h"

//
//  PerspectiveObjectOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 18/01/2013.
//
//

#include <string>
#include <iostream>

const std::string StageObjectOverlay::NAME = "stage object overlay";

std::string StageObjectOverlay::getName()
{
    return NAME;
}

int StageObjectOverlay::getGeometry() { return PERSPECTIVE ; }

StageObjectOverlay::StageObjectOverlay()
{
    addStringParam("source", "");
    addFloatParam("xoffset", 0, -200, 200);
    addFloatParam("yoffset", 0, -200, 200);
    addFloatParam("zoffset", 0, -400, 0);
    addFloatParam("scale",1,0,50);
    addFloatParam("rot angle", 0, -180, 180);
    addFloatParam("xrot", 0, 0, 1);
    addFloatParam("yrot", 0, 0, 1);
    addFloatParam("zrot", 0, 0, 1);
    addBoolParam("wireframe", false);
}

void StageObjectOverlay::update(ofxCvColorImage* input)
{
    
}

void StageObjectOverlay::paramChanged(int index)
{
    if (getParamName(index)=="source")
    {
        model.loadModel(getStringValue(index), true);
        //model.setAnimation(0);
        model.setPosition(0,8,0);
        model.setScale(0.1, 0.1, 0.1);
        model.enableColors();
        model.enableMaterials();
        
//        int meshes = model.getNumMeshes();
        mesh = model.getMesh(0);
        position = model.getPosition();
        normScale = model.getNormalizedScale();
        scale = model.getScale();
    }
}

void StageObjectOverlay::draw()
{
    
    ofSetColor(255, 255, 255, 255);
        //note we have to enable depth buffer in main.mm
	//see: window->enableDepthBuffer(); in main.mm
    
	glEnable(GL_DEPTH_TEST);
    
    
    ofPushMatrix();
    float scale = getFloatValue(4);
    glScalef(scale, scale, scale);
    glTranslatef(getFloatValue(1), getFloatValue(2), getFloatValue(3));
    glRotatef (getFloatValue(5),getFloatValue(6), getFloatValue(7),getFloatValue(8));
    if (getBoolValue(9))
        model.drawWireframe();
    else
        model.drawFaces();
    //mesh.drawFaces();
    ofPopMatrix();    
}


void StageObjectOverlay::setup(float width, float height)
{
    _width = width; _height = height;
    // we need GL_TEXTURE_2D for our models coords.
    ofDisableArbTex();
    
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    //some model / light stuff
    glShadeModel(GL_SMOOTH);
    ofMatrix4x4 moveOhs;
    moveOhs.translate((width - ofGetWidth())/2, (height-ofGetHeight())/2, 0);
    ofLoadMatrix(moveOhs);
    //light.enable();
    //ofEnableSeparateSpecularLight();
    /*glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    
    GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    GLfloat ambient[] = {0.2, 0.2f, 0.2f, 0.2f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    GLfloat position[] = { 0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glEnable(GL_LIGHT0);
    
    //some model / light stuff
    glShadeModel(GL_SMOOTH);
    //  light.enable();
    ofEnableSeparateSpecularLight();

    // Culling
    //if(meshHelper.twoSided)
    //    glEnable(GL_CULL_FACE);
    //else
    //    glDisable(GL_CULL_FACE);*/
}

