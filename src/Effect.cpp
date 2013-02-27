//
//  Effect.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 22/02/2013.
//
//

#include "Effect.h"

void Effect::pushSensor(const std::string& sensorName)
{
    sensorNames.push_back(sensorName);
}

void Effect::pushOverlay(const std::string& overlayName)
{
    overlayNames.push_back(overlayName);
}

std::vector<std::string> Effect::getOverlays()
{
    return overlayNames;
}

std::vector<std::string> Effect::getSensors()
{
    return sensorNames;
}
