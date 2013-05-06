//
//  GravityStageOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 08/04/2013.
//
//

#include "GravityStageOverlay.h"
#include "PoseSensor.h"

 const std::string GravityStageOverlay::NAME = "gravity object";
void GravityStageOverlay::update(ofxCvColorImage* input)
{
    LinesOverlay::update(input);
    world.update();
}


void GravityStageOverlay::drawModel()
{
    for (auto binding = bindings.begin(); binding < bindings.end(); ++binding)
    {
        ofPushMatrix();
        ofTranslate(ofVec3f() - (*binding)->getModelTranslation());
        
        float scale = getFloatValue(4);
        
        glRotatef (getFloatValue(6), 1.0f, 0,0);
        glRotatef (getFloatValue(7), 0, 1.0f, 0);
        glRotatef (getFloatValue(8), 0,0, 1.0f);
        
        ofPoint modelCentre = model->getSceneCenter();
        ofTranslate(-modelCentre.x, -modelCentre.y, -modelCentre.z);
        glScalef(scale, scale, scale);
        ofTranslate(modelCentre);
        
        if (getBoolValue(9))
            model->drawWireframe();
        else
            model->drawFaces();
        ofPopMatrix();
    }
}

void GravityStageOverlay::setup(float width, float height)
{
    
    LinesOverlay::setup(width,height);
    world.clear();
    world.clear();
    world.setGravity(ofVec3f(0,-0.1,0));
    world.setWorldMin(ofVec3f(-100,-30,-100));
    world.setWorldMax(ofVec3f(100,100,100));
    world.setTimeStep(1.0f/7);
    world.enableCollision();
    ofVec3f translate(getFloatValue(1), getFloatValue(2), getFloatValue(3));
    bindings.push_back( new ModelParticleBinding(*model,world,ofVec3f()-translate));
}

std::string GravityStageOverlay::getName() {return NAME;}

void GravityStageOverlay::addACube(const ofVec3f &position)
{
    bindings.push_back( new ModelParticleBinding(*model,world,position));
}

GravityStageOverlay::GravityStageOverlay()
{
    //addBoolParam("draw floor", true);
}

GravityStageOverlay::~GravityStageOverlay()
{
    for (auto binding = bindings.begin(); binding < bindings.end(); ++binding)
    {
        delete *binding;
    }
    bindings.clear();
}