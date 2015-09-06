#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "CircleSprite.h"
#include "GUIBase.h"

class ofApp : public ofBaseApp{

public:
  void setup(); // ��ʼ��
  void update(); // ����״̬
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
  void updateEnemies( float dt );
  void randBornEnemy( float dt );
  void eraseEnemy( 
    deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy, 
    string SoundEat );
  void startGame();
  void gameOver();
  void playSoundAtVolumeSpeed( 
    ofSoundPlayer& SChgSize,
    float Vol=1.0f, 
    float Spd=1.0f );
  void saveCanvasImage();

private:	
  ofTrueTypeFont Font; // ����
  map<string,ofSoundPlayer> Sounds; // ��Ч

  // ��¼����״̬
  map<int,bool> KeysState;
  map<int,bool> MouseKeyState;
  ofVec2f MousePos;   

  ofParameter<bool> bShowDebug; // �Ƿ���ʾ������Ϣ
  ofParameter<float> FPS; // ֡��
  int windowSizeX, windowSizeY; //���ڳߴ�
    
  ofPtr<DrawGame::CircleSprite> pPlayer; // ��� 

  deque<ofPtr<DrawGame::CircleSprite> > Enemies; // ����   
  ofParameter<float> EnemyBirthrate; // ���˳�������	
  ofParameter<float> EnemyGrowthrate; // ������������
  ofParameter<float> WhiteEnemyRatio; // ��ɫ���˵ı���

  bool bGameRunning; // ��Ϸ״̬
  string GameOverString; // ��Ϸ������ʾ������
  ofParameter<float> HP,HPMax; // �������������ֵ  

  ofFbo Canvas; // ����

  // ��Ϸ�������
  ofParameter<float> CoinValue;
  ofParameter<float> HPIncSpd;
  ofParameter<float> HPDecSpd;
  ofParameter<float> HPDecJumpA;
  ofParameter<float> HPDecJumpB; 
  ofParameter<float> HPEatAmt;
  ofParameter<float> HPBeatAmt;
  ofParameter<float> HPBeatAmt2;

  // ���Խ���
  ofParameterGroup Params;
  ofxPanel GUI_Debug; // ����GUI
  ofxButton BtnReset; // ���ð�ť
  ofxButton BtnSaveSettings;// Save Settings ��ť
  ofxButton BtnLoadSettings;// Load Settings ��ť  
  ofxButton BtnSaveDrawing; // Save Drawing ��ť
  void saveSettings();
  void loadSettings();

  // ��Ϸ����
  ofPtr<DrawGame::GUIBase> pWidget;  
  void GUICallback(DrawGame::GUIEventArgs &E);
  bool pWidgetOn;
};
