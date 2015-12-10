//
//  ofxEnvRecEnvelope.h
//  ofxEnvRecEnvelope
//
//  Created by Fiore Martin on 04/12/2015.
//
//

#ifndef ofxEnvRecEnvelope_h
#define ofxEnvRecEnvelope_h

#include <vector>

#include "ofMain.h"


/**
 an envelope returned by ofxEnvRec. 
 
 The envelope is represented as set of points ordered by their x coordinate.
 A valid envelope - isValid() returns true - only goes from left to right.
 
 The envelope can be drawn from the set of points by connecting with a line each 
 point of the vector returned by getPoints() with the previous one and the next one.
 
 */
class ofxEnvRecEnvelope {
    
    
public:
    
    
    ofxEnvRecEnvelope(bool valid = true)
    {
        mValid = valid;
    }
    
    /* whether an envelope is valid, For iunstance an invalid envelope is returned by ofxEnvRec
       to flag that a valid envelope cannot be instantiated from the gesture 
     */
    bool isValid() const
    {
        return mValid;
    }
    
    /*
     struct Point
     {
     Point(float _x, float _y);
     float x;
     float y;
     };
    */
    
    /**
     in openframeworks Point is defined as ofVec2f 
     */
    typedef ofVec2f Point;
    
    
    /**
     returns a reference to the internal vector of points
     */
    std::vector<Point> & getPoints();
    
    /**
     returns a const reference to the internal vector of points
     */
    const std::vector<Point> & getPoints() const;
    
    /**
     scales the points of the envelope passed as argument, note that this modifies
     the envelope passed as argument. So make a copy first if you need to keep the old values as well.
     
     arguments are 
     
     envelope: the envelope to scale, it gets modified by this function
     origin: the rectange where the envelope was generated
     dest: the new rectangle the envelope will be fit into
     
     throws the following exceptions: 
     - std::invalid_argument: if the envelope passed is not valid (isValid() returns false)
     - std::out_of_range : if the points of the envelope passed as argument are not all contained 
       in the origin rectangle. Note that if this exception happens, then the envelope might containt 
       both scaled and non-scaled points; in that case it will be marked as invalid. If you need to restore
       the original state of the envelope then make a copy before calling this method.
     */
    static void scale(ofxEnvRecEnvelope & envelope, const ofRectangle & origin, const ofRectangle & dest);
    
        
    
    
private:
    
    bool mValid;
    
    std::vector<Point> mPoints;
    
};


#endif /* ofxEnvRecEnvelope_h */
