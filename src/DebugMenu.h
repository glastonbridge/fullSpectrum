//
//  DebugMenu.h
//  fullSpectrum
//
//  Created by Alex Shaw on 24/05/2013.
//
//

#ifndef fullSpectrum_DebugMenu_h
#define fullSpectrum_DebugMenu_h

#include "ofxUI.h"
#include "VideoOverlayer.h"
#include <memory>

class DebugMenu
{
public:
    DebugMenu();
    void setSize(float width, float height);
    void setVideoOverlayer(VideoOverlayer* newVideoOverlayer);
    void setVisible(bool visible);
    bool getVisible();
private:
    
    /** Our GUI widgets */
    std::auto_ptr<ofxUIScrollableCanvas> parameterTweakGui;
    std::auto_ptr<ofxUICanvas> tabBar;
    
    void recalculateParameterTweakUI();
    void drawTabBar();
    
    VideoOverlayer* videoOverlayer;
    std::string activeOverlay;
    
    /** Callbacks */
    void parameterisableGuiEvent(ofxUIEventArgs &e);
    void tabGuiEvent(ofxUIEventArgs &e);
    
};

#endif
