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

void GravityStageOverlay::draw()
{
    PoseSensor * sensor = dynamic_cast<PoseSensor *>(sensors[0]);
    
    float storeProjection[16], storeModelView[16];
    glGetFloatv(GL_PROJECTION_MATRIX, storeProjection);
    glGetFloatv(GL_MODELVIEW_MATRIX, storeModelView);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( sensor->projectionMatrix );
	glMatrixMode(GL_MODELVIEW);
    
	//Draw the object with the estimated pose
	glLoadIdentity();
	glScalef( 1.0f, 1.0f, -1.0f);
	glMultMatrixf( sensor->posePOSIT );
	//glEnable( GL_LIGHTING );
	//glEnable( GL_LIGHT0 );
    
    
    ofSetColor(255, 255, 255, 255);
    
	glEnable(GL_DEPTH_TEST);
    
    
    ofPushMatrix();
    float scale = getFloatValue(4);
    glRotatef (getFloatValue(5),getFloatValue(6), getFloatValue(7),getFloatValue(8));
    //glScalef(scale, scale, scale);
    
    ofTranslate(binding->getModelTranslation());
    
    if (getBoolValue(9))
        model.drawWireframe();
    else
        model.drawFaces();

    ofPopMatrix();
    
	//glDisable( GL_LIGHTING );
    //glDisable( GL_LIGHT0 );
    //glLoadIdentity();
    
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(storeProjection);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    glLoadMatrixf(storeModelView);
    
    ofSetColor(255,255,255);
    
}

void GravityStageOverlay::setup(float width, float height)
{
    LinesOverlay::setup(width,height);
    world.clear();
    world.setGravity(ofVec3f(0,1,0));
    world.setWorldMin(ofVec3f(-100,-20,-100));
    world.setWorldMax(ofVec3f(100,100,100));
    world.setTimeStep(1.0f/60);
    ofVec3f translate(getFloatValue(1), getFloatValue(2), getFloatValue(3));
    binding = std::auto_ptr<ModelParticleBinding>(new ModelParticleBinding(model,world,translate));
}

std::string GravityStageOverlay::getName() {return NAME;}

GravityStageOverlay::GravityStageOverlay()
{
    addBoolParam("draw floor", true);
}