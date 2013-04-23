//
//  CubeRainOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/04/2013.
//
//

#include "CubeRainOverlay.h"


const std::string CubeRainOverlay::NAME="cube rain";
void CubeRainOverlay::update(ofxCvColorImage* input)
{
    GravityStageOverlay::update(input);
    // remove cubes if they're underground
    for (auto binding = bindings.begin(); binding < bindings.end(); ++binding)
    {
        float height = (*binding)->getModelTranslation().y;
        if (height < -50 || isnan(height))
        {
            ModelParticleBinding* doomed = *binding;
            bindings.erase(binding); // won't cause concurrency error?
            delete doomed;
        }
    }
    // add cubes if there's room for more
    
    int maxRaindrops = getIntValue("max raindrops");
    while (bindings.size()<maxRaindrops)
    {
        addACube(ofVec3f(ofRandom(-65,80),200,ofRandom(0,60)));
    }
}

void CubeRainOverlay::drawModel()
{
    GravityStageOverlay::drawModel();
}

void CubeRainOverlay::setup(float width, float height)
{
    world.clear();
    world.setGravity(ofVec3f(0,-0.1,0));
    world.setWorldMin(ofVec3f(-100,-60,-100));
    world.setWorldMax(ofVec3f(100,100,100));
    world.setTimeStep(1.0f/20);
    world.enableCollision();
    
    
    int maxRaindrops = getIntValue("max raindrops");
    while (bindings.size()<maxRaindrops)
    {
        addACube(ofVec3f(ofRandom(-65,80),ofRandom(10,100),ofRandom(0,60)));
    }
}

std::string CubeRainOverlay::getName()
{return NAME;
}

CubeRainOverlay::CubeRainOverlay()
{
    addIntParam("max raindrops", 100, 10, 1000);
}
