#include "ofApp.h"
#include "Shape.h"
#include "GM_Circle.h"

using namespace DrawGame;

//--------------------------------------------------------------
void ofApp::setup(){
  ofPtr<DrawGame::Circle> circleGeom;
  circleGeom.reset(new DrawGame::Circle);
  Geom = circleGeom;

  Geom->setPosition(200,300,0);
  Geom->setScale(100,20,1); 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofMesh* msh = Geom->updateMesh();

  ofPushStyle();
  ofSetColor(255);
  msh->draw();
  ofSetColor(0);
  msh->drawWireframe();
  ofPopStyle();
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
  Geom->setPosition(x,y,0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
