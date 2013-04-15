//
//  PoseSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/03/2013.
//
//

#include "PoseSensor.h"


 const std::string PoseSensor::NAME = "pose";

const float FOCAL_LENGTH = 760.0;

bool PoseSensor::requiresRepositioning = true;

bool PoseSensor::isPersistent() {return true;}

PoseSensor::PoseSensor()
{
    addFloatParam("focal length", 130,1,500);
};

/**
 Some of this is leeched from here:
 opencv.willowgarage.com/wiki/Posit
 
 This code needs a refactor to be cleaner within the context of openframeworks, which does
 some of this stuff elsewhere
 **/
void initializeIntrinsics(CvMat* intrinsics, const double &width, const double &height )
{
	cvSetZero( intrinsics );
	cvmSet( intrinsics , 0, 0, FOCAL_LENGTH );
	cvmSet( intrinsics , 1, 1, FOCAL_LENGTH );
	cvmSet( intrinsics , 0, 2, width * 0.5 );//principal point in the centre of the image
	cvmSet( intrinsics , 1, 2, height * 0.5 );
	cvmSet( intrinsics , 2, 2, 1.0 );
}

void createOpenGLProjectionMatrix( float* projectionMatrix, CvMat* intrinsics, const float &width, const float &height,
                                         const float &nearPlane, const float &farPlane )
{
	projectionMatrix[0] = 2.0 * cvmGet( intrinsics, 0, 0 ) / width;
	projectionMatrix[1] = 0.0;
	projectionMatrix[2] = 0.0;
	projectionMatrix[3] = 0.0;
    
	projectionMatrix[4] = 0.0;
	projectionMatrix[5] = 2.0 * cvmGet( intrinsics, 1, 1 ) / height;
	projectionMatrix[6] = 0.0;
	projectionMatrix[7] = 0.0;
	
	projectionMatrix[8] = 2.0 * ( cvmGet( intrinsics, 0, 2 ) / width) - 1.0;
	projectionMatrix[9] = 2.0 * ( cvmGet( intrinsics, 1, 2 ) / height ) - 1.0;
	projectionMatrix[10] = -( farPlane+nearPlane ) / ( farPlane - nearPlane );
	projectionMatrix[11] = -1.0;
    
	projectionMatrix[12] = 0.0;
	projectionMatrix[13] = 0.0;
	projectionMatrix[14] = -2.0 * farPlane * nearPlane / ( farPlane - nearPlane );
	projectionMatrix[15] = 0.0;
}

 void PoseSensor::setup(float width, float height)
{
    LinesSensor::setup(width, height);
    _width = width; _height = height;
    
    float cubeSize = 15.0;
    modelPoints.push_back(cvPoint3D32f(0.0f, 0.0f, 0.0f));
    modelPoints.push_back(cvPoint3D32f(0.0f, cubeSize, 0.0f));
    modelPoints.push_back(cvPoint3D32f(cubeSize,cubeSize, 0.0f));
    modelPoints.push_back(cvPoint3D32f(cubeSize, 0.0f, 0.0f));
    modelPoints.push_back(cvPoint3D32f(0.0f, 2*cubeSize, 2*cubeSize));
    modelPoints.push_back(cvPoint3D32f(cubeSize, 2*cubeSize, 2*cubeSize));
  
    
    /*modelPoints.push_back(cvPoint3D32f(0.0f, 0.0f, 0.0f));
    modelPoints.push_back(cvPoint3D32f(cubeSize, 0.0f, 0.0f));
    modelPoints.push_back(cvPoint3D32f(cubeSize,-cubeSize, 0.0f));
    modelPoints.push_back(cvPoint3D32f( 0.0f, -cubeSize, 0.0f));
    modelPoints.push_back(cvPoint3D32f(2*cubeSize, 0.0f, 2*cubeSize));
    modelPoints.push_back(cvPoint3D32f(2*cubeSize, -cubeSize, 2*cubeSize));*/
    
	initializeIntrinsics( intrinsics, width, height );
	createOpenGLProjectionMatrix(projectionMatrix, intrinsics, width, height, 1.0, 1000.0 );
    //initializeIntrinsics( intrinsics, height, width );
	//createOpenGLProjectionMatrix(projectionMatrix, intrinsics, height, width, 1.0, 1000.0 );
    
    positObject = cvCreatePOSITObject( &modelPoints[0], static_cast<int>(modelPoints.size()) );
    
    /*extrinsicObject = cvCreateMat(3, 4, CV_32FC1);

    for(int i = 0; i < modelPoints.size(); ++i)
    {
        cvSetReal2D(extrinsicObject,0,i, modelPoints[i].x);
        cvSetReal2D(extrinsicObject,1,i, modelPoints[i].y);
        cvSetReal2D(extrinsicObject,2,i, 0.0);
    }
    
    for(int i=0; i < 3; ++i)
        for (int j=0; j < 3; ++j)
            cvSetReal2D(intrinsic_matrix,i,j,i==j?1.0:0);
    */
}
 void PoseSensor::analyse(ofxCvColorImage* input)
{
    if (!PoseSensor::requiresRepositioning) return;
    LinesSensor::analyse(input);
    std::vector<CvPoint2D32f> projectedPoints;
    float halfWidth = _width/2;
    float halfHeight = _height/2;
    for (int i=0; i<points.size(); ++i)
    {
        // POSIT points originate from the centre of the screen and y is inverted, so shift (0,0) and invert the y axis
        CvPoint2D32f point;
        point.x = points[i].x -halfWidth;
        point.y = -points[i].y +halfHeight;
        projectedPoints.push_back(point);
    }
    
    if (projectedPoints.size() != modelPoints.size()) return;
    
    CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 1.0e-4f);
    
    
    cvPOSIT( positObject, &projectedPoints[0], FOCAL_LENGTH, criteria, rotation_matrix, translation_vector );
    
    
    //cvFindExtrinsicCameraParams2(extrinsicObject, projectedPointsF, intrinsic_matrix, NULL, rotation_vector, translation_vector);
    
    //cvRodrigues2(rotation_vector, rot_mat, 0);
    
    for (int f=0; f<3; f++)
        for (int c=0; c<3; c++)
            posePOSIT[c*4+f] = rotation_matrix[f*3+c];      //transposed cvGetReal2D(rot_mat,f,c);
    posePOSIT[3] = 0.0;
    posePOSIT[7] = 0.0;
    posePOSIT[11] = 0.0;
    posePOSIT[12] = translation_vector[0];
    posePOSIT[13] = translation_vector[1];
    posePOSIT[14] = translation_vector[2];
    posePOSIT[15] = 1.0;

    /*posePOSIT[12] = cvGetReal2D(translation_vector,0,0);
    posePOSIT[13] = cvGetReal2D(translation_vector,0,1);
     posePOSIT[14] = cvGetReal2D(translation_vector,0,2);*/
    
    if (posePOSIT[0]==posePOSIT[0]) // not NaN
    {
        float a = posePOSIT[0];
        PoseSensor::requiresRepositioning = false;
    }
    
}

std::string PoseSensor::getName() {return NAME;}