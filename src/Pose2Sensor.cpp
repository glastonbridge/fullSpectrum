//
//  Pose2Sensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 25/04/2013.
//
//

#include "Pose2Sensor.h"


 const std::string Pose2Sensor::NAME = "pose 2";

Pose2Sensor::Pose2Sensor() {}

void Pose2Sensor::setup(float width, float height)
{
    ColouredBlobSensor::setup(width,height);
}


enum Location {TOP_LEFT, BOTTOM_LEFT, TOP_RIGHT, BOTTOM_RIGHT, RIGHT};

static std::vector<ofPoint> sortPoints(const std::vector<ofPoint> points, Location l = BOTTOM_LEFT)
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

void getRectsFromContours(ofxCvContourFinder& contours, std::vector<ofPoint>& points)
{
    
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

static ofPoint interpolate(ofPoint a, ofPoint b, float amount)
{
    ofPoint result(a.x*(1-amount)+b.x*amount, a.y*(1-amount) + b.y*amount);
    return result;
}

static ofPoint calculateAverageTranslate(const std::vector<ofPoint>& a, const std::vector<ofPoint>& b)
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

void Pose2Sensor::analyse(ofxCvColorImage* input)
{
    ColouredBlobSensor::analyse(input);
    
    //points.clear();
    std::vector<ofPoint> newPoints;
   
    getRectsFromContours(contours,newPoints);
    
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
    
    hue.setROI(roiOffsetX, roiOffsetY, roiWidth, roiHeight);
    //
    // TODO: if we could get a clearer rect for the bottom marker, our recogniser would be better
    contours.findContours(hue, 1, 32*32, 2, false);
    hue.resetROI();
    
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
    if (basePoints.size()==0 && points.size() == 6) // we have a valid point set and our current reading failed to find the base rect
    {
        basePoints.push_back(points[4]+tx);
        basePoints.push_back(points[5]+tx);
    }
    else if (basePoints.size()==1 && points.size()==6)
    {
        if (basePoints[0].distance(points[1]) > basePoints[0].distance(points[2])) // on de left hand side
        {
            basePoints.insert(basePoints.begin(), points[4]+tx);
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
        averageDistanceShift = ofPoint::zero().distanceSquared(tx);
    }
    else
    {
        // only called if points has been cleared
        points = newPoints;
        averageDistanceShift = MAXFLOAT;
    }
}

std::string Pose2Sensor::getName()
{
    return NAME;
}


