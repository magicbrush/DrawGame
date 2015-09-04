#include "ofApp.h"
#include "DrawGameUtils.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60.0f);
  ofHideCursor();

	// ��ȡ�����ļ�
	bool bLoad = Font.loadFont("fonts/vag.ttf",24);

	// ������Ч��Դ
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
	
  // ��ʼ������״̬
  for(int i=0;i<3;i++)
  {
    MouseKeyState[i] = false;
  } 
  MousePos = ofVec2f(0,0);

	bShowDebug = true;//Ĭ����ʾ������Ϣ

	//��¼Ĭ�ϴ��ڳߴ�
	windowSizeX = ofGetWidth();
	windowSizeY = ofGetHeight();

  // �������
  pPlayer.reset(new DrawGame::CircleSprite(&Font));

  // ��ʼ�����˲���
  EnemyBirthrate = 1.0f;
  EnemyGrowthrate = 10.0f;
  WhiteEnemyRatio = 0.3f;

  // ��Ϸ״̬
  bGameRunning = true;
 
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

	// ���ñ�����ɫ
	ofBackground(ofColor(255,255,255));

  //// debug
  //ofPushMatrix();
  //ofTranslate(MousePos);
  ////ofScale(0.5,1.3,1.0f);
  //ofPushStyle();
  //ofSetColor(100);
  //DrawGame::drawScaledStringByFont("Hello",&Font,ofVec2f(0,0),200,40);
  //ofPopStyle();
  //ofPopMatrix();

  if(bGameRunning)
  {
    // ��ʾ����
    deque<ofPtr<DrawGame::CircleSprite> >::iterator itEnemy;  
    for(itEnemy=Enemies.begin();
      itEnemy!=Enemies.end();
      itEnemy++)
    {
      ofPtr<DrawGame::CircleSprite> En = *itEnemy;
      En->draw();
    }

    // ��ʾ���
    pPlayer->draw();
  }  
  else
  {
    ofPushStyle();
    ofSetColor(ofColor::black);
    DrawGame::drawScaledStringByFont(
      "You're Eaten!",
      &Font,
      ofVec2f(ofGetWidth()/2,ofGetHeight()/2),
      200,30);   
    ofPopStyle();
  }

  ofPushMatrix();
  ofPushStyle();
  // ��ʾ���
  if(!MouseKeyState[0]&&
    !MouseKeyState[1]&&
    !MouseKeyState[2])
    // û�а�ס����
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
    // �������
  {
    ofSetColor(ofColor::green);   
    ofFill();
    ofCircle(MousePos,2);   
  }
  ofPopMatrix();
  ofPopStyle();

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

	KeysState[key] = true; // ��¼����״̬

	switch (key) // ����key��ȡֵ��ѡ��ִ�е�����
	{
	case '1':// ��keyΪ1����뾶Ϊ25
		pPlayer->setSize(25.0f);    
    playSoundAtVolumeSpeed(Sounds["ChangeSize"], 0.3f, 1.5f);
		break;
	case '2':// ��keyΪ2����뾶Ϊ50
		pPlayer->setSize(50.0f);		
    playSoundAtVolumeSpeed(Sounds["ChangeSize"], 0.5f, 1.0f);
		break;
	case '3':// ��keyΪ3����뾶Ϊ75
		pPlayer->setSize(75.0f);		
    playSoundAtVolumeSpeed(Sounds["ChangeSize"], 1.0f, 0.5f);
		break;	
	case OF_KEY_F1: // ��keyΪF1:�л�������Ϣ�Ŀɼ���
		ofSendMessage("ToggleShowDebug");
		break;
  case OF_KEY_F5: // F5: ������Ϸ
    Enemies.clear();
    bGameRunning = true;    
    playSoundAtVolumeSpeed(Sounds["Background"]);
    break;
	default:// Ĭ���߼�Ϊ��
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	KeysState[key] = false; // ��¼����״̬
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  MousePos = ofVec2f(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  MousePos = ofVec2f(x,y);
	if(0==button)
	{
		pPlayer->setPosition(ofVec2f(x,y));
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  MouseKeyState[button] = true;
  MousePos = ofVec2f(x,y);
	if(0==button)
	{    
    // �������֮ǰ��λ��
    ofVec2f PosLast = pPlayer->getPosition();
		
    // �ƶ����ǵ���ǰ���λ��
    ofVec2f PosNow = ofVec2f(x,y);
    pPlayer->setPosition(PosNow);   
    
    // ������Ծ��Ч
    float dist = PosNow.distance(PosLast);
    float distNorm = (dist*dist)/(ofGetWidth()*ofGetHeight());
    float SoundSpd = ofMap(distNorm,0.0f,1.0f,1/0.618f,0.618f);
    SoundSpd = ofClamp(SoundSpd,0.5f,2.0f);
    Sounds["Jump"].stop();    
    Sounds["Jump"].setSpeed(SoundSpd);
    Sounds["Jump"].play();

    // �������ǵ�����
     pPlayer->setMood(DrawGame::DRAWGAME_MOOD_ACTIVE);  
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  MouseKeyState[button] = false;
  MousePos = ofVec2f(x,y);
	if(0==button)
	{		
		pPlayer->setMood(DrawGame::DRAWGAME_MOOD_BORING);
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
    E->setPosition(Pos);
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
  pPlayer->setPosition(
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


