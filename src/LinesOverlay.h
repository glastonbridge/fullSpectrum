//
//  LinesOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/03/2013.
//
//

#ifndef fullSpectrumAnalyser_LinesOverlay_h
#define fullSpectrumAnalyser_LinesOverlay_h

#include "StageObjectOverlay.h"

/**
 * The amazingly badly-named LinesOverlay is the base class for using a PoseSensor to create
 * a posited view in 3D
 *
 * Rather than overriding draw(), you should override drawModel() to draw your models in the camera space
 */
class LinesOverlay : public StageObjectOverlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    
    virtual int getGeometry();
    LinesOverlay();
    
protected:
    /**
     * In subclasses that use pose estimation from this class, override
     * drawModel instead of draw, to draw straight into the prepared perspective
     * geometry
     */
    virtual void drawModel();
    
};

#endif
