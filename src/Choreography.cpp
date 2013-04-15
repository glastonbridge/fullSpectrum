//
//  Choreography.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#include "Choreography.h"

#include "BlobOverlay.h"
#include "ColourShiftOverlay.h"

#include "ColouredBlobSensor.h"
#include "OverlayLibrary.h"
#include "SensorLibrary.h"
#include "ofxXmlSettings.h"

#include <algorithm>

void Choreography::setOverlayLibrary(OverlayLibrary* newOverlayLibrary)
{
    _overlayLibrary = newOverlayLibrary;
    _overlayLibrary->setChoreography(this);
}

void Choreography::setSensorLibrary(SensorLibrary *newSensorLibrary)
{
    _sensorLibrary = newSensorLibrary;
}

void choreographyLoadValues(ofxXmlSettings& settings, Parameterisable* parameterisable)
{
    unsigned int numParams = settings.getNumTags("Property");
    for (unsigned int p = 0; p < numParams; ++p)
    {
        std::string paramName (settings.getAttribute("Property", "name", "", p));
        int paramIndex = parameterisable->getParamId(paramName);
        if (paramIndex < 0)
        {
            ofLog(OF_LOG_ERROR, std::string("Unknown property ")+paramName+".  Could it be one of these?...");
            for(unsigned int poss = 0; poss < parameterisable->getParamCount(); ++poss)
            {
                ofLog(OF_LOG_ERROR, parameterisable->getParamName(poss));
            }
            continue;
        }
        int paramType = parameterisable->getParamType(paramIndex);
        ofLog(OF_LOG_VERBOSE, std::string("Setting param ")+paramName+" to " +settings.getValue("Property","unknown", p) );
        if (paramType == Parameterisable::PARAM_INT)
        {
            parameterisable->setIntValue(paramIndex, settings.getValue("Property", 0, p));
        }
        else if (paramType == Parameterisable::PARAM_FLOAT)
        {
            parameterisable->setFloatValue(paramIndex, settings.getValue("Property", 0.0, p));
        }
        else if (paramType==Parameterisable::PARAM_BOOL)
        {
            parameterisable->setBoolValue(paramIndex, settings.getValue("Property", "false", p)=="true");
        }
        else if (paramType==Parameterisable::PARAM_STRING)
        {
            parameterisable->setStringValue(paramIndex, settings.getValue("Property", "", p));
        }
    }
}


std::vector<std::string> Choreography::loadCueSheet(std::string path)
{
    ofxXmlSettings settings;
    
    settings.loadFile(path);
    
    settings.pushTag("CueSheet");
    
    unsigned int numSensors = settings.getNumTags("Sensor");
    for (unsigned int i = 0; i < numSensors; ++i)
    {
        std::string sensorType = settings.getAttribute("Sensor", "type", "bad type",i);
        std::string sensorName = settings.getAttribute("Sensor", "id", "bad id",i);
        ofLog(OF_LOG_VERBOSE, std::string("creating sensor ")+sensorName+ " of type "+sensorType);

        Sensor* sensor = _sensorLibrary->addSensor(sensorName, sensorType);
        settings.pushTag("Sensor",i);
        choreographyLoadValues(settings, sensor);
        settings.popTag();
    }
    
    unsigned int numOverlays = settings.getNumTags("Overlay");
    for (unsigned int i = 0; i < numOverlays; ++i)
    {
        std::string overlayType = settings.getAttribute("Overlay", "type", "bad type",i);
        std::string overlayName = settings.getAttribute("Overlay", "id", "bad id",i);
        Overlay* overlay = _overlayLibrary->addOverlay(overlayName, overlayType);
        if (!overlay) ofLog(OF_LOG_ERROR, std::string("could not create overlay of type ") + overlayType);
        settings.pushTag("Overlay",i);
        choreographyLoadValues(settings, overlay);
        settings.popTag();
    }
    
    unsigned int numEffects = settings.getNumTags("Effect");
    for (unsigned int i = 0; i < numEffects; ++i)
    {
        std::string effectId(settings.getAttribute("Effect", "id", "unnamed effect", i));
        settings.pushTag("Effect", i);
        Effect* effect = new Effect;
        std::vector<std::string> attributes;
        bool got = settings.getAttributeNames("Sensor", attributes);
        for (int i=0; i<settings.getNumTags("Sensor"); ++i)
            effect->pushSensor(settings.getAttribute("Sensor", "ref","bad ref", i));
        for (int i=0; i<settings.getNumTags("Overlay"); ++i)
            effect->pushOverlay(settings.getAttribute("Overlay", "ref","bad ref", i));
        effects[effectId]=effect;
        settings.popTag();
    }
    
    std::vector<std::string> startEffectNames;
    unsigned int numStartEffects = settings.getNumTags("InitialEffect");
    for (unsigned int i = 0; i < numStartEffects; ++i)
        startEffectNames.push_back(settings.getAttribute("InitialEffect", "ref", "",i));
    
    settings.popTag();
    return startEffectNames;
}

