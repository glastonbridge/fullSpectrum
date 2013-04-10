//
//  LinesSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/03/2013.
//
//

#include "LinesSensor.h"

#include "ofxCvMain.h"

#include "findsquares.h"

// AverageLine.h reads these values.  Yeah, this whole sensor sucks
static const float MAX_ANGLE_CHANGE =  PI/18;
static const int MAX_POINT_MOVEMENT =  25;// squared for happy math

//#include "AverageLine.h"

const std::string LinesSensor::NAME = "lines sensor";


void getLinesUsingContours(ofxCvContourFinder& contours, std::vector<ofPoint>& points);
void getLinesUsingSquareFinder(ofxCvColorImage * input, std::vector<ofPoint>& points);

std::vector<ofPoint> sortPoints(const std::vector<ofPoint> points)
{
    auto topLeft = points.begin();
    auto pointIter = points.begin() ;
    ++pointIter;
    for (;pointIter < points.end(); ++pointIter)
    {
        if (pointIter->y + pointIter->x < topLeft->y + topLeft->x)
        {
            topLeft = pointIter;
        }
    }
    std::vector<ofPoint> sortedPoints;
    sortedPoints.insert(sortedPoints.begin(), topLeft, points.end());
    sortedPoints.insert(sortedPoints.end(), points.begin(), topLeft);
    return sortedPoints;
}

LinesSensor::LinesSensor()
{
    addFloatParam("threshold1", 0, 0, 255);
    addFloatParam("threshold2",255,0,255);
    addFloatParam("min length",0,0,200);
    addFloatParam("max length",200,0,200);
}

void LinesSensor::setup(float width, float height)
{
    ColouredBlobSensor::setup(width, height);
    hsv.allocate(width,height);
    h.allocate(width,height);
    s.allocate(width,height);
    v.allocate(width,height);
    lines.allocate(width, height);
    
    storage = cvCreateMemStorage(0);
    CvPoint3D32f* positPoints = new CvPoint3D32f[4];
    positPoints[0].x=0; positPoints[0].y=0; positPoints[0].z=0;
    positPoints[1].x=10; positPoints[1].y=0; positPoints[1].z=0;
    positPoints[2].x=10; positPoints[2].y=10; positPoints[2].z=0;
    positPoints[3].x=0; positPoints[3].y=10; positPoints[3].z=0;
    object = cvCreatePOSITObject(positPoints, 4);
}

void LinesSensor::analyse(ofxCvColorImage* input)
{
    //ColouredBlobSensor::analyse(input);
    points.clear();
    //getLinesUsingContours(contours,points);
    //getLinesUsingSquareFinder(input, points);
    //return;
    lines.set(0);
    hue = *input;
    
    
    cvCanny(hue.getCvImage(), lines.getCvImage(), getFloatValue(11), getFloatValue(12));
    
    //lines.blurGaussian();
    
    int minBlob = getIntValue(4);
    int maxBlob = getIntValue(5);
    int numBlobs = getIntValue(6);
    
    // first get the squares
    contours.findContours(lines, 40*40, 90*80, 1, false, true);
    
    getLinesUsingContours(contours,points);
    points = sortPoints(points);
    
    // then get the lines below
    if (points.size()<4) return;
    lines.setROI(points[0].x-10, points[2].y +40, 150, 200);
    contours.findContours(lines, 1, 64, 2, false);
    lines.resetROI();
    
    std::vector<ofPoint> basePoints;
    for (auto contIter = contours.blobs.begin();contIter < contours.blobs.end(); ++contIter)
    {
        // remove the offset caused by constraining the ROI
        ofPoint unRoiedPoint(contIter->boundingRect.getBottomRight());
        unRoiedPoint.x += points[0].x-10;
        unRoiedPoint.y += points[2].y+40;
        basePoints.push_back(unRoiedPoint);
    }
    
    basePoints = sortPoints(basePoints);
    points.insert(points.end(), basePoints.begin(), basePoints.end());
    
    /*CvSeq* foundLines = cvHoughLines2( lines.getCvImage(),
                                      storage,
                                      CV_HOUGH_PROBABILISTIC,
                                      1,
                                      CV_PI/180,
                                      10,
                                      getFloatValue(getParamId("min length")),
                                      getFloatValue(getParamId("max length")));*/
    
    
    
    
}

