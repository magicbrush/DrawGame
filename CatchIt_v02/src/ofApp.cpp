#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60.0f);
  ofHideCursor();

  // ��ȡ�����ļ�
  bool bLoad = Font.loadFont("fonts/vag.ttf",24);

  // ������Ч��Դ
  ofSoundPlayer P0;
  bool bP0 = P0.loadSound("sounds/tap1.mp3");
  P0.setMultiPlay(true);
  P0.setLoop(false);
  Sounds["ChangeSize"] = P0;
  ofSoundPlayer P1;
  bool bP1 = P1.loadSound("sounds/mario_mainTheme.mp3");
  P1.setLoop(true);
  P1.setVolume(0.3f);
  Sounds["Background"] = P1;	
  P1.play();
  ofSoundPlayer P2;
  bool bP2 = P2.loadSound("sounds/mario_jump.mp3");
  P2.setLoop(false);
  P2.setVolume(1.0f);
  P2.setSpeed(1.25f);
  Sounds["Jump"] = P2;

  // ��ʼ������״̬
  for(int i=0;i<3;i++)
  {
     MouseKeyState[i] = false;
  } 
  MousePos = ofVec2f(0,0);
  
  bShowDebug = true;//Ĭ����ʾ������Ϣ
  //��¼Ĭ�ϴ��ڳߴ�
  windowSizeX = ofGetWidth();
  windowSizeY = ofGetHeight();
  X = 100; // Բ�ε�x�����ʼ��Ϊ100
  Y = 50; // Բ�ε�y�����ʼ��Ϊ50
  Size = 50; // Բ�ΰ뾶��ʼ��Ϊ50	
  Rot = 0.0f; // ��ת�Ƕȳ�ʼ��Ϊ0
}

//--------------------------------------------------------------
void ofApp::update(){  
  float dt = ofGetLastFrameTime();
  if(KeysState['a'])
  {
    Rot -= 360.0f*dt;
  }
  else if(KeysState['d'])
  {
    Rot += 360.0f*dt;
  }  
  Rot = ofWrapDegrees(Rot);  
}

//--------------------------------------------------------------
void ofApp::draw(){		

  // ���ñ�����ɫ
  ofBackground(ofColor::white);
  
  // ��ʾԲ��	
  ofPushMatrix();	
  ofTranslate(ofPoint(X,Y)); // ƫ��һ��λ��,ofPoint=ofVec3f=ofVec2f
  ofRotate(Rot,0,0,1);	
  ofScale(Size,Size,1.0f); // ������������ų߶�	
  ofPushStyle();	
  ofStyle S = ofGetStyle(); // �����¼ofStyle
  S.bFill = true;	
  S.circleResolution = 36;
  S.color = ofColor::black;
  ofSetStyle(S);
  ofCircle(0,0,1.0f);
  ofPopStyle();
  ofPopMatrix();

  // ��ʾ����
  ofPushMatrix();
  ofTranslate(ofPoint(X,Y)); // ƫ��һ��λ��,ofPoint=ofVec3f=ofVec2f
  ofRotate(Rot,0,0,1);	
  float FontSize = Font.getSize();
  ofScale(Size/FontSize,Size/FontSize,1.0f);
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofScale(0.5f,1.0f,1.0f);
  Font.drawString("^_^",-37,10);
  ofPopStyle();
  ofPopMatrix();

  // ��ʾ���
  ofPushMatrix();
  ofPushStyle();  
  if(!MouseKeyState[0]&&
    !MouseKeyState[1]&&
    !MouseKeyState[2])
  // û�а�ס����
  {
    ofSetColor(ofColor::white);
    ofSetLineWidth(1.0f);
    ofNoFill();
    ofCircle(MousePos,15); 
    ofSetColor(ofColor::black);
    ofCircle(MousePos,16); 
  }
  else if(
    MouseKeyState[0]&&
    !MouseKeyState[1]&&
    !MouseKeyState[2])
  // �������
  {
    ofSetColor(ofColor::green);   
    ofFill();
    ofCircle(MousePos,2);   
  }
  ofPopMatrix();
  ofPopStyle();
  
  // ��ʾ֡��
  if(bShowDebug) // ��bShowDebug�����Ƶ�����Ϣ����ʾ���
  {		
    ofPushStyle();
    ofSetColor(ofColor::black); // �ú�ɫ��ʾ������Ϣ
    string FPS = "FPS:" +ofToString(ofGetFrameRate());
    ofDrawBitmapString( FPS,5,ofGetHeight()-25);		
    ofPopStyle();
  }	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  
  KeysState[key] = true; // ��¼����״̬

  ofSoundPlayer& SChgSize = Sounds["ChangeSize"];	

  switch (key) // ����key��ȡֵ��ѡ��ִ�е�����
  {
  case '1':// ��keyΪ1����뾶Ϊ25
    Size = 25.0f;
    SChgSize.setVolume(0.2);
    SChgSize.setSpeed(1.5f);
    SChgSize.play();		
    break;
  case '2':// ��keyΪ2����뾶Ϊ50
    Size = 50.0f;
    SChgSize.setVolume(0.4);
    SChgSize.setSpeed(1.0f);
    SChgSize.play();		
    break;
  case '3':// ��keyΪ3����뾶Ϊ75
    Size = 75.0f;
    SChgSize.setVolume(1.0);
    SChgSize.setSpeed(0.5f);
    SChgSize.play();		
    break;	
  case OF_KEY_F1: // ��keyΪF1:�л�������Ϣ�Ŀɼ���
    ofSendMessage("ToggleShowDebug");
    break;
  default:// Ĭ���߼�Ϊ��
    break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  KeysState[key] = false; // ��¼����״̬
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  MousePos = ofVec2f(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  MousePos = ofVec2f(x,y);
  if(0==button)
  {
    moveCircleTo(x, y);		
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  MouseKeyState[button] = true;
  MousePos = ofVec2f(x,y);
  if(0==button)
  {
    moveCircleTo(x, y);		
    Sounds["Jump"].stop();    
    Sounds["Jump"].play();
  }  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  MouseKeyState[button] = false;
  MousePos = ofVec2f(x,y);
 
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  ofSetWindowShape(windowSizeX,windowSizeY);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
  if("ToggleShowDebug" == msg.message)
  // �����յ���Ϣ"ToggleShowDebug"�����л�bShowDebug״̬
  {
    bShowDebug = !bShowDebug;
  }	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::moveCircleTo( int x, int y )
{
  // �����λ�ø�ֵ��Բ��λ��
  X = x;
  Y = y;
}
