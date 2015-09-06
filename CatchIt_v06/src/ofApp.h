#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "CircleSprite.h"
#include "GUIBase.h"

class ofApp : public ofBaseApp{

public:
  void setup(); // 初始化
  void update(); // 更新状态
  void draw();// 绘制
  void keyPressed(int key);// 按键key按下
  void keyReleased(int key);// 按键key释放
  void mouseMoved(int x, int y ); // 鼠标移动
  void mouseDragged(int x, int y, int button);// 鼠标拖拽
  void mousePressed(int x, int y, int button);// 鼠标键按下
  void mouseReleased(int x, int y, int button);// 鼠标键释放
  void windowResized(int w, int h); // 窗口大小改变
  void dragEvent(ofDragInfo dragInfo); // 拖动文件到窗口
  void gotMessage(ofMessage msg); // 接收到ofSendMessage()的消息
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
  ofTrueTypeFont Font; // 字体
  map<string,ofSoundPlayer> Sounds; // 音效

  // 记录键鼠状态
  map<int,bool> KeysState;
  map<int,bool> MouseKeyState;
  ofVec2f MousePos;   

  ofParameter<bool> bShowDebug; // 是否显示调试信息
  ofParameter<float> FPS; // 帧率
  int windowSizeX, windowSizeY; //窗口尺寸
    
  ofPtr<DrawGame::CircleSprite> pPlayer; // 玩家 

  deque<ofPtr<DrawGame::CircleSprite> > Enemies; // 敌人   
  ofParameter<float> EnemyBirthrate; // 敌人出生概率	
  ofParameter<float> EnemyGrowthrate; // 敌人生长速率
  ofParameter<float> WhiteEnemyRatio; // 白色敌人的比率

  bool bGameRunning; // 游戏状态
  string GameOverString; // 游戏结束显示的文字
  ofParameter<float> HP,HPMax; // 体力，体力最大值  

  ofFbo Canvas; // 画布

  // 游戏规则参数
  ofParameter<float> CoinValue;
  ofParameter<float> HPIncSpd;
  ofParameter<float> HPDecSpd;
  ofParameter<float> HPDecJumpA;
  ofParameter<float> HPDecJumpB; 
  ofParameter<float> HPEatAmt;
  ofParameter<float> HPBeatAmt;
  ofParameter<float> HPBeatAmt2;

  // 调试界面
  ofParameterGroup Params;
  ofxPanel GUI_Debug; // 调试GUI
  ofxButton BtnReset; // 重置按钮
  ofxButton BtnSaveSettings;// Save Settings 按钮
  ofxButton BtnLoadSettings;// Load Settings 按钮  
  ofxButton BtnSaveDrawing; // Save Drawing 按钮
  void saveSettings();
  void loadSettings();

  // 游戏界面
  ofPtr<DrawGame::GUIBase> pWidget;  
  void GUICallback(DrawGame::GUIEventArgs &E);
  bool pWidgetOn;
};
