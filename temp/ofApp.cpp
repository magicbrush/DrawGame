#include "ofApp.h"
#include "DrawGameUtils.h"

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
  ofSoundPlayer P3;
  bool bP3 = P3.loadSound("sounds/mario_fail.mp3");
  P3.setLoop(false);
  P3.setVolume(1.0f);
  P3.setSpeed(1.0f);
  Sounds["Fail"] = P3;
  ofSoundPlayer P4;
  bool bP4 = P4.loadSound("sounds/mario_stepOnEnemy.mp3");
  P4.setLoop(false);
  P4.setVolume(1.0f);
  P4.setSpeed(1.0f);
  P4.setMultiPlay(true);
  Sounds["Eat"] = P4;
  ofSoundPlayer P5;
  bool bP5 = P5.loadSound("sounds/mario_coin.mp3");
  P5.setLoop(false);
  P5.setVolume(1.0f);
  P5.setSpeed(1.0f);
  P5.setMultiPlay(true);
  Sounds["Coin"] = P5;
  ofSoundPlayer P6;
  bool bP6 = P6.loadSound("sounds/error.wav");
  P6.setLoop(false);
  P6.setVolume(1.0f);
  P6.setSpeed(1.0f);
  P6.setMultiPlay(true);
  Sounds["Error"] = P6;
	
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

  // 构造玩家
  pPlayer.reset(new DrawGame::CircleSprite(&Font));   

  // 初始化敌人参数
  EnemyBirthrate = 1.0f;
  EnemyGrowthrate = 10.0f;
  WhiteEnemyRatio = 0.3f;

  // 游戏状态
  bGameRunning = true;
  HP = 100.0f;
  HPMax = 100.0f; 

  // 画布
  Canvas.allocate(windowSizeX,windowSizeY,GL_RGBA);
  Canvas.begin();
  ofClear(ofColor::white);
  Canvas.end();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	float dt = ofGetLastFrameTime();

  if(bGameRunning)
  {
    randBornEnemy(dt);
    updateEnemies(dt);

    deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy;  
    for(itEnemy=Enemies.begin();
      itEnemy!=Enemies.end();
      itEnemy++)
    {
      ofPtr<DrawGame::CircleSprite> En = *itEnemy;     
      if(pPlayer->isSameColor(*En)&&pPlayer->encompass(*En))
      {       
        eraseEnemy(itEnemy, "Eat");
        break;
      }
      if(!pPlayer->isSameColor(*En)&&En->encompass(*pPlayer))
      {
        eraseEnemy(itEnemy,"Coin");      
        break;
      }     
      if(pPlayer->isSameColor(*En)&&En->encompass(*pPlayer))
      {
        gameOver();
        GameOverString = "You're Eaten!";
        return;
      }    
      if(En->getSize()<5.0f)
      {
        eraseEnemy(itEnemy," ");
        break;
      }
    }

    if(KeysState['a'])
    {
      pPlayer->changeRot(-360.0f*dt);
    }
    else if(KeysState['d'])
    {
      pPlayer->changeRot(360.0f*dt);
    }
  } 
  
}

