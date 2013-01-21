//
//  PerspectiveQuadSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 16/01/2013.
//
//

#include "PerspectiveQuadSensor.h"

const std::string PerspectiveQuadSensor::NAME="perspective quad sensor";

std::string PerspectiveQuadSensor::getName()
{
    return NAME;
}

void PerspectiveQuadSensor::setup(float width, float height)
{
    ColouredBlobSensor::setup(width, height);
    
    setIntValue(getParamId("hue range"),21); // 0
    setIntValue(getParamId("hue offset"), 96);// 1
    setIntValue(getParamId("sat threshold"),33);// 2
    setIntValue(getParamId("val threshold"), 74); // 3
    
    setIntValue(getParamId("min blob width"), 8); // 4
    setIntValue(getParamId("max blob width"), 200); // 5
    setIntValue(getParamId("num blobs"), 4); // 6
    
    cvWarpMatrix = cvCreateMat(3,3,CV_32FC1);
}

void PerspectiveQuadSensor::analyse(ofxCvColorImage* input)
{
    
    ColouredBlobSensor::analyse(input);
    if (contours.blobs.size()!=4) return;
    
    vector<ofxCvBlob> topToBottom;
    
    
    //TODO: blob copying, use pass by reference
    vector<ofxCvBlob>::const_iterator blobSearch = contours.blobs.begin();
    topToBottom.push_back(*blobSearch);
    int expectedSize = 1;
    for (++blobSearch; blobSearch < contours.blobs.end(); ++blobSearch)
    {
        vector<ofxCvBlob>::iterator blobInsert = topToBottom.begin();
        for (; blobInsert < topToBottom.end(); ++blobInsert)
        {
            if (blobSearch->centroid.y>blobInsert->centroid.y)
            {
                // blobInsert is the insert point, blobSearch is the blob to insert
                topToBottom.insert(blobInsert, *blobSearch);
                break;
            }
        }
        if (++expectedSize != topToBottom.size())
            topToBottom.push_back(*blobSearch);
    }
    CvPoint2D32f plainQuad[4], dstQuad[4];
    plainQuad[0].x=0;
    plainQuad[0].y=0;
    plainQuad[1].x=10;
    plainQuad[1].y=0;
    plainQuad[2].x=0;
    plainQuad[2].y=10;
    plainQuad[3].x=10;
    plainQuad[4].y=10;
    
    
    if (topToBottom[0].centroid.x<topToBottom[1].centroid.x)
    {
        bottomLeft=topToBottom[0].centroid; bottomRight = topToBottom[1].centroid;
    }
    else
    {
        bottomLeft=topToBottom[1].centroid; bottomRight = topToBottom[0].centroid;
    }
    
    if (topToBottom[2].centroid.x<topToBottom[3].centroid.x)
    {
        topLeft=topToBottom[2].centroid; topRight = topToBottom[3].centroid;
    }
    else
    {
        topLeft=topToBottom[3].centroid; topRight = topToBottom[2].centroid;
    }
    
    return;
    
    bottomRight.y -= topLeft.y;
    bottomRight.x -= topLeft.x;
    topRight.y -= topLeft.y;
    topRight.x -= topLeft.x;
    bottomLeft.y -= topLeft.y;
    bottomLeft.x -= topLeft.x;
    
    topLeft.x = 0;
    topLeft.y = 0;
    
    return;
    
    dstQuad[0].x = topLeft.x;
    dstQuad[0].y = topLeft.y;
    dstQuad[1].x = topRight.x;
    dstQuad[1].y = topRight.y;
    dstQuad[2].x = bottomLeft.x;
    dstQuad[2].y = bottomLeft.y;
    dstQuad[3].x = bottomRight.x;
    dstQuad[3].y = bottomRight.y;
    
    
    cvGetPerspectiveTransform(plainQuad, dstQuad, cvWarpMatrix);
}
