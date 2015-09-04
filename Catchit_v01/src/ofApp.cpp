#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bShowDebug = true;//Ĭ����ʾ������Ϣ
	//��¼Ĭ�ϴ��ڳߴ�
	windowSizeX = ofGetWidth();
	windowSizeY = ofGetHeight();
	X = 100; // Բ�ε�x�����ʼ��Ϊ100
	Y = 50; // Բ�ε�y�����ʼ��Ϊ50
	Size = 50; // Բ�ΰ뾶��ʼ��Ϊ50
}

//--------------------------------------------------------------
void ofApp::update(){
	float TimeNow = ofGetElapsedTimef();//��õ�ǰ�ĳ��򾭹���ʱ�䣨�룩	
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ��ʾ֡��
	if(bShowDebug) // ��bShowDebug�����Ƶ�����Ϣ����ʾ���
	{
		string FPS = ofToString(ofGetFrameRate());
		ofDrawBitmapString(FPS,5,ofGetHeight()-25);
	}	
	// ��ʾԲ��
	ofCircle(X,Y,Size);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) // ����key��ȡֵ��ѡ��ִ�е�����
	{
	case '1':// ��keyΪ1����뾶Ϊ25
		Size = 25.0f;
		break;
	case '2':// ��keyΪ2����뾶Ϊ50
		Size = 50.0f;
		break;
	case '3':// ��keyΪ3����뾶Ϊ75
		Size = 75.0f;
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
