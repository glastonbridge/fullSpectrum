#include "ofMain.h"
#include "Lens.h"
#include "ofxiPhone.h"

#ifndef __MACOSX_CORE__

int main(){
	
    ofSetLogLevel(OF_LOG_VERBOSE);
    
	ofSetupOpenGL(1024,768, OF_FULLSCREEN);			// <-------- setup the GL context

	ofRunApp(new Lens);
}
#endif
