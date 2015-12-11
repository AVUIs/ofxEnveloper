//
//  ofxEnveloperData.cpp
//  ofxEnveloperData
//
//  Created by Fiore Martin on 04/12/2015.
//
//

#include "ofxEnveloperData.h"



std::vector<ofxEnveloperData::Point> & ofxEnveloperData::getPoints()
{
    return mPoints;
};

const std::vector<ofxEnveloperData::Point> & ofxEnveloperData::getPoints() const
{
    return mPoints;
};

void ofxEnveloperData::scale(ofxEnveloperData & envelopeData, const ofRectangle & origin, const ofRectangle & dest)
{
    if(!envelopeData.isValid()){
        throw std::invalid_argument( "Trying to scale an invalid envelope" );
    }
    
    std::vector<Point> & points = envelopeData.getPoints();
    
    bool validEnvelope = true;
    for( Point & p : points){
        
        if(!origin.inside(p)) {
            
            /* if the exception happens after the first point, then the envelope is corrupted
               (contains both scaled and non-scaled points) so it's marked non-valid  */
            if(!validEnvelope){
                envelopeData.mValid = false;
            }
            
            throw std::out_of_range("Envelope data point outisde origin boundaries");
        }
        
        validEnvelope = false;
        /* scale the x coord */
            
        /* get x as a normalized value, ranging from 0 to 1 */
        float norm_x = (p.x - origin.getLeft()) / origin.getWidth();
        /* map the normalized value to the new rect ans assign to the point */
        p.x = dest.getLeft() + (norm_x * dest.getWidth());
        
        
        /* scale the y coord */
        
        /* get y as a normalized value, ranging from 0 to 1 */
        float norm_y = (p.y - origin.getTop()) / origin.getHeight();
        /* map the normalized value to the new rect ans assign to the point */
        p.y = dest.getTop() + (norm_y * dest.getHeight());
    }
}