void Choreography::activateEffect(const std::string &effectName, float width, float height)
{
    Effect* effect(effects[effectName]);
    for (int i = 0; i < activeEffects.size(); ++i) if (activeEffects[i]==effect) return;
    activeEffects.push_back(effect);
    
    std::vector<std::string> sensors(effect->getSensors());
    for (int i = 0; i < sensors.size(); ++i)
    {
        if (sensors[i] != "bad ref") _sensorLibrary->activate(sensors[i], width, height);
    }
    std::vector<std::string> overlays(effect->getOverlays());
    for (int i = 0; i < overlays.size(); ++i)
    {
        Overlay* overlay(_overlayLibrary->activate(overlays[i], width, height));
        for (int j = 0; j < sensors.size(); ++j)
            overlay->attachSensor( (*_sensorLibrary)[sensors[j]]);
    }
    
}

std::string findKeyByValue(const std::map<std::string,Effect*>& map, Effect* effectToFind)
{
    std::map<std::string,Effect*>::const_iterator eff = map.begin();
    for(;eff != map.end(); ++eff)
    {
        if (eff->second == effectToFind)
        {
            return eff->first;
        }
    }
    return "";
}

void Choreography::removeEffect(const std::string& effectName)
{
    Effect* effect = effects[effectName];
    
    // IF not active, do nothing
    std::vector<Effect *>::iterator effectIter = std::find(activeEffects.begin(), activeEffects.end(), effect);
    if (effectIter == activeEffects.end()) return;
    
    std::vector<std::string> overlaysToRemove = effect->getOverlays();
    std::vector<std::string> sensorsToRemove = effect->getSensors();
    
    std::vector<std::string>::iterator mySensor = sensorsToRemove.begin();
    for (;mySensor < sensorsToRemove.end(); ++mySensor)
    {
        if ((*_sensorLibrary)[*mySensor]->isPersistent())
        {
            sensorsToRemove.erase(mySensor);
        }
    }
    
    // Check for other references to this overlay
    // TODO: this would be so much clearer with a reference counted type
    for (int i = 0; i < activeEffects.size(); ++i)
    {
        Effect* effectToTest = activeEffects[i];
        if (effectToTest != effect) // don't include the key to remove when checking for remaining references to s/os
        {
            for (int o = 0; o < effectToTest->getOverlays().size(); ++o)
            {
                std::vector<std::string>::iterator myOverlay = std::find(overlaysToRemove.begin(), overlaysToRemove.end(),effectToTest->getOverlays()[o]);
                if (myOverlay != overlaysToRemove.end())
                {
                    
                    ofLog(OF_LOG_VERBOSE, std::string("not removing overlay ")+(*myOverlay) + " as it is also used by " + findKeyByValue(effects, effectToTest));
                    overlaysToRemove.erase(myOverlay);
                }
            }
            for (int s = 0; s < effectToTest->getSensors().size(); ++s)
            {
                std::vector<std::string>::iterator mySensor = std::find(sensorsToRemove.begin(), sensorsToRemove.end(),effectToTest->getSensors()[s]);
                
                if (mySensor != sensorsToRemove.end())
                {
                    
                    ofLog(OF_LOG_VERBOSE, std::string("not removing sensor ")+(*mySensor) + " as it is also used by "+ findKeyByValue(effects, effectToTest));
                    sensorsToRemove.erase(mySensor);
                    
                }
            }
        }
    }
    
    for (int i = 0; i < overlaysToRemove.size(); ++i)
    {
        _overlayLibrary->removeOverlay(overlaysToRemove[i]);
    }
    for (int i = 0; i < sensorsToRemove.size(); ++i)
    {
        _sensorLibrary->removeSensor(sensorsToRemove[i]);
    }
    
    activeEffects.erase(effectIter);
}

