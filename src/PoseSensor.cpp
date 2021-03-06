//
//  PoseSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/03/2013.
//
//

#include "PoseSensor.h"

#include <sstream>
#include <string>

 const std::string PoseSensor::NAME = "pose";

const float FOCAL_LENGTH = 1160.0;

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
    Pose2Sensor::setup(width, height);
    _width = width; _height = height;
    
    float cubeSize = 15.0;
    modelPoints.push_back(cvPoint3D32f(0.0f, 0.0f, 0.0f));
    modelPoints.push_back(cvPoint3D32f(0.0f, cubeSize, 0.0f));
    modelPoints.push_back(cvPoint3D32f(cubeSize,cubeSize, 0.0f));
    modelPoints.push_back(cvPoint3D32f(cubeSize, 0.0f, 0.0f));
    modelPoints.push_back(cvPoint3D32f(0.0f, 2*cubeSize, 1.5*cubeSize));
    modelPoints.push_back(cvPoint3D32f(cubeSize, 2*cubeSize, 1.5*cubeSize));
  
	initializeIntrinsics( intrinsics, width, height );
	createOpenGLProjectionMatrix(projectionMatrix, intrinsics, width, height, 1.0, 1000.0 );
    
    positObject = cvCreatePOSITObject( &modelPoints[0], static_cast<int>(modelPoints.size()) );
    
    /*extrinsicObject = cvCreateMat(3, 6, CV_32FC1);

    for(int i = 0; i < modelPoints.size(); ++i)
    {
        cvSetReal2D(extrinsicObject,0,i, modelPoints[i].x);
        cvSetReal2D(extrinsicObject,1,i, modelPoints[i].y);
        cvSetReal2D(extrinsicObject,2,i, 0.0);
    }*/
    
    
}
/*
void PoseSensor::orientUsingECP(std::vector<CvPoint2D32f>& projectedPoints, CvMatr32f rotation_matrix, CvVect32f translation_vector_in)
{
    int i=0;
    for (auto point = projectedPoints.begin(); point<projectedPoints.end(); ++point)
    {
        cvSetReal2D(projectedPointsF, i, 0, point->x);
        cvSetReal2D(projectedPointsF, i, 1, point->y);
        ++i;
    }
    for(i=0; i < 3; ++i)
    {
        cvSetReal1D(translation_vector2, i, translation_vector_in[i]);
    }
    
    cvFindExtrinsicCameraParams2(extrinsicObject, projectedPointsF, intrinsics, NULL, rotation_vector, translation_vector2, 1);
    
    cvRodrigues2(rotation_vector, rot_mat, 0);
    
    for (i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            rotation_matrix[i+3*j] = cvGetReal2D(rot_mat, i, j);
    
    for (i=0; i<3; ++i)
        translation_vector_in[i] = cvGetReal1D(translation_vector2,i);
    
}

void dumpMat(const std::string& id, const cv::Mat& mat)
{
    std::stringstream st;
    st << id << ": ";
    for (auto hp = mat.begin<float>(); hp< mat.end<float>(); ++hp)
    {
        st << *hp;
        st << ", ";
    }
    ofLog(OF_LOG_VERBOSE, st.str());
}

void cameraPoseFromHomography(std::vector<CvPoint3D32f>& srcPoints, std::vector<CvPoint2D32f>& dstPoints,  float* poseArray, cv::Mat& pose)
{
    std::vector<cv::Point2d> srcPoints2d;
    
    int count = 0;
    for (auto srcPoint = srcPoints.begin(); srcPoint < srcPoints.end() && count++ < 4 ; ++srcPoint)
        srcPoints2d.push_back(cv::Point2d(srcPoint->x, srcPoint->y));
    
    std::vector<cv::Point2d> dstPointsCpp;
    
    count=0;
    for (auto dstPoint = dstPoints.begin(); dstPoint < dstPoints.end() && count++ < 4 ; ++dstPoint)
        dstPointsCpp.push_back(cv::Point2d(dstPoint->x, dstPoint->y));
    
    cv::Mat H = cv::findHomography(srcPoints2d, dstPointsCpp);
    
    dumpMat("H",H);
    
    pose = cv::Mat::eye(3, 4, CV_64FC1);      // 3x4 matrix, the camera pose
    float norm1 = (float)norm(H.col(0));
    float norm2 = (float)norm(H.col(1));
    float tnorm = (norm1 + norm2) / 2.0f; // Normalization value
    
    cv::Mat p1 = H.col(0);       // Pointer to first column of H
    cv::Mat p2 = pose.col(0);    // Pointer to first column of pose (empty)
    p2.at<float>(1)=5;
    
    cv::normalize(p1, p2);   // Normalize the rotation, and copies the column to pose
    
    //
    //cv::Mat c0 = pose.col(0);
    //p2.copyTo(c0);
    
    //dumpMat("pose", pose);
    //dumpMat("p1",p1);
    //dumpMat("p2",p2);
    //dumpMat("c0",c0);
    //dumpMat("pose", pose);
    
    
    p1 = H.col(1);           // Pointer to second column of H
    p2 = pose.col(1);        // Pointer to second column of pose (empty)
    
    cv::normalize(p1, p2);   // Normalize the rotation and copies the column to pose

    //
    //cv::Mat c1 = pose.col(1);
    //p2.copyTo(c1);
    
    p1 = pose.col(0);
    p2 = pose.col(1);
    
    cv::Mat p3 = p1.cross(p2);   // Computes the cross-product of p1 and p2
    cv::Mat c2 = pose.col(2);    // Pointer to third column of pose
    p3.copyTo(c2);       // Third column is the crossproduct of columns one and two
    
    pose.col(3) = H.col(2) / tnorm;  //vector t [R|t] is the last column of pose
    dumpMat("h",H);
    dumpMat("pose",pose);
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            poseArray[i*4+j] = pose.at<float>(i,j);
}*/

 void PoseSensor::analyse(ofxCvColorImage* input)
{
    //if (!PoseSensor::requiresRepositioning) return;
    Pose2Sensor::analyse(input);
    //if (averageDistanceShift<5) return;
    std::vector<CvPoint2D32f> projectedPoints;
    float halfWidth = _width/2;
    float halfHeight = _height/2;
    std::vector<ofPoint> points = getPoints();
    for (int i=0; i<points.size(); ++i)
    {
        // POSIT points originate from the centre of the screen and y is inverted, so shift (0,0) and invert the y axis
        CvPoint2D32f point;
        point.x = points[i].x -halfWidth;
        point.y = -points[i].y  +halfHeight;
        projectedPoints.push_back(point);
    }
    
    if (projectedPoints.size() != modelPoints.size()) return;
    
    CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 1.0e-4f);
    cvPOSIT( positObject, &projectedPoints[0], FOCAL_LENGTH, criteria, rotation_matrix, translation_vector );
    
    //orientUsingECP(projectedPoints, rotation_matrix, translation_vector);
    //cv::Mat pose(3,4,CV_32FC1);
    //cameraPoseFromHomography(modelPoints, projectedPoints, posePOSIT, pose);
    //return;
    
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
    
    if (posePOSIT[0]==posePOSIT[0]) // not NaN
    {
        float a = posePOSIT[0];
        PoseSensor::requiresRepositioning = false;
    }
    
}


std::string PoseSensor::getName() {return NAME;}