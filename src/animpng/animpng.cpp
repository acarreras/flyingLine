#include "animpng.h"

//--------------------------------------------------------------
void animPng::setup(string folder, float fps, ofLoopType state) {
    bplayAnim = false;
    bcompletedAnim = false;
    bfirstLoop = true;
    bdrawInfoHelp = false;

    ofDirectory dir;
    totalFramesAnim = dir.listDir(folder);
    dir.sort();
    if(totalFramesAnim){
        for(int i=0; i<totalFramesAnim; i++) {
            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().load(filePath);
        }
    }
    else{
        ofLogError() << "ERROR::animPng:: could not find folder " << folder << " or is empty" << endl;
    }
    sequenceFPS = fps;
    frameIndex = 0;
    loopState = state;
}

//--------------------------------------------------------------
void animPng::startAnim(){
    bplayAnim = true;
    bcompletedAnim = false;
    bfirstLoop = true;
    frameIndex = 0;
    initTime = ofGetElapsedTimef();
}
//--------------------------------------------------------------
void animPng::stopAnim(){
    bplayAnim = false;
    bcompletedAnim = true;
}

//--------------------------------------------------------------
void animPng::update(){
    if(bplayAnim){
        frameIndex = (int)((ofGetElapsedTimef()-initTime)*sequenceFPS)%totalFramesAnim;
        if( (frameIndex == totalFramesAnim-1)&&(bfirstLoop) ){
            bfirstLoop = false;
        }
        if( (loopState == OF_LOOP_NONE)&&(frameIndex == 0)&&(!bfirstLoop) ){
            stopAnim();
        }
    }
}

//--------------------------------------------------------------
void animPng::draw() {
    ofSetColor(255);
    images[frameIndex].draw(0,0);
}

//--------------------------------------------------------------
void animPng::draw(int x, int y, int w, int h){
    ofSetColor(255);
    images[frameIndex].draw(x,y,w,h);
    if(bdrawInfoHelp){
        ofDrawBitmapString(ofToString(frameIndex) + "/" + ofToString(totalFramesAnim) + "\nat " + ofToString(sequenceFPS) + "fps", x+60,y+80);
    }
}
