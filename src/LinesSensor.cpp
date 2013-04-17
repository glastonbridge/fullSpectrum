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


void getRectsOfSize(ofxCvContourFinder& contours, ofxCvGrayscaleImage* in, std::vector<ofPoint>& points, unsigned int minSize, unsigned int maxSize);
void getLinesUsingSquareFinder(ofxCvColorImage * input, std::vector<ofPoint>& points);

enum Location {TOP_LEFT, BOTTOM_LEFT, TOP_RIGHT, BOTTOM_RIGHT, RIGHT};

// y = mx + c
// for bottom left, m=1 and y = -x + c
// but "y" = -y in screen coords
// -y = -x + c, y = x - c, x - y = c
// minimising c means finding the least value of x - y

//iPad runs in portrait mode but looks landscape, so top left becomes bottom left
std::vector<ofPoint> sortPoints(const std::vector<ofPoint> points, Location l = BOTTOM_LEFT)
{
    std::vector<ofPoint> sortedPoints;
    auto locatedAtLocation = points.begin();
    auto pointIter = points.begin() ;
    ++pointIter;
    for (;pointIter < points.end(); ++pointIter)
    {
        if ((l==TOP_LEFT    && ( pointIter->y + pointIter->x <  locatedAtLocation->y + locatedAtLocation->x)) ||
            (l==BOTTOM_LEFT && (-pointIter->y + pointIter->x < -locatedAtLocation->y + locatedAtLocation->x)) ||
            (l==BOTTOM_RIGHT&& ( pointIter->y + pointIter->x >  locatedAtLocation->y + locatedAtLocation->x)) ||
            (l==TOP_RIGHT   && (-pointIter->y + pointIter->x > -locatedAtLocation->y + locatedAtLocation->x)) ||
            (l==RIGHT       && (pointIter->y > locatedAtLocation->y ))
            )
        {
            locatedAtLocation = pointIter;
        }
    }
    sortedPoints.insert(sortedPoints.begin(), locatedAtLocation, points.end());
    sortedPoints.insert(sortedPoints.end(), points.begin(), locatedAtLocation);
    
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
}

// 0 = a, 1 = b, 0.5 = in between
ofPoint interpolate(ofPoint a, ofPoint b, float amount)
{
    ofPoint result(a.x*(1-amount)+b.x*amount, a.y*(1-amount) + b.y*amount);
    return result;
}

ofPoint calculateAverageTranslate(const std::vector<ofPoint>& a, const std::vector<ofPoint>& b)
{
    ofPoint result;
    int pointsConsidered=0;
    while (a.size()>pointsConsidered && b.size()>pointsConsidered)
    {
        result += (b[pointsConsidered] - a[pointsConsidered]);
        ++pointsConsidered;
    }
    result /= pointsConsidered;
    return result;
}

void LinesSensor::analyse(ofxCvColorImage* input)
{
    //points.clear();
    std::vector<ofPoint> newPoints;

    lines.set(0);
    hue = *input;
    
    cvCanny(hue.getCvImage(), lines.getCvImage(), getFloatValue(11), getFloatValue(12));
    
    int minBlob = getIntValue(4);
    int maxBlob = getIntValue(5);
    
    getRectsOfSize(contours, &lines, newPoints, minBlob, maxBlob);
    
    // then get the lines below
    if (newPoints.size()<4) return;
    
    // Assumes points are ccw
    float rectHeight = newPoints[0].distance(newPoints[1]);
    float rectWidth = newPoints[2].distance(newPoints[1]);
    
    //float roiOffsetX = points[0].x-(rectWidth/2);
    //float roiOffsetY = points[2].y +rectHeight;
    //float roiWidth = rectWidth * 2;
    //float roiHeight = rectHeight;
    // iPad constraints
    float roiOffsetX = newPoints[2].x +rectHeight;
    float roiOffsetY = newPoints[2].y-(rectWidth/2);
    float roiWidth = rectHeight;
    float roiHeight = rectWidth * 2;
    
    lines.setROI(roiOffsetX, roiOffsetY, roiWidth, roiHeight);
    //
    // TODO: if we could get a clearer rect for the bottom marker, our recogniser would be better
    contours.findContours(lines, 1, 64, 2, false);
    lines.resetROI();
    
    std::vector<ofPoint> basePoints;
    for (auto contIter = contours.blobs.begin();contIter < contours.blobs.end(); ++contIter)
    {
        // remove the offset caused by constraining the ROI

        // iPad rotated coords, look for the rightest = find the bottomest
        ofPoint unRoiedPoint = sortPoints(contIter->pts, RIGHT)[0];
        unRoiedPoint.x += roiOffsetX;
        unRoiedPoint.y += roiOffsetY;
        basePoints.push_back(unRoiedPoint);
    }
    
    
    ofPoint tx = calculateAverageTranslate(points, newPoints);
    if (basePoints.size()==0 && points.size() == 6) // we have a valid point set and a
    {
        basePoints.push_back(points[4]+tx);
        basePoints.push_back(points[5]+tx);
    }
    else if (basePoints.size()==1 && points.size()==6)
    {
        if (basePoints[0].distance(points[2]) > basePoints[0].distance(points[3])) // on de left hand side
        {
            basePoints.push_back(points[4]+tx);
        }
        else
        {
            basePoints.push_back(points[5]+tx);
        }
    }
    
    basePoints = sortPoints(basePoints);
    newPoints.insert(newPoints.end(), basePoints.begin(), basePoints.end());
    
    // experimental average-forcing.  any really unusual points get replaced with where, on average, they might be
    
    if (points.size() == 6)
    for (int i = 0; i < newPoints.size(); ++i)
    {
        if (abs(newPoints[i].distance(points[i]+tx))>10)
        {
            newPoints[i] = points[i]+tx;
        }
    }
    
    if (newPoints.size()!=6) return;
    
    if (points.size()==newPoints.size())
    {
        for (int i = 0; i < newPoints.size(); ++i)
        {
            points[i] = interpolate(points[i], newPoints[i], 0.5);
        }
    }
    else
    {
        points = newPoints;
    }
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

void getRectsOfSize(ofxCvContourFinder& contours, ofxCvGrayscaleImage* in, std::vector<ofPoint>& points, unsigned int minSize, unsigned int maxSize)
{
    
    // first get the squares
    contours.findContours(*in, minSize*minSize, maxSize*maxSize, 1, false, true);
    
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
                ofPoint b; b.x = approx[j].x; b.y=approx[j].y;
                points.push_back(b);
                
            }
        }
    }
    
    
    points = sortPoints(points);
    
}

std::string LinesSensor::getName() {return NAME;}