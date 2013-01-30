//
//  Sensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/01/2013.
//
//

#include "Parameterisable.h"
#include <string>

/** Not the most efficient use of memory, but byte packing hardly seems worth it */
struct Param
{   
    int type;
    
    std::string name;
    
    Param() {}
    
    Param(const Param &src) :
    type(src.type),
    name(src.name)
    {}
    virtual ~Param(){};
};

struct FloatParam : public Param
{
    float floatVal, floatMax, floatMin;
    
    FloatParam() {};
    FloatParam(const FloatParam& src) :
    Param(src),
    floatVal(src.floatVal),
    floatMax(src.floatMax),
    floatMin(src.floatMin)
    {}
};

struct BoolParam : public Param
{
    bool boolVal;
    BoolParam(){};
    BoolParam(const BoolParam& src) :
    Param(src),
    boolVal(src.boolVal)
    {}
};

struct StringParam : public Param
{
    std::string stringVal;
    StringParam(){};
    StringParam(const StringParam& src) :
    Param(src),
    stringVal(src.stringVal)
    {}
};

struct IntParam : public Param
{
    int intVal, intMax, intMin;
    IntParam() {};
    IntParam(const IntParam& src) :
    Param(src),
    intVal(src.intVal),
    intMax(src.intMax),
    intMin(src.intMin)
    {}
};

int Parameterisable::getParamCount()
{
    return paramValues.size();
}

std::string Parameterisable::getParamName(int index)
{
    return paramValues[index]->name;
}

int Parameterisable::getParamId(const std::string& name)
{
    for (int i = 0; i < paramValues.size(); ++i)
    {
        if (paramValues[i]->name == name) return i;
    }
    return -1;
}

int Parameterisable::getParamType(int index)
{
    return paramValues[index]->type;
}

float Parameterisable::getFloatValue(int index)
{
    return ((FloatParam *) paramValues[index])->floatVal;
}

float Parameterisable::getFloatMax(int index)
{
    return ((FloatParam *) paramValues[index])->floatMax;
}

float Parameterisable::getFloatMin(int index)
{
    return ((FloatParam *) paramValues[index])->floatMin;
}

void Parameterisable::setFloatValue(int index, float value)
{
    ((FloatParam *) paramValues[index])->floatVal = value ;
    paramChanged(index);
}

int Parameterisable::getIntValue(int index)
{
    return ((IntParam *) paramValues[index])->intVal;
}

int Parameterisable::getIntMax(int index)
{
    return ((IntParam *) paramValues[index])->intMax;
}

int Parameterisable::getIntMin(int index)
{
    return ((IntParam *) paramValues[index])->intMin;
}

void Parameterisable::setIntValue(int index, int value)
{
    ((IntParam *) paramValues[index])->intVal = value ;
    paramChanged(index);
}

bool Parameterisable::getBoolValue(int index)
{
    return ((BoolParam *) paramValues[index])->boolVal;
}

void Parameterisable::setBoolValue(int index, bool value)
{
    ((BoolParam *) paramValues[index])->boolVal = value ;
    paramChanged(index);
}

std::string Parameterisable::getStringValue(int index)
{
    return ((StringParam *) paramValues[index])->stringVal;
}

void Parameterisable::setStringValue(int index, const std::string& value)
{
    ((StringParam *) paramValues[index])->stringVal = value ;
    paramChanged(index);
}

void Parameterisable::addFloatParam(std::string name, float defaultValue, float min, float max)
{
    
    FloatParam* newParam = new FloatParam;
    newParam->name = name;
    newParam->type = PARAM_FLOAT;
    newParam->floatVal = defaultValue;
    newParam->floatMin = min;
    newParam->floatMax = max;
    
    paramValues.push_back(newParam);
}

void Parameterisable::addIntParam(std::string name, int defaultValue, int min, int max)
{
    
    IntParam* newParam = new IntParam;
    newParam->name = name;
    newParam->type = PARAM_INT;
    newParam->intVal = defaultValue;
    newParam->intMin = min;
    newParam->intMax = max;
    
    paramValues.push_back(newParam);
}

void Parameterisable::addBoolParam(std::string name, bool defaultValue)
{
    
    BoolParam* newParam = new BoolParam;
    newParam->name = name;
    newParam->type = PARAM_BOOL;
    newParam->boolVal = defaultValue;
    paramValues.push_back(newParam);
}

void Parameterisable::addStringParam(const std::string& name, const std::string& defaultValue)
{
    
    StringParam* newParam = new StringParam;
    newParam->name = name;
    newParam->type = PARAM_STRING;
    newParam->stringVal = defaultValue;
    paramValues.push_back(newParam);
}

Parameterisable::~Parameterisable()
{
    while(paramValues.size()>0)
    {
        delete paramValues.back();
        paramValues.pop_back();
    }
}

void Parameterisable::copyParameters(Parameterisable &dest)
{
    std::vector<Param*>::const_iterator myParam = paramValues.begin();
    for (; myParam < paramValues.end(); ++myParam)
    {
        if ((*myParam)->type==PARAM_BOOL)
        {
            BoolParam* myBoolParam = dynamic_cast<BoolParam*>(*myParam);
            dest.paramValues.push_back(new BoolParam(*myBoolParam));
        }
        else if ((*myParam)->type==PARAM_INT)
        {
            IntParam* myIntParam = dynamic_cast<IntParam*>(*myParam);
            dest.paramValues.push_back(new IntParam(*myIntParam));
        }
        else if ((*myParam)->type==PARAM_FLOAT)
        {
            FloatParam* myFloatParam = dynamic_cast<FloatParam*>(*myParam);
            dest.paramValues.push_back(new FloatParam(*myFloatParam));
        }
        else if ((*myParam)->type==PARAM_FLOAT)
        {
            StringParam* myStringParam = dynamic_cast<StringParam*>(*myParam);
            dest.paramValues.push_back(new StringParam(*myStringParam));
        }
    }
}

void Parameterisable::paramChanged(int id)
{
    // Default implementation does nothing
}
