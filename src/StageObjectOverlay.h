//
//  StageObjectOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 30/01/2013.
//
//

#ifndef fullSpectrumAnalyser_StageObjectOverlay_h
#define fullSpectrumAnalyser_StageObjectOverlay_h

#include "Overlay.h"
#include "ofxAssimpModelLoader.h"

class StageObjectOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual std::string getName();
    
    StageObjectOverlay();
    
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    
    virtual int getGeometry();
protected:
    ofxAssimpModelLoader model;
    virtual void paramChanged(int index);
private:
    float _width, _height;
    
    
    ofVboMesh mesh;
    ofPoint position;
    float normScale;
    ofPoint scale;
    
    ofLight	light;

};

#endif
