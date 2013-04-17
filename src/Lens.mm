#include "Lens.h"

#ifndef __MACOSX_CORE__

#include "ThreadedNetwork.h"
#include "PoseSensor.h"

/**
 * Called once, when the app is opened
 */
void Lens::setup(){
    
    //If you want a landscape oreintation
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	// initialize the accelerometer (TODO: is we going to use this?)
	ofxAccelerometer.setup();
	
    ThreadedNetwork::instance = new ThreadedNetwork;
    ThreadedNetwork::instance->start();
    
	
	ofBackground(0,0,0);
    
    //streamWidth =  1280;
    //streamHeight =720;
    streamHeight = 1280;
    streamWidth = 720;
    
    // Request a camera/video.  May not be exactly the dimensions requested, so
    // update streamWidth and streamHeight with the correct data.
    //videoIn.allocateVideo(0,0, "fingers.m4v");
    //videoIn.allocateCamera(streamWidth, streamHeight);
    //videoIn.allocateCamera(streamHeight,streamWidth);
    //streamWidth = videoIn.getWidth();
    //streamHeight = videoIn.getHeight();
    
    videoIn.allocateVideo(streamWidth, streamHeight, "ipadstyle.mov");
    
    videoOverlayer.setVideoInput(&videoIn);

    videoOverlayer.setChoreography("cue-cubetest.xml");
    
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
}

//--------------------------------------------------------------
void Lens::exit(){
    videoIn.stop();
    ThreadedNetwork::instance->stop();
}

//--------------------------------------------------------------
void Lens::touchDown(ofTouchEventArgs & touch){
    PoseSensor::requiresRepositioning =true;
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
