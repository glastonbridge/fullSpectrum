#include "Lens.h"

#ifndef __MACOSX_CORE__

#include "ThreadedNetwork.h"
#include "PoseSensor.h"

#include "DebugMenu.h"

const bool fakeNetworkButton = false;
const bool useDebugMenu = true;

/**
 * Called once, when the app is opened
 */
void Lens::setup(){
    
    //If you want a landscape oreintation
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	// initialize the accelerometer (TODO: is we going to use this?)
	//ofxAccelerometer.setup();
	
    ThreadedNetwork::instance = new ThreadedNetwork;
    ThreadedNetwork::instance->start();
    
	
	ofBackground(0,0,0);
    
    //streamWidth =  1280;
    //streamHeight =720;
    streamHeight = 1280;
    streamWidth = 720;
    
    // Request a camera/video.
    videoIn.allocateCamera(streamHeight,streamWidth); //  ipad camera needs to be allocated in landscape, regardless of screen
    
    //videoIn.allocateVideo(streamWidth, streamHeight, "infrontofmarker.mov");
    
    videoOverlayer.setVideoInput(&videoIn);

    videoOverlayer.setChoreography("cue-sometests.xml");
    
    if (useDebugMenu)
    {
        debugMenu.setSize(ofGetWidth(), ofGetHeight());
        debugMenu.setVideoOverlayer(&videoOverlayer);
    }
}

/**
 * Do all frame processing that is not directly related to the user viewport.
 * The user viewport will be updated in draw()
 */
void Lens::update(){
    
    ofBackground(0);
    videoOverlayer.update();
}


/**
 * Render the display
 */
void Lens::draw(){
    videoOverlayer.draw();
    
    if (fakeNetworkButton)
    {
        std::string nextButtonPress;
        std::vector<Effect *> activeEffects = videoOverlayer.getActiveEffects();
        for (auto e = activeEffects.begin(); e < activeEffects.end(); ++e)
        {
            if (videoOverlayer.getNamedOverlay((*e)->getOverlays()[0])->getName()=="effect change")
            {
                nextButtonPress = (*e)->getOverlays()[0];
                continue;
            }
        }
        ofSetColor(255,0,255);
        ofDrawBitmapString(std::string("tap to do: ") + nextButtonPress, 20, 20);
        ofSetColor(255,255,255);
    }
}


//--------------------------------------------------------------
void Lens::exit(){
    videoIn.stop();
    ThreadedNetwork::instance->stop();
}

//--------------------------------------------------------------
void Lens::touchDown(ofTouchEventArgs & touch){
    //PoseSensor::requiresRepositioning =true;
    if (fakeNetworkButton)
    {
        std::vector<Effect *> activeEffects = videoOverlayer.getActiveEffects();
        for (auto e = activeEffects.begin(); e < activeEffects.end(); ++e)
        {
            if (videoOverlayer.getNamedOverlay((*e)->getOverlays()[0])->getName()=="effect change")
            {
                std::string pressKey = videoOverlayer.getNamedSensor((*e)->getSensors()[0])->getStringValue("key");
                ofNotifyEvent(ThreadedNetwork::networkKeypressEvent, pressKey);
            }
        }
    }
    
    ofRectangle hitRect(0,ofGetHeight()-50,50,50);
    
    if (useDebugMenu)
    {
        if (hitRect.inside(touch.x, touch.y))
            debugMenu.setVisible(!debugMenu.getVisible());
    }
    
    // Sneaky hack for parameterising the mottled cine
    /*Overlay* cine = videoOverlayer.getNamedOverlay("cine");
    int radiusIndex = cine->getParamId("circle radius");
    float minPoint = cine->getFloatMin(radiusIndex);
    float maxPoint = cine->getFloatMax(radiusIndex);
    float newValue = minPoint + touch.y * (maxPoint - minPoint) / ofGetHeight();
    cine->setFloatValue(radiusIndex, newValue);*/
}

//--------------------------------------------------------------
void Lens::touchMoved(ofTouchEventArgs & touch){
    
    // Sneaky hack for parameterising the mottled cine
    /*Overlay* cine = videoOverlayer.getNamedOverlay("cine");
    int radiusIndex = cine->getParamId("circle radius");
    float minPoint = cine->getFloatMin(radiusIndex);
    float maxPoint = cine->getFloatMax(radiusIndex);
    float newValue = minPoint + touch.y * (maxPoint - minPoint) / ofGetHeight();
    cine->setFloatValue(radiusIndex, newValue);*/
}

//--------------------------------------------------------------
void Lens::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void Lens::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void Lens::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void Lens::lostFocus(){

}

//--------------------------------------------------------------
void Lens::gotFocus(){

}

//--------------------------------------------------------------
void Lens::gotMemoryWarning(){

}

//--------------------------------------------------------------
void Lens::deviceOrientationChanged(int newOrientation){

}

#endif
