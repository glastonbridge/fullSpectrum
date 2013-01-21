//
//  Parameterisable.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 16/01/2013.
//
//

#ifndef fullSpectrumAnalyser_Parameterisable_h
#define fullSpectrumAnalyser_Parameterisable_h

#import <vector>
#import <string>

struct Param;

class Parameterisable
{
public:
    static const int PARAM_FLOAT = 1;
    static const int PARAM_BOOL = 2;
    static const int PARAM_INT = 3;
    
    virtual std::string getName() = 0;
    int getParamCount();
    std::string getParamName(int index);
    int getParamType(int index);
    float getFloatValue(int index);
    float getFloatMax(int index);
    float getFloatMin(int index);
    void setFloatValue(int index, float value);
    int getIntValue(int index);
    int getIntMax(int index);
    int getIntMin(int index);
    void setIntValue(int index, int value);
    bool getBoolValue(int index);
    void setBoolValue(int index, bool value);
    
    int getParamId(const std::string& name);
    
    
    virtual ~Parameterisable();
protected:
    void addFloatParam(std::string name, float defaultValue, float min, float max);
    void addIntParam(std::string name, int defaultValue, int min, int max);
    void addBoolParam(std::string name, bool defaultValue);
    
private:
    // TODO: support values other than floats
    std::vector<Param*> paramValues;
    std::vector<std::string> parameterNames;

};

#endif
