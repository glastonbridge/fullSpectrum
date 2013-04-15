//
//  KeypressSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/02/2013.
//
//

#include "KeypressSensor.h"
#include "ofxNetwork.h"

static const bool useNetwork = true;

const std::string KeypressSensor::NAME = "keypress";



KeypressSensor::KeypressSensor()
{
    addStringParam("key", " ");

}

KeypressSensor::~KeypressSensor()
{
}

void KeypressSensor::setup(float width, float height)
{
    if (useNetwork)
    {
        ofAddListener(ThreadedNetwork::networkKeypressEvent, this, &KeypressSensor::keyMessage);
    }
    else
    {
        ofAddListener(ofEvents().keyPressed, this, &KeypressSensor::keyPressed);
        ofAddListener(ofEvents().keyReleased, this, &KeypressSensor::keyReleased);        
    }
}

void KeypressSensor::analyse(ofxCvColorImage* input)
{
}

std::string KeypressSensor::getName() {return NAME;}

bool KeypressSensor::triggered()
{
    return _triggered;
}

void KeypressSensor::keyPressed(ofKeyEventArgs& args)
{
    unsigned char myKey = getStringValue(0)[0];
    if (args.key==myKey)
    {
        _triggered = true;
    }
}
void KeypressSensor::keyReleased(ofKeyEventArgs& args)
{
    
    if (args.key==getStringValue(0)[0])
    {
        _triggered = false;
    }
}
void KeypressSensor::keyMessage(std::string& message)
{
    unsigned char myKey = getStringValue(0)[0];
    if (message[0]==myKey)
    {
        _triggered = true;
    }
    else
    {
        _triggered = false;
    }
}

