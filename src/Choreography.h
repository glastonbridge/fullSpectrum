//
//  Choreography.h
//  fullSpectrum
//
//  Created by Alex Shaw on 07/01/2013.
//  Copyright (c) 2013 Glastonbridge Software Limited. All rights reserved.
//

#ifndef fullSpectrum_Choreography_h
#define fullSpectrum_Choreography_h

#include "Effect.h"
#include <map>
#include <string>
#include <vector>

class OverlayLibrary;
class SensorLibrary;

class Choreography
{
public:
    void setOverlayLibrary(OverlayLibrary* newOverlayLibrary);
    void setSensorLibrary(SensorLibrary* newSensorLibrary);
    /** Loads a cue sheet.  Returns the effect that should begin immediately */
    std::vector<std::string> loadCueSheet(std::string path);
    void activateEffect(const std::string& effect, float width, float height);
    void removeEffect(const std::string& effect);
private:
    OverlayLibrary* _overlayLibrary;
    SensorLibrary* _sensorLibrary;
    std::map<std::string, Effect*> effects;
    std::vector<Effect*> activeEffects;
};

#endif
