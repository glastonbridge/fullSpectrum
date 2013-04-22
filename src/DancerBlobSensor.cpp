//
//  DancerBlobSensor.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/02/2013.
//
//

#include "DancerBlobSensor.h"


const std::string DancerBlobSensor::NAME="dancer blob sensor";

DancerBlobSensor::DancerBlobSensor()
{
    addFloatParam("threshold1", 0, 0, 255);
    addFloatParam("threshold2",255,0,255);
    setBoolValue(10,true);
};

void DancerBlobSensor::setup(float width, float height)
{
    //ColouredBlobSensor::setup(width,height);
    val.allocate(width/2, height/2);
    lines.allocate(width/2,height/2);
    dancerArea.allocate(width,height);
    lastKnownGood.set(0,0,0,0);
}

void DancerBlobSensor::analyse(ofxCvColorImage* input)
{   /*
     All this stuff is here to try to heuristically `filter out the marker rects.  It doesn't work
    hsv = *input;
    hsv.convertRgbToHsv();
    hsv.convertToGrayscalePlanarImages(hue,sat,val);
    huemax = hue;
    int hueRange = getIntValue(0);
    int hueOffset = getIntValue(1);
    hue.threshold(hueOffset);
    huemax.threshold(hueOffset + hueRange);
    hue -= huemax;
    
    int valVal = getIntValue(3);
    val.threshold(valVal);
    bool valInv = getBoolValue(7);
    if (valInv) val.invert();
    
    sat.threshold(getIntValue(2));
    if (getBoolValue(8)) sat.invert();
    
    if (getBoolValue(9)) hue.invert();
    
    sat &= val;
    hue &= sat;
    
    contours.findContours(hue, 10, 100*100, 4, false, true); // used in a moment to fill gaps
    
    hue.invert();
    hue.erode();
    // reuse val
    val = *input;
    
    lines.set(0);
    cvCanny(val.getCvImage(), lines.getCvImage(), getFloatValue("threshold1"), getFloatValue("threshold2"));    
    lines &= hue;
    
    for (auto blob = contours.blobs.begin(); blob < contours.blobs.end(); ++blob)
    {
        auto pointB = blob->pts.begin();
        auto pointA = pointB;
        ++pointB;
        for (;pointB < blob->pts.end(); ++pointB)
        {
            if ((*pointA).distanceSquared(*pointB) < 70)
            {
                // draw a line, this is a short contour and so should be considered an end point if it meets the dancer
                cvDrawCircle(lines.getCvImage(), cvPoint(pointA->x, pointA->y), 2, cvScalar(255,255,255));
                cvDrawCircle(lines.getCvImage(), cvPoint(pointB->x, pointB->y), 2, cvScalar(255,255,255));
                cvDrawLine(lines.getCvImage(), cvPoint(pointA->x, pointA->y),cvPoint(pointB->x, pointB->y), cvScalar(255,255,255));
            }
            pointA = pointB;
        }
        
        if ((blob->pts.begin())->distanceSquared(*pointB) < 70)            {
            // draw a line, this is a short contour and so should be considered an end point if it meets the dancer
            cvDrawLine(lines.getCvImage(), cvPoint(pointA->x, pointA->y),cvPoint(pointB->x, pointB->y), cvScalar(255,255,255));
        }
    }
    
    lines.blurGaussian();
    lines.blurGaussian();
    */
    
    // From here on, we are working on half-size elements
    sat = *input;
    val.scaleIntoMe(sat, CV_INTER_NN);

    /*if (lastKnownGood.getMinX()!=0 && --timeout>0)
    {
        lastKnownGood.scaleFromCenter(1.24);
        //input->setROI(lastKnownGood);
        val.setROI(lastKnownGood);
        lines.setROI(lastKnownGood);
        --timeout;
    }*/
    
    // canny lines generally give a crisper, more reliable outline than chromakeys, but they
    // need to be blurred or gaps kill the contour finder
    lines.set(0);
    cvCanny(val.getCvImage(), lines.getCvImage(), getFloatValue("threshold1"), getFloatValue("threshold2"));
    lines.blur(3);
    
    float minBlob = getIntValue(4);
    float maxBlob = getIntValue(5);
    contours.findContours(lines, minBlob*minBlob/4, maxBlob*maxBlob/4, getIntValue(6), false);
    
    float bestCandidateDistance = MAXFLOAT;
    ofPoint centrePoint(val.width/2, val.height/2);
    for (auto foundBlob = contours.blobs.begin(); foundBlob < contours.blobs.end(); ++foundBlob)
    {
        if (foundBlob->nPts > 60 && foundBlob->boundingRect.height < 150 &&
            bestCandidateDistance > foundBlob->centroid.distanceSquared(centrePoint))
        {
            // in case of ambiguous match, pick the one nearest the centre.
            bestCandidateDistance = foundBlob->centroid.distanceSquared(centrePoint);
            dancerBlob = *foundBlob;
        }
    }
    
    if (dancerBlob.nPts)
    {
        dancerArea.set(0);
        CvPoint* points = new CvPoint[dancerBlob.nPts];
        for (int i = 0; i < dancerBlob.nPts; ++i)
        {
            points[i].x = dancerBlob.pts[i].x*2;
            points[i].y = dancerBlob.pts[i].y*2;
        }
        CvPoint* pointSet[1] = {points};
        int numPts[1] = {dancerBlob.nPts};
        cvFillPoly(dancerArea.getCvImage(), pointSet, numPts, 1, cvScalar(255,255,255));
        delete points;
        //dancerArea.erode();
        //dancerArea.blur();
        /*lastKnownGood.x = dancerBlob.boundingRect.x;
        lastKnownGood.y = dancerBlob.boundingRect.y;
        lastKnownGood.width = dancerBlob.boundingRect.width;
        lastKnownGood.height = dancerBlob.boundingRect.height;
        timeout=24;*/
    }
    else
    {
        // if we didn't find a dancer in this area, reset the search area for next time
        lastKnownGood.set(0,0,val.width,val.height);
    }
    
    
    val.resetROI();
    lines.resetROI();
    
    /*ColouredBlobSensor::analyse(input);
    std::vector<ofxCvBlob> shortBlobs;
    for (int i=0; i<contours.blobs.size(); ++i)
    {
        if (contours.blobs[i].boundingRect.height < input->getHeight()/2)
        {
            shortBlobs.push_back(contours.blobs[i]);
        }
    }
    contours.blobs = shortBlobs;
     */
}
std::string DancerBlobSensor::getName() {return NAME;}
