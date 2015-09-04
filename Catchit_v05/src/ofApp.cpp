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
  ofSoundPlayer P6;
  bool bP6 = P6.loadSound("sounds/error.wav");
  P6.setLoop(false);
  P6.setVolume(1.0f);
  P6.setSpeed(1.0f);
  P6.setMultiPlay(true);
  Sounds["Error"] = P6;
  ofSoundPlayer P7;
  bool bP7 = P7.loadSound("sounds/shrink.mp3");
  P7.setLoop(false);
  P7.setVolume(1.0f);
  P7.setSpeed(1.0f);
  P7.setMultiPlay(true);
  Sounds["Beat"] = P7;
  ofSoundPlayer P8;
  bool bP8 = P8.loadSound("sounds/whip.mp3");
  P8.setLoop(false);
  P8.setVolume(1.0f);
  P8.setSpeed(1.0f);
  P8.setMultiPlay(true);
  Sounds["Beat2"] = P8;
	
  // ��ʼ������״̬
  for(int i=0;i<3;i++)
  {
    MouseKeyState[i] = false;
  } 
  MousePos = ofVec2f(0,0);

	bShowDebug.set("ShowDebugInfo",true);//Ĭ����ʾ������Ϣ
  FPS.set("FPS",0,0,100);

	//��¼Ĭ�ϴ��ڳߴ�
	windowSizeX = ofGetWidth();
	windowSizeY = ofGetHeight();

  // �������
  pPlayer.reset(new DrawGame::CircleSprite(&Font));   

  // ��ʼ�����˲���
  EnemyBirthrate.set("EnemyBirthRate",1.0f,0.2f,5.0f);
  EnemyGrowthrate.set("EnemyGrowthRate",10.0f,0.0f,50.0f);
  WhiteEnemyRatio.set("WhiteEnemyRatio",0.3f,0.0f,1.0f);

  // ��Ϸ״̬
  bGameRunning = true;
  HP.set("HP",100.0f,50.0f,500.0f);
  HPMax.set("HPMax",100.0f,50.0f,500.0f); 

  // ����
  Canvas.allocate(windowSizeX,windowSizeY,GL_RGBA);
  Canvas.begin();
  ofClear(ofColor::white);
  Canvas.end();

  // ��Ϸ�������
  CoinValue.set("CoinValue",20.0f,0.0f,100.0f);
  HPIncSpd.set("HPIncreaseSpeed",3.0f,0.0f,30.0f);
  HPDecSpd.set("HPDecreaseSpeed",1.0f,0.0f,10.0f);
  HPDecJumpA.set("HPDecJumpA",5.0f,0.0f,50.0f);
  HPDecJumpB.set("HPDecJumpB",2.0f,0.0f,20.0f);
  HPEatAmt.set("HPEatAmount",7.0f,0.0f,200.0f);
  HPBeatAmt.set("HPBeatAmount",15.0f,0.0f,500.0f);
  HPBeatAmt2.set("HPBeatAmount",50.0f,0.0f,500.0f);

  // ��ʼ�����Խ���
  Params.setName("Settings");    
  Params.add(EnemyBirthrate);
  Params.add(EnemyGrowthrate);
  Params.add(WhiteEnemyRatio);
  Params.add(HP);
  Params.add(HPMax);
  Params.add(CoinValue);
  Params.add(HPIncSpd);
  Params.add(HPDecSpd);
  Params.add(HPDecJumpA);
  Params.add(HPDecJumpB);
  Params.add(HPEatAmt);
  Params.add(HPBeatAmt);
  Params.add(HPBeatAmt2);
  loadSettings();
  
  BtnReset.setup("Reset Game");
  BtnReset.addListener(this,&ofApp::startGame);
  BtnSaveDrawing.setup("Save Drawing");
  BtnSaveDrawing.addListener(this,&ofApp::saveCanvasImage);
  BtnSaveSettings.setup("Save Settings");
  BtnSaveSettings.addListener(this,&ofApp::saveSettings);
  BtnLoadSettings.setup("Load Settings");  
  BtnLoadSettings.addListener(this,&ofApp::loadSettings);
 
  GUI_Debug.setup("Params");
  GUI_Debug.add(&BtnReset);
  GUI_Debug.add(&BtnSaveDrawing);
  GUI_Debug.add(&BtnSaveSettings);
  GUI_Debug.add(&BtnLoadSettings);
  GUI_Debug.add(bShowDebug);
  GUI_Debug.add(FPS);
  GUI_Debug.add(Params);
  GUI_Debug.setPosition(
    ofGetWidth()-GUI_Debug.getWidth(),0);  

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
        HP += HPEatAmt;
        eraseEnemy(itEnemy, "Eat");
        break;
      }
      if(!pPlayer->isSameColor(*En)&&En->encompass(*pPlayer))
      {
        eraseEnemy(itEnemy,"Coin");  
        HP+= CoinValue;
        break;
      }     
      if(pPlayer->isSameColor(*En)&&En->encompass(*pPlayer))
      {
        HP-=HPBeatAmt; 
        eraseEnemy(itEnemy,"Beat");        
        if(HP<=0.0f)
        {
          GameOverString = "You're Exhausted!";
          gameOver();           
        }   
        break;
      }    
      if(En->getSize()<25.0f&&En->getbWhite())
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

    if(MouseKeyState[0])
    {
      HP+= dt*HPIncSpd;     
    }    
  } 
  HP = ofClamp(HP,0,HPMax);

  // �����Ƿ�סGUI���ж��Ƿ���ʾ���
  bool bPressGUI = GUI_Debug.getShape().inside(
    ofVec2f(ofGetMouseX(),ofGetMouseY()));
  if(bPressGUI&&bShowDebug)
  {
    ofShowCursor();
  }
  else
  {
    ofHideCursor();
  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){		

	// ���ñ�����ɫ
	ofBackground(ofColor(255,255,255));
  
  // ��ʾ����
  Canvas.draw(0,0,ofGetWidth(),ofGetHeight());

  if(bGameRunning)
  {
    // ��ʾ�ʴ�
    ofPushStyle();
    ofSetColor(ofColor::black);
    pPlayer->paint();
    ofPopStyle();

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

  // ��ʾ����
  // ����
  float BarX(1.0f);
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

	// ��ʾ֡��
	if(bShowDebug) // ��bShowDebug�����Ƶ�����Ϣ����ʾ���
	{		
    FPS = ofGetFrameRate();
		ofPushStyle();
		GUI_Debug.draw();
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	KeysState[key] = true; // ��¼����״̬

  if(!MouseKeyState[0]) // δ�϶�ʱ�ſ��Ըı��ɫ��С
  {
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
    }
  }
  else
  {
    if(key=='1'||key=='2'||key=='3')
    {
      playSoundAtVolumeSpeed(Sounds["Error"]);
    }
  }

	switch (key) // ����key��ȡֵ��ѡ��ִ�е�����
	{	
	case OF_KEY_F1: // ��keyΪF1:�л�������Ϣ�Ŀɼ���
		ofSendMessage("ToggleShowDebug");
		break;
  case OF_KEY_F2: // F2: ����ͼƬ
    saveCanvasImage();
    break;
  case OF_KEY_F5: // F5: ������Ϸ
    startGame();

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
  if(!bGameRunning)return;
  MousePos = ofVec2f(x,y);
	if(0==button)
	{
    ofVec2f PosLast = pPlayer->getPosition();
    ofVec2f PosNow = ofVec2f(x,y);
    float dist = PosNow.distance(PosLast);
    float sizePlayer = pPlayer->getSize();
    float DeltaHP = -sizePlayer*dist*0.001f*HPDecSpd;
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
    // �������֮ǰ��λ��
    ofVec2f PosLast = pPlayer->getPosition();
		
    // �ƶ����ǵ���ǰ���λ��
    ofVec2f PosNow = ofVec2f(x,y);
    pPlayer->jumpTo(PosNow);   

    // ��Ծ��HP
    float dist = PosNow.distance(PosLast);
    HP -= HPDecJumpA+dist*0.01f*HPDecJumpB;
        
    // ������Ծ��Ч
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
      if(En->getSize()>100.0f)
      { 
        HP -= HPBeatAmt2;
        if(HP<=0.0f)
        {
          eraseEnemy(itEnemy,"Beat2");
          GameOverString = "You're Eaten!";
          gameOver();
        }                
        break;
      }
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
  map<string,ofSoundPlayer>::iterator it;
  for(it=Sounds.begin();it!=Sounds.end();it++)
  {
    it->second.stop();
  }
  playSoundAtVolumeSpeed(Sounds["Background"]);
  Canvas.begin();
  ofClear(ofFloatColor::white);
  Canvas.end();
}

void ofApp::saveSettings()
{
  ofXml X;
  X.serialize(Params);
  string FilePath("setting/settings.xml");
  bool bSaved = X.save(FilePath);
  if(bSaved)
  {
    cout << "Save settings to: " << FilePath << endl;
  }
  else
  {
    cout << "Fail to save settings!" << endl;
  } 
}

void ofApp::loadSettings()
{
  string FilePath("setting/settings.xml");
  ofXml X;
  bool bLoad = X.load(FilePath);
  if(bLoad)
  {
    X.deserialize(Params);
    cout << "settings loaded from: "<<FilePath << endl;
  }
  else
  {
    cout << "Fail to load settings!" << endl;
  }
}

