#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// ��ȡ�����ļ�
	bool bLoad = Font.loadFont("vag.ttf",24);

	// ������Ч��Դ
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
	
	bShowDebug = true;//Ĭ����ʾ������Ϣ
	//��¼Ĭ�ϴ��ڳߴ�
	windowSizeX = ofGetWidth();
	windowSizeY = ofGetHeight();
	X = 100; // Բ�ε�x�����ʼ��Ϊ100
	Y = 50; // Բ�ε�y�����ʼ��Ϊ50
	Size = 50; // Բ�ΰ뾶��ʼ��Ϊ50
	Roundness = 1.0f; // Բ�ȳ�ʼΪ1.0
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

	// ���ñ�����ɫ
	ofBackground(ofColor::white);
	
	// ��ʾԲ��	
	ofPushMatrix();	
	ofTranslate(ofPoint(X,Y)); // ƫ��һ��λ��, ofPoint=ofVec3f=ofVec2f
	ofRotate(Rot,0,0,1);	
	ofScale(Size*Roundness,Size/Roundness,1.0f); // ������������ų߶�	
	ofPushStyle();
	//ofSetColor(ofColor::black); // ��ɫ����ofColor���
	//ofSetCircleResolution(12); // Բ�εķֱ���	
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
	ofTranslate(ofPoint(X,Y)); // ƫ��һ��λ��, ofPoint=ofVec3f=ofVec2f
	ofRotate(Rot,0,0,1);	
	float FontSize = Font.getSize();
	ofScale(Size*Roundness/FontSize,Size*Roundness/FontSize,1.0f);
	ofPushStyle();
	ofSetColor(ofColor::white);
	ofScale(0.5f,1.0f/(Roundness*Roundness),1.0f);
	Font.drawString("^_^",-37,10);
	ofPopStyle();
	ofPopMatrix();

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

	KeyboardState[key] = true; // ��¼����״̬

	ofSoundPlayer& STap = Sounds["tap"];	

	switch (key) // ����key��ȡֵ��ѡ��ִ�е�����
	{
	case '1':// ��keyΪ1����뾶Ϊ25
		Size = 25.0f;
		STap.setVolume(0.2);
		STap.setSpeed(1.5f);
		STap.play();		
		break;
	case '2':// ��keyΪ2����뾶Ϊ50
		Size = 50.0f;
		STap.setVolume(0.4);
		STap.setSpeed(1.0f);
		STap.play();		
		break;
	case '3':// ��keyΪ3����뾶Ϊ75
		Size = 75.0f;
		STap.setVolume(1.0);
		STap.setSpeed(0.5f);
		STap.play();		
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
	KeyboardState[key] = false; // ��¼����״̬
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
