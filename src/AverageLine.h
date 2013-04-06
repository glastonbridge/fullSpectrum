//
//  AverageLine.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 20/03/2013.
//
//

#ifndef fullSpectrumAnalyser_AverageLine_h
#define fullSpectrumAnalyser_AverageLine_h

class AverageLine
{
    std::vector<CvPoint> lowend, highend;
    const CvPoint* nearest(const CvPoint& object, const CvPoint& a, const CvPoint& b)
    {
        // calculate the squared distances between object and a and b
        int da = pow(object.x-a.x,2.0) + pow(object.y-a.y,2.0);
        int db = pow(object.x-b.x,2.0) + pow(object.y-b.y,2.0);
        // compare the squared distances (this is pythagoras, but rooting the distances would be pointless in this case
        
        return da < db ? &a : &b;
    }
    
    
    
    // clockwise angle from the y axis
    float angle(const CvPoint& a, const CvPoint& b)
    {
        
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        double hypotenuse = pow(pow(dx,2.0) + pow(dy,2.0),0.5);
        double angle = asin(dx/hypotenuse);
        angle = fmod(angle, PI);
        return angle;
    }
    
    
    void rotatePoint(CvPoint& point, float angle)
    {
        float sinA = sin(angle);
        float cosA = cos(angle);
        float newx, newy;
        newx = point.x * cosA + point.y * sinA;
        newy = - point.x * sinA + point.y * cosA;
        point.x = newx;
        point.y = newy;
    }
    
public:
    AverageLine(const CvPoint& a, const CvPoint& b)
    {
        CvPoint origin;
        if (nearest(origin, a, b) == &a)
        {
            lowend.push_back(a);
            highend.push_back(b);
        }
        else
        {
            lowend.push_back(b);
            highend.push_back(a);
        }
        
    }
    
    CvPoint low()
    {
        CvPoint result;
        result.x=0;
        result.y=0;
        for (int i = 0; i < lowend.size(); ++i)
        {
            result.x += lowend[i].x;
            result.y += lowend[i].y;
        }
        result.x /= lowend.size();
        result.y /= lowend.size();
        return result;
    }
    
    CvPoint high()
    {
        CvPoint result;
        result.x=0;
        result.y=0;
        for (int i = 0; i < highend.size(); ++i)
        {
            result.x += highend[i].x;
            result.y += highend[i].y;
        }
        result.x /= highend.size();
        result.y /= highend.size();
        return result;
    }
    
    bool matches(const CvPoint& unorderedEnd1, const CvPoint& unorderedEnd2)
    {
        CvPoint lowPoint(low());
        CvPoint highPoint(high());
        const CvPoint& end1 = (nearest(lowPoint, unorderedEnd1, unorderedEnd2) == &unorderedEnd1)? unorderedEnd1 : unorderedEnd2;
        const CvPoint& end2 = (&end1 == &unorderedEnd1)? unorderedEnd2 : unorderedEnd1;
        float myAngle(angle(lowPoint, highPoint));
        float matchAngle(angle(end1, end2));
        if (myAngle > matchAngle - MAX_ANGLE_CHANGE && myAngle < matchAngle + MAX_ANGLE_CHANGE)
        {
            myAngle = -myAngle; // this is the angle required to centre around the Y axis
            CvPoint rotatedEnd1(end1);
            rotatePoint(rotatedEnd1, myAngle);
            CvPoint rotatedEnd2(end2);
            rotatePoint(rotatedEnd2, myAngle);
            
            rotatePoint(lowPoint, myAngle);
            rotatePoint(highPoint, myAngle);
            //float x1 = lowPoint.x, x2=highPoint.x;
            // Now, as we have aligned our average line to be parallel with the Y axis, lowPoint.x ~= highPoint.x
            if ((lowPoint.x - MAX_POINT_MOVEMENT < rotatedEnd1.x &&
                 lowPoint.x + MAX_POINT_MOVEMENT > rotatedEnd1.x) &&
                
                (lowPoint.x - MAX_POINT_MOVEMENT < rotatedEnd2.x &&
                 lowPoint.x + MAX_POINT_MOVEMENT > rotatedEnd2.x) &&
                
                (lowPoint.y - MAX_POINT_MOVEMENT < rotatedEnd1.y &&
                 highPoint.y + MAX_POINT_MOVEMENT > rotatedEnd2.y)
                )
            {
                return true;
            }
        }
        return false;
    }
    
    void add(const CvPoint& a, const CvPoint& b)
    {
        CvPoint mylow = low();
        CvPoint myhigh = high();
        if (nearest(a, mylow, myhigh) == &mylow)
        {
            lowend.push_back(a);
        }
        else
        {
            highend.push_back(a);
        }
        
        if (nearest(b, mylow, myhigh) == &mylow)
        {
            lowend.push_back(b);
        }
        else
        {
            highend.push_back(b);
        }
    }
};

#endif
