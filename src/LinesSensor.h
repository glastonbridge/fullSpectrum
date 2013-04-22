//
//  LinesSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/03/2013.
//
//

#ifndef fullSpectrumAnalyser_LinesSensor_h
#define fullSpectrumAnalyser_LinesSensor_h

#import "ColouredBlobSensor.h"
#import "ofxOpenCv.h"
#import "ofMain.h"
#import <vector>

class LinesSensor : public ColouredBlobSensor
{
public:
    static const std::string NAME;
    
    LinesSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
    
    ofxCvGrayscaleImage lines;
    
    std::vector<ofPoint> points;
    
    float averageDistanceShift;
private:
    ofxCvGrayscaleImage h,s,v;
    ofxCvColorImage hsv;
    CvMemStorage* storage;
    CvPOSITObject* object;
};

#endif
