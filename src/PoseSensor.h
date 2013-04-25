//
//  PoseSensor.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/03/2013.
//
//

#ifndef fullSpectrumAnalyser_PoseSensor_h
#define fullSpectrumAnalyser_PoseSensor_h

//#include "LinesSensor.h"
#include "Pose2Sensor.h"

//class CvMat;

class PoseSensor : public Pose2Sensor
{
public:
    static const std::string NAME;
    
    PoseSensor();
    
    virtual void setup(float width, float height);
    virtual void analyse(ofxCvColorImage* input);
    virtual std::string getName();
    
    float posePOSIT[16];
    
    CvMatr32f rotation_matrix = new float[9];
    CvVect32f translation_vector = new float[3];
    
	float projectionMatrix[16];
    std::vector<CvPoint3D32f> modelPoints;
    
    static bool requiresRepositioning;
    
    virtual bool isPersistent();
	CvMat* intrinsics = cvCreateMat( 3, 3, CV_32F );
private:
    
    // Experimental FindExtrinsicCameraParams datatypes.  We just box and unbox into these as necessary
    /*CvMat* extrinsicObject;
    CvMat *rot_mat = cvCreateMat( 3, 3, CV_32FC1);
    CvMat* projectedPointsF = cvCreateMat(6, 2, CV_32FC1);
    CvMat *rotation_vector = cvCreateMat( 1, 3, CV_32FC1);
    CvMat *translation_vector2 = cvCreateMat( 1, 3, CV_32FC1);*/
    
    float _width, _height;
    
    
    CvPOSITObject *positObject;
    
    //void orientUsingECP(std::vector<CvPoint2D32f>& projectedPoints, CvMatr32f rotation_matrix, CvVect32f translation_vector);
    
};

#endif
