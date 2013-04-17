#include "ofMain.h"
#include "Lens.h"

#ifndef __MACOSX_CORE__

#include "ofxiPhone.h"
int main(){
	
    ofSetLogLevel(OF_LOG_VERBOSE);
    
	ofSetupOpenGL(1024,768, OF_FULLSCREEN);			// <-------- setup the GL context

	ofRunApp(new Lens);
}
#endif
