//
//  KeypressSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/02/2013.
//
//

#ifndef fullSpectrumAnalyser_KeypressSensor_h
#define fullSpectrumAnalyser_KeypressSensor_h

#include "Trigger.h"
#include "ThreadedNetwork.h"

class KeypressSensor : public Trigger
{
public:
    
    static const std::string NAME;
    
    KeypressSensor();
    ~KeypressSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
    virtual bool triggered();
    
private:
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    void keyMessage(std::string& message);
    bool _triggered;
    static ThreadedNetwork network;
};

#endif
