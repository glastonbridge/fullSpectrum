//
//  Effect.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/01/2013.
//
//

#ifndef fullSpectrumAnalyser_Effect_h
#define fullSpectrumAnalyser_Effect_h

#include <string>
#include <vector>

class Effect
{
public:
    void pushSensor(const std::string& sensorName);
    void pushOverlay(const std::string& overlayName);
    std::vector<std::string> getOverlays();
    std::vector<std::string> getSensors();
    
private:
    std::vector<std::string> sensorNames;
    std::vector<std::string> overlayNames;
};

#endif
