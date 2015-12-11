//  Created by Fiore Martin and Nuno Correia on 04/12/2015.

#include "ofApp.h"
#include "ofxEnveloper.h"

//create envelope recognition with pixel threshold for H and V lines
ofxEnveloper enveloper(10, 10);

//declare lines and areas
ofPolyline inputLine;
ofPolyline outputLine;
ofRectangle inputArea;
ofRectangle outputArea;

vector<ofPoint> outputCircles;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    //define input and output areas:
    outputArea=ofRectangle(30,30,200,100);
    inputArea=ofRectangle(0,0,ofGetWidth(),ofGetHeight());
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //INPUT
    ofSetColor(255);
    ofSetLineWidth(2);
    //when input line is 0, there is no envelope, just the gesture line
    if(inputLine.size() == 0){
        //draw gesture
        enveloper.drawGesture();
        //draw interpolation
        ofSetColor(0,0,255,127);
        enveloper.drawInterpolation();
    }else{
        inputLine.draw();
    }
    
    //OUTPUT
    ofSetColor(255);
    ofDrawRectangle(outputArea);
    ofSetColor(0);
    outputLine.draw();
    //circles
    ofSetColor(0,0,255,127);
    for (const ofxEnveloperData::Point & p : outputCircles ){
        ofDrawCircle(p.x,p.y,10);
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(button == 0){
        if(x<inputArea.width&&x>inputArea.x&&y<inputArea.height&&y>inputArea.y){
            //add point to envelope recognition
            enveloper.push_back(x, y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //deletes the envelopes
    enveloper.clear();
    inputLine.clear();
    outputLine.clear();
    outputCircles.clear();
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //create an envelope object inputEnv, with the processed gesture data
    ofxEnveloperData inputEnv = enveloper.getEnvelope();
    
    //the if clause is needed to make sure envelope is drawn from left to right
    if(inputEnv.isValid()){

        //loop goes throught the vector of input envelope points
        for (const ofxEnveloperData::Point & p : inputEnv.getPoints() ){
            inputLine.addVertex(p.x, p.y);
        }
        
        //create a output envelope, at first with data from input envelope
        ofxEnveloperData outputEnv = inputEnv;
        
        //scale the output envelope from the input area to the output area
        ofxEnveloperData::scale(outputEnv, inputArea, outputArea);

        //add the points of the scaled envelope to the line
        for (const ofxEnveloperData::Point & p : outputEnv.getPoints() ){
            outputLine.addVertex(p.x, p.y);
            outputCircles.push_back(p);
        }

    }
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    inputArea=ofRectangle(0,0,ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
