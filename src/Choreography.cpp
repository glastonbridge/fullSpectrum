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

#include "ofxXmlSettings.h"

void Choreography::setOverlayLibrary(OverlayLibrary* newOverlayLibrary)
{
    _overlayLibrary = newOverlayLibrary;
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
        effect->sensorName=settings.getAttribute("Sensor", "ref","bad ref");
        effect->overlayName=settings.getAttribute("Overlay", "ref","bad ref");
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
    Sensor* sensor;
    Effect* effect(effects[effectName]);
    if (effect->sensorName != "bad ref") sensor = _sensorLibrary->activate(effect->sensorName, width, height);
    Overlay* overlay(_overlayLibrary->activate(effect->overlayName, width, height));
    if (sensor) overlay->attachSensor(sensor);
}
