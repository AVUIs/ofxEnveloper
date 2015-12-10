//
//  ofxEnvRec.h
//  ofxEnvRec
//
//  Created by Fiore Martin on 04/12/2015.
//
//

#ifndef ofxEnvRec_h
#define ofxEnvRec_h


#include <vector>

#include "MSAInterpolator.h"
#include "ofxEnvRecEnvelope.h"


/**
 ofxEnvRec creates smooth linear envelopes out of line-drawing like gesture.
 It performs a linear interpolation of a guesture with sqrt( n ) samples, where n 
 is the number of points of the drawing gesture. Then it cancels all the intermediate points
 of a set of contiguous points going in the same direction.
 
 Note that this class doesn't have any knowledge of the coordinate system. It will just 
 work with the values that you feed it, namely the envelopes that it produces will have the same values
 as the gesture they were generated from.
 If you want to have the envelope values to be different the ones of the gestures, for instance 
 values ranging from 0 to 1, then see the static function scale() to see how to accomplish that.
 
 
 */
class ofxEnvRec {
    
    enum Direction
    {
        kDirUp,
        kDirDown,
        kDirHoriz,
        kDirVert
    };
    
    /* interpolator from http://www.memo.tv/ofxmsainterpolator/ */
    msa::Interpolator2D mInterpolator;
    /* the number of steps of the interpolation */
    int mNumSteps;
    
    float mHorizThreshold;
    float mVertThreshold;
    /* mHorizYCoord keeps track of the first horizontal coordinate encountered when 
       the direction turns to horizontal. This is used to draw a straight line from the first 
       horizontal sample to the last and interpolate out all the samples inthe middle */
    float mFirstHorizYCoord;
    
    inline Direction compare_dir(float x1, float y1, float x2, float y2) const
    {
        
        if( fabs(x1 - x2) < mVertThreshold){
            return kDirVert;
        }else if( fabs(y1 - y2) < mHorizThreshold) {
            return kDirHoriz;
        }
        
        /* comparison is inverted because of how openGL maps the Y coord */
        return (y1 < y2) ? kDirUp : kDirDown;
    }
    
public:
    
    /**
     Creates a new Envelope Recognition class.
     
     horizontalThreshold and verticalThreshold are the the maximum distances respectively on the
     y and x axis, within which an envelope point will be snapped to the same coordinate of the previous point
     during the creation of the envelope(in getEnvelope()).
     
     The bigger the horizontal threshold the more a straight line, going from p1 to p2 with an increasing
     or decreasing slope, will be snapped back to a horizontal line going from (p1.x, p1.y) to (p2.x, p1.y).
     
     The bigger the threshold threshold the more a straight line, going from p1 to p2 with an increasing
     or decreasing slope, will be snapped back to a vertical line going from (p1.x, p1.y) to (p1.x, p2.y).
     
     */
    ofxEnvRec(float horizotalThreshold = 0, float verticalThreshold = 0);
    
    inline void setHorizontalThreshold(float horizontalThreshold)
    {
        mHorizThreshold = horizontalThreshold;
    }
    
    inline float getHorizontalThreshold() const
    {
        return mHorizThreshold;
    }
    
    inline void setVerticalThreshold(float verticalThreshold)
    {
        mVertThreshold = verticalThreshold;
    }
    
    inline float getVerticalThreshold()
    {
        return mVertThreshold;
    }
    
    /**
     pushes a new point in the set of points representing the gesture
     */
    void push_back(float x, float y);
    
    /**
     clears the set of points representing the gesture
     */
    void clear(void);
    
    /**
     returns the size of the set of points representing the gesture
     */
    int size() const;
    
    /* draws the gesture pushed back so far */
    void drawGesture();
    
    /* draws the interpolation the envelope extraction is based upon */
    void drawInterpolation();
    
    /**
     Creates and returns a new envelope based onthe gesture currently pushed in this ofxEnvRec instance
     */
    ofxEnvRecEnvelope getEnvelope();
};


#endif /* ofxEnvRec_h */
