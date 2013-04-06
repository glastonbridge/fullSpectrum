#include "Lens.h"

#ifndef __MACOSX_CORE__

/**
 * Called once, when the app is opened
 */
void Lens::setup(){	
	// initialize the accelerometer (TODO: is we going to use this?)
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(0,0,0);
    
    streamWidth =  1280;
    streamHeight =720;
    
    // Request a camera/video.  May not be exactly the dimensions requested, so
    // update streamWidth and streamHeight with the correct data.
    //videoIn.allocateVideo(0,0, "fingers.m4v");
    //videoIn.allocateCamera(streamWidth, streamHeight);
    //streamWidth = videoIn.getWidth();
    //streamHeight = videoIn.getHeight();
    
    videoIn.allocateVideo(streamWidth, streamHeight, "walkabout.mov");
    
    lensImage.allocate(streamWidth, streamHeight);
    ofSetFrameRate(60);
    
    choreography.setOverlayLibrary(&overlayLibrary);
    choreography.setSensorLibrary(&sensorLibrary);
    std::vector<std::string> startEffects = choreography.loadCueSheet("cue-lines.xml");
    
    std::vector<std::string>::const_iterator startEffect = startEffects.begin();
    for(;startEffect<startEffects.end(); ++startEffect)
        choreography.activateEffect(*startEffect, streamWidth, streamHeight);

}

/**
 * Do all frame processing that is not directly related to the user viewport.
 * The user viewport will be updated in draw()
 */
void Lens::update(){
    
    ofBackground(0);
    videoIn.update();
    if (videoIn.isFrameNew())
    {
        if (videoIn.getPixels()) lensImage.setFromPixels(videoIn.getPixels(), streamWidth, streamHeight);
        sensorLibrary.onEnterFrame(&lensImage);
        overlayLibrary.update(&lensImage);
    }
    
}

/**
 * Render the display
 */
void Lens::draw(){
	lensImage.draw(0,0);
    overlayLibrary.draw();
    
	cam.begin();
	ofScale(50, 50, 50);
}

//--------------------------------------------------------------
void Lens::exit(){
    videoIn.stop();
}

//--------------------------------------------------------------
void Lens::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void Lens::touchMoved(ofTouchEventArgs & touch){

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