void getLinesUsingSquareFinder(ofxCvColorImage * input, std::vector<ofPoint>& points)
{
    
    cv::Mat image = input->getCvImage();
    std::vector<std::vector<cv::Point > > squares;
    find_squares(image,squares);
    //hsv = *input;
    //lines = h;
    //return;
    //hsv.convertRgbToHsv();
    //hsv.convertToGrayscalePlanarImage(h, 0);
    
    points.clear();
    
    auto squareIterator = squares.begin();
    for(; squareIterator < squares.end(); ++squareIterator)
    {
        auto lineIterator = squareIterator->begin();
        for (; lineIterator < squareIterator->end(); ++lineIterator)
        {
            ofPoint myPoint;
            myPoint.x = lineIterator->x;
            myPoint.y = lineIterator->y;
            points.push_back(myPoint);
        }
    }
}

void getLinesUsingContours(ofxCvContourFinder& contours, std::vector<ofPoint>& points)
{
    std::vector<ofPoint> smoothedLines;
    
    for (int i = 0; i < contours.blobs.size() ;++i)
    {
        std::vector<cv::Point> approx;
            // approximate contour with accuracy proportional
            // to the contour perimeter
        std::vector<cv::Point> inputs;
        for (int j = 0; j < contours.blobs[i].pts.size() ; ++j)
        {
            cv::Point inpoint;
            inpoint.x = contours.blobs[i].pts[j].x;
            inpoint.y = contours.blobs[i].pts[j].y;
            inputs.push_back(inpoint);
        }
        cv::approxPolyDP(cv::Mat(inputs), approx, arcLength(cv::Mat(inputs), true)*0.02, true);
        
        if (approx.size()==4)
        {
            
            for (int j=0; j<approx.size(); ++j)
            {
                //ofPoint a; a.x = approx[j-1].x; a.y=approx[j-1].y;
                ofPoint b; b.x = approx[j].x; b.y=approx[j].y;
                //points.push_back(a);
                points.push_back(b);
                
            }
            //ofPoint a; a.x = approx[approx.size()-1].x; a.y=approx[approx.size()-1].y;
            //ofPoint b; b.x = approx[0].x; b.y=approx[0].y;
            
            //points.push_back(a);
            //points.push_back(b);
        }
        // the two little blobs
        /*else if (contours.blobs[i].area < 25)
        {
            for (int j = 1; j < contours.blobs[i].pts.size() ; ++j)
            {
                points.push_back(contours.blobs[i].pts[j-1]);
                points.push_back(contours.blobs[i].pts[j]);
            }
        }*/
        
        /*ofxCvBlob& blob = contours.blobs[i];
        
        smoothedLines.push_back(blob.pts[0]); // assumes that the start point is nicely aligned on a corner :/
        
        float oldTrajectory = atan((blob.pts[1].x - blob.pts[0].x)/(blob.pts[1].y - blob.pts[0].y));
        for (int j = 1; j < blob.pts.size(); ++j)
        {
            // if the angle of trajectory changes too much, start a new line
            float trajectory = (blob.pts[j].x - blob.pts[j-1].x)>0 ? PI/2: -PI/2; // div0 safety
            if (blob.pts[j].y != blob.pts[j-1].y)
                trajectory = atan((float)(blob.pts[j].x - blob.pts[j-1].x)/(float)(blob.pts[j].y - blob.pts[j-1].y));
            if (abs(trajectory-oldTrajectory)>MAX_ANGLE_CHANGE &&
                pow(blob.pts[j].x-blob.pts[j-1].x,2)+pow(blob.pts[j].y-blob.pts[j-1].y,2)> MAX_POINT_MOVEMENT
                )
            {
                smoothedLines.push_back(blob.pts[j-1]);
            }
            oldTrajectory = trajectory;
        }
        if (smoothedLines[smoothedLines.size()-1] != blob.pts[blob.pts.size()-1]) smoothedLines.push_back(blob.pts[blob.pts.size()-1]);
        //blob.pts = smoothedLines;
        
        for (int k = 1; k < smoothedLines.size(); ++k)
        {
            points.push_back(smoothedLines[k-1]);
            points.push_back(smoothedLines[k]);
        }*/
    }
    
}

std::string LinesSensor::getName() {return NAME;}