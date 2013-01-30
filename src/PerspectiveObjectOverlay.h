//
//  PerspectiveObjectOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 18/01/2013.
//
//

#ifndef fullSpectrumAnalyser_PerspectiveObjectOverlay_h
#define fullSpectrumAnalyser_PerspectiveObjectOverlay_h

#import "Overlay.h"

#import "ofxAssimpModelLoader.h"

class PerspectiveObjectOverlay : public Overlay
{
public:
    static const std::string NAME;
    virtual std::string getName();
    
    PerspectiveObjectOverlay();
    
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    
protected:
    virtual void paramChanged(int index);
private:
    
    ofPoint* srcPoints, *dstPoints;
    
    ofxAssimpModelLoader model;
    
    ofVboMesh mesh;
    ofPoint position;
    float normScale;
    ofPoint scale;
    
    ofLight	light;
    
    ofImage bob;
};


#endif
