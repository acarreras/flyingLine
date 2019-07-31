#pragma once

#ifndef _ANIMPNG
#define _ANIMPNG

#include "ofMain.h"

class animPng {

public:

    void setup(string folder, float fps, ofLoopType state = OF_LOOP_NONE);
    void update();
    void draw();
    void draw(int x, int y, int w, int h);

    float sequenceFPS;
    ofLoopType loopState;

    void startAnim();
    void stopAnim();
    bool isCompleted(){ return bcompletedAnim; };
    bool isPlaying(){ return bplayAnim; };

    void toggleDrawInfoHelp(){ bdrawInfoHelp = !bdrawInfoHelp; };
    void showDrawInfoHelp(){ bdrawInfoHelp = true; };
    void hideDrawInfoHelp(){ bdrawInfoHelp = false; };

    int getTotalFramesAnim(){ return totalFramesAnim; };

private:
    int totalFramesAnim;
    int frameIndex;
    vector <ofImage> images;

    float initTime;

    bool bplayAnim;
    bool bcompletedAnim;
    bool bfirstLoop;

    bool bdrawInfoHelp;

};

#endif
