#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup(); // ��ʼ��
		void update(); // ����״̬
		void draw();// ����

		void keyPressed(int key);// ����key����
		void keyReleased(int key);// ����key�ͷ�
		void mouseMoved(int x, int y ); // ����ƶ�
		void mouseDragged(int x, int y, int button);// �����ק
		void moveCircleTo( int x, int y );
		void mousePressed(int x, int y, int button);// ��������
		void mouseReleased(int x, int y, int button);// �����ͷ�
		void windowResized(int w, int h); // ���ڴ�С�ı�
		void dragEvent(ofDragInfo dragInfo); // �϶��ļ�������
		void gotMessage(ofMessage msg); // ���յ�ofSendMessage()����Ϣ

		bool bShowDebug;
		int windowSizeX, windowSizeY; //���ڳߴ�
		float X; // Բ�ε�x������ھ�����ʱ��
		float Y; // Բ�ε�y����0.8�����ھ�����ʱ��
		float Size; // Բ�εİ뾶��ʱ�䰴���ҹ������ڱ仯
				
};
