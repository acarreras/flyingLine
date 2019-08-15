#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetVerticalSync(true);

#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shadersGL3/shader");
    }else{
        shader.load("shadersGL2/shader");
    }
#endif
    
    imagen.load("img.jpg");
    imageMask.load("transparent_sm.png");
    nave_1.setup("nave_1", 5, OF_LOOP_NORMAL);
    nave_1.startAnim();
	  
}


//--------------------------------------------------------------
void ofApp::update(){
    nave_1.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);

    if((linep.size() > 1)&&(cont >0)){
      ofPoint pp = linep.at(cont);
      ofPoint pa = linep.at(cont-1);
      ofPushMatrix();
      ofTranslate(pp.x, pp.y);
      float angle = atan2(pp.y-pa.y, pp.x-pa.x);
      ofRotateRad(angle);
      nave_1.draw(0,0, 300,191);
      ofPopMatrix();

      ofSetColor(255,0,0);
      ofDrawCircle(linep.at(cont).x, linep.at(cont).y,5);
    }

    ofSetColor(0,0,0);
    //ofDrawBitmapString("longi: " + ofToString(linep.size()), 20,20);
    //ofDrawBitmapString("cont: " + ofToString(cont), 20,40);

    for(int i=0; i<linep.size(); i++){
        ofDrawCircle(linep.at(i).x, linep.at(i).y,2);
    }
    for(int i=1; i<linep.size(); i++){
        ofDrawLine(linep.at(i).x, linep.at(i).y, linep.at(i-1).x, linep.at(i-1).y);
    }

    ofSetColor(0,0,255);
    line.draw();
    for(int i=0; i<line.size(); i++){
        ofPoint p = line.getPointAtIndexInterpolated(i);
        ofDrawCircle(p.x, p.y,3);
    }

    ofSetColor(0,0,0);
    ofDrawBitmapString("tecla s to save path", 20,20);
    ofDrawBitmapString("tecla l to load path", 20,40);
    ofDrawBitmapString("mousePressed o mouseDragged to drw points", 20,60);
    ofDrawBitmapString("tecla x to delete point", 20,80);
    ofDrawBitmapString("tecla + to move to next point", 20,100);
    ofDrawBitmapString("tecla - to move to previous point", 20,120);
    ofDrawBitmapString("tecla y to smooth line", 20,160);
    ofDrawBitmapString("tecla u to load smoothed line into animation line", 20,180);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){    
  if (key == 'f'){
      ofToggleFullscreen();
  }
  else if(key == '+'){
      cont ++;
      if(cont >= linep.size()){
        cont = 1;
      }
  }
  else if(key == '-'){
      cont --;
      if(cont < 1){
        cont = linep.size()-1;
      }
  }
  else if(key == 'x'){
      linep.erase(linep.begin()+cont);
      if(cont >= linep.size()){
        cont = 1;
      }
  }
  else if(key == 's'){
      for(int i=0; i<linep.size(); i++){
          ofJson pt;
          pt["x"] = linep.at(i).x;
          pt["y"] = linep.at(i).y;
          js.push_back(pt);
      }
      ofSaveJson("nave.json", js);
  }
  else if(key == 'l'){
      ofFile file("nave.json");
      if(file.exists()){
          file >> js;
          if(!js.empty()){
              linep.clear();
              for(auto & p: js){
                linep.push_back(ofPoint(p["x"], p["y"]));
              }
          }
          cont = 1;
       }
  }
  else if(key == 'y'){
      line.clear();
      for(int i=0; i<linep.size(); i++){
        line.addVertex(linep.at(i).x, linep.at(i).y);
      }
      line = line.getSmoothed(2, 0.5);
      line = line.getSmoothed(2, 0.5);
      line = line.getSmoothed(2, 0.5);
      line = line.getResampledBySpacing(5); // spacing separacio entre punts
  }
  else if(key == 'u'){
      linep.clear();
      for(int i=0; i<line.size(); i++){
          ofPoint p = line.getPointAtIndexInterpolated(i);
          linep.push_back(p);
      }
      line.clear();
  }

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  linep.push_back(ofPoint(x,y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  linep.push_back(ofPoint(x,y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  cont = 1;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}



