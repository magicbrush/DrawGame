#pragma once

#include "ofMain.h"
#include "CircleSprite.h"

class ofApp : public ofBaseApp{

	public:
		void setup(); // ��ʼ��
		void update(); // ����״̬

    void gameOver();


    void updateEnemies( float dt );
    void randBornEnemy( float dt );
    void eraseEnemy( 
      deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy, 
      string SoundEat );

    void draw();// ����
		void keyPressed(int key);// ����key����
    void keyReleased(int key);// ����key�ͷ�
		void mouseMoved(int x, int y ); // ����ƶ�
		void mouseDragged(int x, int y, int button);// �����ק
		void mousePressed(int x, int y, int button);// ��������
		void mouseReleased(int x, int y, int button);// �����ͷ�
		void windowResized(int w, int h); // ���ڴ�С�ı�
		void dragEvent(ofDragInfo dragInfo); // �϶��ļ�������
		void gotMessage(ofMessage msg); // ���յ�ofSendMessage()����Ϣ

private:
    void playSoundAtVolumeSpeed( 
      ofSoundPlayer& SChgSize,
      float Vol=1.0f, 
      float Spd=1.0f );

public:		
		ofTrueTypeFont Font; // ����
		map<string,ofSoundPlayer> Sounds; // ��Ч

    // ��¼����״̬
    map<int,bool> KeysState;
    map<int,bool> MouseKeyState;
    ofVec2f MousePos;   

		bool bShowDebug; // �Ƿ���ʾ������Ϣ

		int windowSizeX, windowSizeY; //���ڳߴ�
		
		ofPtr<DrawGame::CircleSprite> pPlayer; // ���

    deque<ofPtr<DrawGame::CircleSprite> > Enemies; // ����   
    float EnemyBirthrate; // ���˳�������	
    float EnemyGrowthrate; // ������������
    float WhiteEnemyRatio; // ��ɫ���˵ı���

    bool bGameRunning; // ��Ϸ״̬

   
};
