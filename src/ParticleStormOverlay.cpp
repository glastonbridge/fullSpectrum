//
//  ParticleStormOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/02/2013.
//
//

#include "ParticleStormOverlay.h"
#include <string>
#include "DancerBlobSensor.h"
#include "ImageUtils.h"

static const unsigned int NUM_MOLECULES = 100;

const std::string ParticleStormOverlay::NAME = "particle storm";
std::string ParticleStormOverlay::getName() { return NAME;}

ParticleStormOverlay::ParticleStormOverlay() {}

void ParticleStormOverlay::update(ofxCvColorImage* input)
{
    ColouredBlobSensor* blobSensor = dynamic_cast<ColouredBlobSensor*> (sensors[0]);
    
    if (!displayImage.isAllocated())
    {
        int width = input->getWidth(), height = input->getHeight();
        displayImage.allocate(width, height ,OF_IMAGE_COLOR_ALPHA);
        pixels = new unsigned char[width*height*4];
    }
    setAlphaImage(displayImage, *input, blobSensor->val, pixels);
}

void ParticleStormOverlay::draw()
{
    DancerBlobSensor* dancerSensor = dynamic_cast<DancerBlobSensor*>(sensors[0]);
    if (dancerSensor->contours.blobs.size() < 1) return;
    ofPoint stormCentre = dancerSensor->contours.blobs[0].centroid;
    ofRectangle dancerRect = dancerSensor->contours.blobs[0].boundingRect;
    std::vector<ofPoint>::iterator molecule(molecules.begin());
    ofSetColor(255,255,0,40);
    for (; molecule <molecules.end(); ++molecule)
    {
        float cosAngle = cos(molecule->z);
        if (cosAngle >0) continue;
        float circleX = stormCentre.x + molecule->x * sin(molecule->z);
        float circleY = stormCentre.y + molecule->y * cosAngle;
        if (abs(cosAngle)<0.2 && dancerRect.inside(circleX-5, circleY))
        {
            circleX += (0.2-abs(cosAngle))*5*(dancerRect.x+dancerRect.width - circleX+  5); // TODO: tidy up
        }
        ofCircle(circleX, circleY, (2+cosAngle));
    }
    ofSetColor(0xFF,0xFF,0xFF,0xFF);
    displayImage.draw(0,0);
    ofSetColor(255,255,0,200);
    for (molecule = molecules.begin(); molecule <molecules.end(); ++molecule)
    {
        float cosAngle = cos(molecule->z);
        float circleX = stormCentre.x + molecule->x * sin(molecule->z);
        float circleY = stormCentre.y + molecule->y * cosAngle;
        
        molecule->z +=0.1;
        if (molecule->z >= 2*PI) molecule->z -= 2*PI;
        
        if (cosAngle <=0) continue;
        
        if (abs(cosAngle)<0.2 && dancerRect.inside(circleX-5, circleY))
        {
            circleX += (0.2-abs(cosAngle))*5*(dancerRect.x+dancerRect.width - circleX+5); // TODO: tidy up
        }
        ofCircle(circleX, circleY, (2+cosAngle));
    }
    ofSetColor(0xFF,0xFF,0xFF,0xFF);
}

//The molecules have a radial coordinate about the dancer with x=radius, y=height, z=angle
void ParticleStormOverlay::setup(float width, float height)
{
    for (int i = 0; i < NUM_MOLECULES; ++i)
    {
        molecules.push_back(ofPoint(ofRandom(25,50), ofRandom(10), ofRandom(2*PI)));
    }
}

