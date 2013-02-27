//
//  KeypressSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/02/2013.
//
//

#ifndef fullSpectrumAnalyser_KeypressSensor_h
#define fullSpectrumAnalyser_KeypressSensor_h

#include "Sensor.h"

class KeypressSensor : public Sensor
{
public:
    
    static const std::string NAME;
    
    KeypressSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
    bool triggered();
    
private:
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    bool _triggered;
};

#endif