//--------------------------------------------------------------
void ofApp::draw(){		

	// 设置背景颜色
	ofBackground(ofColor(255,255,255));
  
  // 显示背景
  Canvas.draw(0,0,ofGetWidth(),ofGetHeight());

  if(bGameRunning)
  {
    // 显示笔触
    ofPushStyle();
    ofSetColor(ofColor::black);
    pPlayer->paint();
    ofPopStyle();

    // 显示敌人
    deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy;  
    for(itEnemy=Enemies.begin();
      itEnemy!=Enemies.end();
      itEnemy++)
    {
      ofPtr<DrawGame::CircleSprite> En = *itEnemy;
      En->draw();
    }

    // 显示玩家
    pPlayer->draw();
  }  
  else
  {
    ofPushStyle();
    ofSetColor(ofColor::black);
    float wd,ht;
    ht = Font.stringHeight(GameOverString);
    wd = Font.stringWidth(GameOverString);
    DrawGame::drawScaledStringByFont(
      GameOverString,
      &Font,
      ofVec2f(ofGetWidth()/2,ofGetHeight()/2),
      wd,ht);   
    ofPopStyle();
  }

  ofPushMatrix();
  ofPushStyle();
  // 显示光标
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

  // 显示界面
  // 体力
  float BarX(5.0f);
  float BarY(25.0f);
  float BarHeight(-Font.stringHeight("HP"));
  ofPushMatrix();
  ofPushStyle();
  ofSetColor(ofColor::mediumSeaGreen);
  Font.drawString("HP",BarX,BarY);
  BarX += Font.stringWidth("HP")+4.0f;
  ofSetColor(ofColor::gray);
  ofRect(BarX,BarY,HPMax,BarHeight);
  ofNoFill();
  ofSetColor(ofColor::black);
  ofRect(BarX,BarY,HPMax,BarHeight);
  ofFill();
  ofSetColor(ofColor::green);
  if(HP<HPMax*0.2f)
  {
    ofSetColor(ofColor::red);
  }  
  ofRect(BarX,BarY,HP,BarHeight);
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

	KeysState[key] = true; // 记录按键状态

  if(!MouseKeyState[0]) // 未拖动时才可以改变角色大小
  {
    switch (key) // 依据key的取值来选择执行的内容
    {
    case '1':// 若key为1，设半径为25
      pPlayer->setSize(25.0f);    
      playSoundAtVolumeSpeed(Sounds["ChangeSize"], 0.3f, 1.5f);
      break;
    case '2':// 若key为2，设半径为50
      pPlayer->setSize(50.0f);		
      playSoundAtVolumeSpeed(Sounds["ChangeSize"], 0.5f, 1.0f);
      break;
    case '3':// 若key为3，设半径为75
      pPlayer->setSize(75.0f);		
      playSoundAtVolumeSpeed(Sounds["ChangeSize"], 1.0f, 0.5f);
      break;	
    }
  }
  else
  {
    if(key=='1'||key=='2'||key=='3')
    {
      playSoundAtVolumeSpeed(Sounds["Error"]);
    }
  }

	switch (key) // 依据key的取值来选择执行的内容
	{	
	case OF_KEY_F1: // 若key为F1:切换调试信息的可见性
		ofSendMessage("ToggleShowDebug");
		break;
  case OF_KEY_F2: // F2: 保存图片
    saveCanvasImage();
    break;
  case OF_KEY_F5: // F5: 启动游戏
    startGame();

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
  if(!bGameRunning)return;
  MousePos = ofVec2f(x,y);
	if(0==button)
	{
    ofVec2f PosLast = pPlayer->getPosition();
    ofVec2f PosNow = ofVec2f(x,y);
    float dist = PosNow.distance(PosLast);
    float sizePlayer = pPlayer->getSize();
    float DeltaHP = -sizePlayer*dist*0.001f;
    HP += DeltaHP;
    if(HP<=0.0f)
    {
      GameOverString = "You're Exausted!";
      gameOver();
    }

		pPlayer->moveTo(PosNow);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  if(!bGameRunning)return;
  MouseKeyState[button] = true;
  MousePos = ofVec2f(x,y);
	if(0==button)
	{    
    // 获得主角之前的位置
    ofVec2f PosLast = pPlayer->getPosition();
		
    // 移动主角到当前鼠标位置
    ofVec2f PosNow = ofVec2f(x,y);
    pPlayer->jumpTo(PosNow);   
    
    // 播放跳跃声效
    float dist = PosNow.distance(PosLast);
    float distNorm = (dist*dist)/(ofGetWidth()*ofGetHeight());
    float SoundSpd = ofMap(distNorm,0.0f,1.0f,1/0.618f,0.618f);
    SoundSpd = ofClamp(SoundSpd,0.5f,2.0f);
    Sounds["Jump"].stop();    
    Sounds["Jump"].setSpeed(SoundSpd);
    Sounds["Jump"].play();

    // 设置主角的情绪
     pPlayer->setMood(DrawGame::DRAWGAME_MOOD_ACTIVE);  
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  if(!bGameRunning)return;
  MouseKeyState[button] = false;
  MousePos = ofVec2f(x,y);
	if(0==button)
	{		
		pPlayer->setMood(DrawGame::DRAWGAME_MOOD_BORING);
    
    Canvas.begin();
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(ofColor::black);
    pPlayer->paint();
    ofPopStyle();
    ofPopMatrix();
    Canvas.end();
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

void ofApp::randBornEnemy( float dt )
{
  float randThres =dt*EnemyBirthrate;
  float randNum = ofRandom(0,1);
  if(randNum<randThres)
  {
    ofPtr<DrawGame::CircleSprite> E;
    E.reset(new DrawGame::CircleSprite(&Font));
    ofVec2f Pos(
      ofRandom(0,ofGetWidth()),
      ofRandom(0,ofGetHeight()));
    float randNum2 = ofRandom(0,1);
    if(randNum2>WhiteEnemyRatio)
    {
      E->setSize(ofRandom(5,10));
      E->setMood(DrawGame::DRAWGAME_MOOD_EVIL);          
    }
    else
    {
      E->setSize(ofRandom(60,80));
      E->setMood(DrawGame::DRAWGAME_MOOD_JOY);
      E->setWhite(true);
    }
    E->jumpTo(Pos);
    E->setRot(ofRandom(-180,180));
    Enemies.push_back(E);   
  }
}

void ofApp::updateEnemies( float dt )
{
  deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy;  
  for(itEnemy=Enemies.begin();
    itEnemy!=Enemies.end();
    itEnemy++)
  {
    ofPtr<DrawGame::CircleSprite> En = *itEnemy;
    bool bWhite = En->getbWhite();
    if(!bWhite)
    {
      En->changeSize(dt*EnemyGrowthrate);
      En->changeRot(dt*90.0f);
    }
    else
    {
      En->changeSize(-dt*EnemyGrowthrate);
      En->changeRot(-dt*90.0f);
    }    
  }
}

void ofApp::eraseEnemy( 
  deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy, 
  string SoundEat )
{
  Enemies.erase(itEnemy);
  if(Sounds.find(SoundEat)!=Sounds.end())
  {
    Sounds[SoundEat].play();
  }  
}

void ofApp::gameOver()
{
  bGameRunning = false;
  Enemies.clear();
  pPlayer->jumpTo(
    ofVec2f(ofGetWidth()/2,ofGetHeight()/2));
  Sounds["Fail"].play();
  Sounds["Background"].stop();
 
}

void ofApp::playSoundAtVolumeSpeed( 
  ofSoundPlayer& SChgSize, 
  float Vol, 
  float Spd )
{
  SChgSize.setVolume(Vol);
  SChgSize.setSpeed(Spd);
  SChgSize.play();
}

void ofApp::saveCanvasImage()
{
  ofImage I;
  Canvas.begin();
  I.grabScreen(0,0,Canvas.getWidth(),Canvas.getHeight());
  Canvas.end();
  I.mirror(true,false);
  string FileName = "myPainting/Work"+ofGetTimestampString()+".jpg";
  I.saveImage(FileName);
  cout << "Artwork Saved:" << FileName << endl;
}

void ofApp::startGame()
{
  HP = HPMax;
  Enemies.clear();
  bGameRunning = true;    
  playSoundAtVolumeSpeed(Sounds["Background"]);
  Canvas.begin();
  ofClear(ofFloatColor::white);
  Canvas.end();
}




