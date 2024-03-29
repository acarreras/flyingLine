#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "animpng/animpng.h"



class ofApp : public ofBaseApp{

    public:
            void setup();
            void update();
            void draw();

	    void keyPressed  (int key);
	    void keyReleased(int key);
	    void mouseMoved(int x, int y );
	    void mouseDragged(int x, int y, int button);
	    void mousePressed(int x, int y, int button);
	    void mouseReleased(int x, int y, int button);
	    void windowResized(int w, int h);


    vector <ofPoint> linep;
    ofPolyline line;
    ofJson js;
    int cont;

    ofShader shader;
    ofImage imagen;
    ofImage imagen_top;
    ofImage imageMask;
    animPng nave_1;
    	
};

#endif
