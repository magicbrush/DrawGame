#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// 读取字体文件
	bool bLoad = Font.loadFont("vag.ttf",24);

	// 加载音效资源
	ofSoundPlayer P0;
	bool bP0 = P0.loadSound("tap1.mp3");
	P0.setMultiPlay(true);
	P0.setLoop(false);
	Sounds["tap"] = P0;
	ofSoundPlayer P1;
	bool bP1 = P1.loadSound("humorBackground.mp3");
	P1.setLoop(true);
	P1.setVolume(0.3f);
	Sounds["humorBackground"] = P1;	
	P1.play();
	
	bShowDebug = true;//默认显示调试信息
	//记录默认窗口尺寸
	windowSizeX = ofGetWidth();
	windowSizeY = ofGetHeight();
	X = 100; // 圆形的x坐标初始化为100
	Y = 50; // 圆形的y坐标初始化为50
	Size = 50; // 圆形半径初始化为50
	Roundness = 1.0f; // 圆度初始为1.0
	Rot = 0.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	float dt = ofGetLastFrameTime();
	if(KeyboardState['w'])
	{
		Roundness += 0.5f*dt;
	}
	else if(KeyboardState['s'])
	{
		Roundness -= 0.5f*dt;
	}
	else if(KeyboardState['a'])
	{
		Rot -= 360.0f*dt;
	}
	else if(KeyboardState['d'])
	{
		Rot += 360.0f*dt;
	}

	Roundness = ofClamp(Roundness,0.618f,1.0f/0.618f);
	Rot = ofWrapDegrees(Rot);
	
}

//--------------------------------------------------------------
void ofApp::draw(){		

	// 设置背景颜色
	ofBackground(ofColor::white);
	
	// 显示圆形	
	ofPushMatrix();	
	ofTranslate(ofPoint(X,Y)); // 偏移一定位移, ofPoint=ofVec3f=ofVec2f
	ofRotate(Rot,0,0,1);	
	ofScale(Size*Roundness,Size/Roundness,1.0f); // 三个轴向的缩放尺度	
	ofPushStyle();
	//ofSetColor(ofColor::black); // 颜色用类ofColor表达
	//ofSetCircleResolution(12); // 圆形的分辨率	
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
	ofTranslate(ofPoint(X,Y)); // 偏移一定位移, ofPoint=ofVec3f=ofVec2f
	ofRotate(Rot,0,0,1);	
	float FontSize = Font.getSize();
	ofScale(Size*Roundness/FontSize,Size*Roundness/FontSize,1.0f);
	ofPushStyle();
	ofSetColor(ofColor::white);
	ofScale(0.5f,1.0f/(Roundness*Roundness),1.0f);
	Font.drawString("^_^",-37,10);
	ofPopStyle();
	ofPopMatrix();

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

	KeyboardState[key] = true; // 记录按键状态

	ofSoundPlayer& STap = Sounds["tap"];	

	switch (key) // 依据key的取值来选择执行的内容
	{
	case '1':// 若key为1，设半径为25
		Size = 25.0f;
		STap.setVolume(0.2);
		STap.setSpeed(1.5f);
		STap.play();		
		break;
	case '2':// 若key为2，设半径为50
		Size = 50.0f;
		STap.setVolume(0.4);
		STap.setSpeed(1.0f);
		STap.play();		
		break;
	case '3':// 若key为3，设半径为75
		Size = 75.0f;
		STap.setVolume(1.0);
		STap.setSpeed(0.5f);
		STap.play();		
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
	KeyboardState[key] = false; // 记录按键状态
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(0==button)
	{
		moveCircleTo(x, y);		
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(0==button)
	{
		moveCircleTo(x, y);		
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if(0==button)
	{		
		
	}
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
