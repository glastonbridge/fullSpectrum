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
    static const int PARAM_STRING = 4;
    
    virtual std::string getName() = 0;
    virtual void setInstanceName(const std::string& name);
    virtual const std::string& getInstanceName();
    int getParamCount();
    std::string getParamName(int index);
    int getParamType(int index);
    float getFloatValue(int index);
    float getFloatValue(const std::string& name);
    float getFloatMax(int index);
    float getFloatMin(int index);
    void setFloatValue(int index, float value);
    int getIntValue(int index);
    int getIntValue(const std::string& name);
    int getIntMax(int index);
    int getIntMin(int index);
    void setIntValue(int index, int value);
    bool getBoolValue(int index);
    void setBoolValue(int index, bool value);
    std::string getStringValue(int index);
    std::string getStringValue(const std::string& name);
    void setStringValue(int index, const std::string& value);
    
    int getParamId(const std::string& name);
    
    virtual ~Parameterisable();
    void copyParameters(Parameterisable& dest);
protected:
    void addFloatParam(std::string name, float defaultValue, float min, float max);
    void addIntParam(std::string name, int defaultValue, int min, int max);
    void addBoolParam(std::string name, bool defaultValue);
    void addStringParam(const std::string& name, const std::string& defaultValue);
    
    
    /** Override this if you want to be notified when a parameter changes */
    virtual void paramChanged(int id);
    
private:
    std::vector<Param*> paramValues;
    std::string instanceName;
};

#endif
