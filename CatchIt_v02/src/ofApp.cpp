#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60.0f);
  ofHideCursor();

  // 读取字体文件
  bool bLoad = Font.loadFont("fonts/vag.ttf",24);

  // 加载音效资源
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

  // 初始化键鼠状态
  for(int i=0;i<3;i++)
  {
     MouseKeyState[i] = false;
  } 
  MousePos = ofVec2f(0,0);
  
  bShowDebug = true;//默认显示调试信息
  //记录默认窗口尺寸
  windowSizeX = ofGetWidth();
  windowSizeY = ofGetHeight();
  X = 100; // 圆形的x坐标初始化为100
  Y = 50; // 圆形的y坐标初始化为50
  Size = 50; // 圆形半径初始化为50	
  Rot = 0.0f; // 旋转角度初始化为0
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

  // 设置背景颜色
  ofBackground(ofColor::white);
  
  // 显示圆形	
  ofPushMatrix();	
  ofTranslate(ofPoint(X,Y)); // 偏移一定位移,ofPoint=ofVec3f=ofVec2f
  ofRotate(Rot,0,0,1);	
  ofScale(Size,Size,1.0f); // 三个轴向的缩放尺度	
  ofPushStyle();	
  ofStyle S = ofGetStyle(); // 详见附录ofStyle
  S.bFill = true;	
  S.circleResolution = 36;
  S.color = ofColor::black;
  ofSetStyle(S);
  ofCircle(0,0,1.0f);
  ofPopStyle();
  ofPopMatrix();

  // 显示表情
  ofPushMatrix();
  ofTranslate(ofPoint(X,Y)); // 偏移一定位移,ofPoint=ofVec3f=ofVec2f
  ofRotate(Rot,0,0,1);	
  float FontSize = Font.getSize();
  ofScale(Size/FontSize,Size/FontSize,1.0f);
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofScale(0.5f,1.0f,1.0f);
  Font.drawString("^_^",-37,10);
  ofPopStyle();
  ofPopMatrix();

  // 显示光标
  ofPushMatrix();
  ofPushStyle();  
  if(!MouseKeyState[0]&&
    !MouseKeyState[1]&&
    !MouseKeyState[2])
  // 没有按住鼠标键
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
  // 按下左键
  {
    ofSetColor(ofColor::green);   
    ofFill();
    ofCircle(MousePos,2);   
  }
  ofPopMatrix();
  ofPopStyle();
  
  // 显示帧率
  if(bShowDebug) // 用bShowDebug来控制调试信息的显示与否
  {		
    ofPushStyle();
    ofSetColor(ofColor::black); // 用黑色显示调试信息
    string FPS = "FPS:" +ofToString(ofGetFrameRate());
    ofDrawBitmapString( FPS,5,ofGetHeight()-25);		
    ofPopStyle();
  }	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  
  KeysState[key] = true; // 记录按键状态

  ofSoundPlayer& SChgSize = Sounds["ChangeSize"];	

  switch (key) // 依据key的取值来选择执行的内容
  {
  case '1':// 若key为1，设半径为25
    Size = 25.0f;
    SChgSize.setVolume(0.2);
    SChgSize.setSpeed(1.5f);
    SChgSize.play();		
    break;
  case '2':// 若key为2，设半径为50
    Size = 50.0f;
    SChgSize.setVolume(0.4);
    SChgSize.setSpeed(1.0f);
    SChgSize.play();		
    break;
  case '3':// 若key为3，设半径为75
    Size = 75.0f;
    SChgSize.setVolume(1.0);
    SChgSize.setSpeed(0.5f);
    SChgSize.play();		
    break;	
  case OF_KEY_F1: // 若key为F1:切换调试信息的可见性
    ofSendMessage("ToggleShowDebug");
    break;
  default:// 默认逻辑为空
    break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  KeysState[key] = false; // 记录按键状态
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
  // 若接收到消息"ToggleShowDebug"，则切换bShowDebug状态
  {
    bShowDebug = !bShowDebug;
  }	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::moveCircleTo( int x, int y )
{
  // 将鼠标位置赋值给圆心位置
  X = x;
  Y = y;
}
