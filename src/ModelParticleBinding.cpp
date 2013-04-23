//
//  ModelParticleBinding.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 08/04/2013.
//
//

#include "ModelParticleBinding.h"

ModelParticleBinding::ModelParticleBinding(ofxAssimpModelLoader& myModel, msa::physics::World3D& myWorld, const ofVec3f& initialPosition) : model(myModel), world(myWorld)
{
    
    ofVec3f centre = model.getSceneCenter();
    particles.push_back(new msa::physics::Particle3D(initialPosition+centre));
    addToWorld(world);
    
    /* The previous way of doing it modeled the corners of the cube.  For simplicity we're ignoring this.
     It's actually quite unclear how to link the corners together in a rigid cube arrangement anyway
     
    // This top/right/front nomenclature is arbitrary for the sake of traversing a cube.
    // x = height, y=span, z=depth
    // We create a cube from the outer bounds of the object and make physics particles from them.
    // This should be okay for memcubes etc.
    ofVec3f nodeBottomLeftBack(model.getSceneMin());
    ofVec3f nodeTopRightFront(model.getSceneMax());
    
    float top   = nodeTopRightFront.x,  bottom = nodeBottomLeftBack.x;
    float left  = nodeBottomLeftBack.y, right  = nodeTopRightFront.y;
    float front = nodeTopRightFront.z,  back   = nodeBottomLeftBack.z;
    
    ofVec3f nodeBottomLeftFront(bottom,left,front);
    ofVec3f nodeBottomRightFront(bottom,right,front);
    ofVec3f nodeBottomRightBack(bottom,right,back);
    
    ofVec3f nodeTopLeftBack(top, left, back);
    ofVec3f nodeTopLeftFront(top, left, front);
    ofVec3f nodeTopRightBack(top,right,back);
    
    // So long as the first three points form a base triangle, we don't care what order the others are in
    particles.push_back(new msa::physics::Particle3D(nodeBottomLeftBack+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeBottomLeftFront+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeBottomRightBack+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeBottomRightFront+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeTopLeftBack+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeTopLeftFront+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeTopRightBack+initialPosition));
    particles.push_back(new msa::physics::Particle3D(nodeTopRightFront+initialPosition));
    
    originalPositions.push_back(nodeBottomLeftBack+initialPosition);
    originalPositions.push_back(nodeBottomLeftFront+initialPosition);
    originalPositions.push_back(nodeBottomRightBack+initialPosition);
    originalPositions.push_back(nodeBottomRightFront+initialPosition);
    originalPositions.push_back(nodeTopLeftBack+initialPosition);
    originalPositions.push_back(nodeTopLeftFront+initialPosition);
    originalPositions.push_back(nodeTopRightBack+initialPosition);
    originalPositions.push_back(nodeTopRightFront+initialPosition);
    
    addToWorld(world);
     */

}

ofVec3f ModelParticleBinding::getModelTranslation()
{
    return particles[0]->getPosition() ;// - originalPositions[0];
}

ofVec3f ModelParticleBinding::getModelRotation()
{
    return ofVec3f();
}

void ModelParticleBinding::addToWorld(msa::physics::World3D& world)
{
    auto particle = particles.begin();
    for (; particle < particles.end(); ++particle)
    {
        (*particle)->setBounce(0.2);
        (*particle)->setRadius(5);
        world.addParticle(*particle);
        //auto previousParticle = particles.begin();
        
        // mesh all particles together
        //for (;previousParticle < particle; ++previousParticle)
        //{
            //world.makeSpring(*particle, *previousParticle, 1, (*particle)->getPosition().distance((*previousParticle)->getPosition()));//->setForceCap(0.01);
        //}
    }
}

ModelParticleBinding::~ModelParticleBinding()
{
    for (auto particle = particles.begin(); particle < particles.end(); ++particle)
    {
        (*particle)->kill();
    }
}

