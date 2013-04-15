#pragma once

#ifndef __MACOSX_CORE__

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#include "ofxOpenCv.h"
#include "ofxBlender.h"

#include "VideoOverlayer.h"

class Lens : public ofxiPhoneApp{
	
public:
    void setup();
    void update();
    void draw();
    void exit();
	
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    /** The input data, set from the videoIn */
    float streamHeight, streamWidth;
    
    
private:
    /** The camera input */
    VideoSource videoIn;
    
    /** The bitmap of the camera view, underneath any overlays */
    ofxCvColorImage lensImage;
    
    /** The actual mechanism that does teh overlaying */
    VideoOverlayer videoOverlayer;
    
    // Hack to add in a 3d model
    ofxBlender blendFile;
    ofEasyCam cam;
    ofLight light;

};

#endif


