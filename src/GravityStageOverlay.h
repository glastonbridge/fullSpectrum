//
//  GravityStageOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 08/04/2013.
//
//

#ifndef fullSpectrumAnalyser_GravityStageOverlay_h
#define fullSpectrumAnalyser_GravityStageOverlay_h

#include "LinesOverlay.h"
#include "EffectChangeOverlay.h"
#include "MSAPhysics3D.h"
#include "ModelParticleBinding.h"
#include <memory>

/**
 *  Like any other stage object, except that this one has a start position, start velocity, and a floor,
 *  and it is subject to gravity if the first is not near the second.
 *  On impact, it changes effects.
 *
 *  TODO: there is a special hell for people who deliberately use diamond inheritance.
 */
class GravityStageOverlay : public LinesOverlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    //virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    
    GravityStageOverlay();
    ~GravityStageOverlay();
protected:
    msa::physics::World3D world;
    virtual void drawModel();
    std::vector<ModelParticleBinding*> bindings;
    void addACube(const ofVec3f& position);
};

#endif
