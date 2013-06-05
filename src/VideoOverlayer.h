//
//  VideoOverlayer.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 10/04/2013.
//
//

#ifndef fullSpectrumAnalyser_VideoOverlayer_h
#define fullSpectrumAnalyser_VideoOverlayer_h

#include "VideoSource.h"
#include <string>
#include "Choreography.h"
#include "ofxCvMain.h"
#include "OverlayLibrary.h"
#include "SensorLibrary.h"

class VideoOverlayer
{
public:
    VideoOverlayer();
    void setVideoInput(VideoSource* newVideoIn);
    void setChoreography(const std::string path);
    
    void update();
    void draw();
    
    std::vector<Overlay*> getActiveOverlays();
    std::vector<Sensor*> getActiveSensors();
    std::vector<Effect*> getActiveEffects();
    Overlay* getNamedOverlay(const std::string& name);
    Sensor* getNamedSensor(const std::string& name);
    void addEffect(const std::string& effectName);
    void removeEffect(const std::string& effectName);
    std::vector<std::string> getAllEffectNames();
    
private:
    /** The input data, set from the videoIn */
    float streamHeight, streamWidth;
    
    /** The camera input */
    VideoSource* videoIn;
    
    /** The bitmap of the camera view, underneath any overlays */
    ofxCvColorImage lensImage;
    
    /** The choreography that we are following */
    Choreography choreography;
    
    /** The overlays in our possession */
    OverlayLibrary overlayLibrary;
    
    /** The sensors being applied to the scene */
    SensorLibrary sensorLibrary;
    
    /** A workaround for the fact that we need to constrain the viewport for perspective things 
     this should not be necessary in iPad mode, but provided the camera and screen widths match it
     shouldn't matter.
     */
    void setOrthoScale();
    void unsetOrthoScale();
};

#endif
