//
//  Trigger.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 06/04/2013.
//
//

#ifndef fullSpectrumAnalyser_Trigger_h
#define fullSpectrumAnalyser_Trigger_h

#include "Sensor.h"

class Trigger : public Sensor
{
public:
    
    virtual bool triggered()=0;

};

#endif
