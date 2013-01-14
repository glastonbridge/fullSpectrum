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
    
    streamWidth = 320;
    streamHeight = 240;
    
    // Request a camera/video.  May not be exactly the dimensions requested, so
    // update streamWidth and streamHeight with the correct data.
    //videoIn.allocateVideo(0,0, "fingers.m4v");
    videoIn.allocateCamera(streamWidth, streamHeight);
    streamWidth = videoIn.getWidth();
    streamHeight = videoIn.getHeight();
    
    lensImage.allocate(streamWidth, streamHeight);
    ofSetFrameRate(60);
    
    choreography.setOverlayLibrary(&overlayLibrary);
    choreography.setSensorLibrary(&sensorLibrary);
    
    // Hack to add blendre
    
	glEnable(GL_DEPTH_TEST);
	//ofSetSmoothLighting(true);
    
	blendFile.load("beach.blend");
    
	glShadeModel(GL_SMOOTH);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_DEPTH_TEST);
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
        choreography.onEnterFrame(streamWidth, streamHeight);
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
	blendFile.getActiveScene()->activeCamera = NULL;
	blendFile.getActiveScene()->draw();
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
