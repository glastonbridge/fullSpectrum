//
//  ModelParticleBinding.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 08/04/2013.
//
//

#ifndef fullSpectrumAnalyser_ModelParticleBinding_h
#define fullSpectrumAnalyser_ModelParticleBinding_h

#include "ofxAssimpModelLoader.h"
#include "MSAPhysics3D.h"
#include <vector>

/**
 *  Maintains particles around the bounding box of the model we're interested in.
 *  
 */
class ModelParticleBinding
{
public:
    ModelParticleBinding(ofxAssimpModelLoader& myModel, msa::physics::World3D& myWorld, const ofVec3f& initialPosition);
    ~ModelParticleBinding();
    ofVec3f getModelTranslation();
    ofVec3f getModelRotation();
private:
    std::vector<msa::physics::Particle3D *> particles;
    std::vector<ofVec3f> originalPositions;
    ofxAssimpModelLoader& model;
    msa::physics::World3D& world;
    void addToWorld(msa::physics::World3D& world);
};

#endif
