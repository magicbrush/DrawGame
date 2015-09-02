#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bShowDebug = true;//默认显示调试信息
	//记录默认窗口尺寸
	windowSizeX = ofGetWidth();
	windowSizeY = ofGetHeight();
	X = 100; // 圆形的x坐标初始化为100
	Y = 50; // 圆形的y坐标初始化为50
	Size = 50; // 圆形半径初始化为50
}

//--------------------------------------------------------------
void ofApp::update(){
	float TimeNow = ofGetElapsedTimef();//获得当前的程序经过的时间（秒）	
}

//--------------------------------------------------------------
void ofApp::draw(){
	// 显示帧率
	if(bShowDebug) // 用bShowDebug来控制调试信息的显示与否
	{
		string FPS = ofToString(ofGetFrameRate());
		ofDrawBitmapString(FPS,5,ofGetHeight()-25);
	}	
	// 显示圆形
	ofCircle(X,Y,Size);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) // 依据key的取值来选择执行的内容
	{
	case '1':// 若key为1，设半径为25
		Size = 25.0f;
		break;
	case '2':// 若key为2，设半径为50
		Size = 50.0f;
		break;
	case '3':// 若key为3，设半径为75
		Size = 75.0f;
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

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(0==button)moveCircleTo(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(0==button)moveCircleTo(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
