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
    
    ofTrueTypeFont Font; // ����
    map<string,ofSoundPlayer> Sounds; // ��Ч

    // ��¼����״̬
    map<int,bool> KeysState;
    map<int,bool> MouseKeyState;
    ofVec2f MousePos;

    bool bShowDebug; // �Ƿ���ʾ������Ϣ

    int windowSizeX, windowSizeY; //���ڳߴ�
    
    // ���ǵĲ���
    float X; // Բ�ε�x����
    float Y; // Բ�ε�y����
    float Size; // Բ�εĴ�С		
    float Rot; // ��ת�Ƕȣ��ȣ�

    
        
};
