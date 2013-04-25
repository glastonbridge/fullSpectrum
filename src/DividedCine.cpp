//
//  DividedCine.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 24/04/2013.
//
//

#include "DividedCine.h"
#include "PoseSensor.h"
#include "ImageUtils.h"

 const std::string DividedCine::NAME = "divided cine";
 void DividedCine::update(ofxCvColorImage* input)
{
    cineFilter.update(input);
    PoseSensor* sensor = dynamic_cast<PoseSensor *>(sensors[0]);
    // pose a point on screen to determine where the boundary of the cine should be
    float modelPoint[] =  { getFloatValue("centre x"), 0, getFloatValue("centre z"), 1.0f };
    CvMat modelPointMatrix = cvMat( 4, 1, CV_32F, modelPoint );
    float point3D[4];
    CvMat poseMatrix = cvMat( 4, 4, CV_32F, sensor->posePOSIT );
    CvMat point3DMatrix = cvMat( 4, 1, CV_32F, point3D );
    cvGEMM( &poseMatrix , &modelPointMatrix, 1.0, NULL, 0.0, &point3DMatrix, CV_GEMM_A_T );
    
    //Project the transformed 3D points
    CvPoint2D32f point2D = cvPoint2D32f( 0.0, 0.0 );
    if ( point3D[2] != 0 )
    {
        point2D.x = cvmGet( sensor->intrinsics, 0, 0 ) * point3D[0] / point3D[2];
        point2D.y = cvmGet( sensor->intrinsics, 1, 1 ) * point3D[1] / point3D[2];
    }
    
    ofEnableAlphaBlending();
    cineFilter.getFbo().begin();
    
	glColorMask(0, 0, 0, 1);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
    ofSetColor(0,0,0,255);
    ofRect(0,-point2D.y+input->getHeight()/2,
                         input->getWidth(), point2D.y+input->getHeight()/2);
    glColorMask(1, 1, 1, 1);
    ofSetColor(255,255,255,255);
    cineFilter.getFbo().end();
    ofDisableAlphaBlending();
    
    
}
 void DividedCine::draw()
{
    ofEnableAlphaBlending();
    cineFilter.getFbo().draw(0,0);
    ofDisableAlphaBlending();
    //borderMask.draw(0,0);
}

 void DividedCine::setup(float width, float height)
{
    cineFilter.allocate(width, height);
}

 std::string DividedCine::getName() {return NAME;}

DividedCine::DividedCine()
{
    addFloatParam("centre x", 8, -80, 80);
    addFloatParam("centre z", 30, 0, 100);
    
}
