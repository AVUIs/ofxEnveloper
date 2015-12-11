//
//  ofxEnveloper.cpp
//  ofxEnveloper
//
//  Created by Fiore Martin on 04/12/2015.
//
//

#include "ofxEnveloper.h"


ofxEnveloper::ofxEnveloper(float horizotalThreshold, float verticalThreshold):
    mNumSteps(1),
    mHorizThreshold(horizotalThreshold),
    mVertThreshold(verticalThreshold),
    mFirstHorizYCoord(0)
{
    
}



void ofxEnveloper::push_back(float x, float y)
{
    mInterpolator.push_back(msa::Vec2f(x, y));
    
    mNumSteps = floor(sqrt(mInterpolator.size()));
}

int ofxEnveloper::size() const
{
    return mInterpolator.size();
}


void ofxEnveloper::clear()
{
    mInterpolator.clear();
    mNumSteps = 1;
}

void ofxEnveloper::drawGesture()
{
    drawInterpolatorRaw(mInterpolator, 5, 4);
}

void ofxEnveloper::drawInterpolation()
{
    drawInterpolatorSmooth(mInterpolator, mNumSteps, 20,  2) ;
}


ofxEnveloperData ofxEnveloper::getEnvelope()
{
 
    
    if(mInterpolator.size() == 0) {
        return ofxEnveloperData(false); 
    }
    
    float spacing = 1.0/mNumSteps; // good that mNumSteps is never 0, pfiuu!
    
    std::vector<msa::Vec2f> samples;
    samples.reserve(mNumSteps+1);
    
    /* sample the points from the interpolator */
    for(float f=0; f<1; f+= spacing) {
        samples.push_back(mInterpolator.sampleAt(f));
    }
    
    /* add the very last point of the gesture */
    samples.push_back(mInterpolator.at(mInterpolator.size()-1));
    
    /* just press and release is not a valid gesture */
    if(samples.size() <= 2){
        return ofxEnveloperData(false);
    }
    
    ofxEnveloperData envelope(true); // the envelope to return
    vector<ofxEnveloperData::Point> & envelopePoints = envelope.getPoints();
    
    /* push the first sample in the envelope */
    const msa::Vec2f & firstSample = samples[0];
    envelopePoints.push_back(ofxEnveloperData::Point(firstSample.x, firstSample.y));
    mFirstHorizYCoord = firstSample.y;
    
    /* Now scan all the samples and keep track of the previous direction, namely the direction
       of the line that connects the current sample with the previous. If the direction changes
       then pop the sample into the envelope, otherwise carry on and interpolate out all the
       samples in a line straight line. start from third sample because the sample 0 goes in the
       envelope anyway. From sample 1 on, the n-th sample goes into the envelope when the 
       n+1-th sample is examined (namely when the iteration variable i is equal to n)
     */
    
    float diff_x = samples[1].x - samples[0].x;
    
    /* check there is no going backwards in the gesture */
    if( fabs ( diff_x ) < mVertThreshold ){
        /* snap the second point x coord to the first if close enough */
        samples[1].x = samples[0].x;
    }else if(diff_x < 0){
        /* if the gesture goes backwards, return invalid envelope */
        return ofxEnveloperData(false);
    }
    
    Direction prevDir = compare_dir(samples[0].x, samples[0].y, samples[1].x, samples[1].y);
    Direction currentDir;
    
    for(int i=2; i< samples.size(); i++){

        /* check there is no going backwards in the gesture */
        diff_x = samples[i].x - samples[i-1].x;
        
        if( fabs(diff_x) < mVertThreshold ){
            /* snap the second point x coord to the first if close enough */
            samples[i].x = samples[i-1].x;
        }else if( diff_x < 0){
            /* if the gesture goes backwards, return invalid envelope */
            return ofxEnveloperData(false);
        }
        
        currentDir = compare_dir(samples[i-1].x, samples[i-1].y, samples[i].x, samples[i].y );
        
        /* change of direction makes the previous point good for the envelope */
        if(currentDir != prevDir){
            
            if(prevDir == kDirHoriz){
                envelopePoints.push_back( ofxEnveloperData::Point( samples[i-1].x, mFirstHorizYCoord) );
            }else {
                if(currentDir == kDirHoriz){
                    mFirstHorizYCoord = samples[i-1].y;
                }
                envelopePoints.push_back( ofxEnveloperData::Point( samples[i-1].x, samples[i-1].y) );
            }
            
            prevDir = currentDir;
        }

        
    }

    /* finally pop in the envelope the very last sample */
    msa::Vec2f & lastSample = samples[samples.size()-1];
    if(currentDir == kDirHoriz){
        lastSample.y = mFirstHorizYCoord;
    }
    envelopePoints.push_back(ofxEnveloperData::Point(lastSample.x, samples[samples.size()-1].y));


    return envelope;
}

