#include "ofApp.h"
#include "Sprite.h"
#include "Status.h"
#include "khGetInSameCrCircle.h"
#include "khEncompassInvCrCircle.h"
#include "khLuaScript.h"
#include "Brush.h"
#include "Body.h"
#include "BrSplash.h"
#include "DrawGameUtils.h"
#include "SoundEngine.h"
#include "SingletonTemplate.h"
#include "DrawGameGUI.h"
#include "ofxAssets.h"
#include "Informer.h"
#include "TextNode.h"
#include "DrawGameDefs.h"

using namespace DrawGame;

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60.0f);
  ofSetVerticalSync(true);

  WindowSize.x = ofGetWidth();
  WindowSize.y = ofGetHeight();

  bGameRunning = true;
  
  sp.reset(new 
    DrawGame::Sprite());
  sp->setSize(50);

  spStatus.reset(new DrawGame::Status());
  sp->linkStatus(spStatus);
  ofPtr<DrawGame::Brush> Br;
  Br.reset(new DrawGame::Brush);
  Br->linkCanvas(&CanvasFbo);
  sp->linkBrush(Br);
  ofPtr<DrawGame::Brush> BrE;
  BrE.reset(new DrawGame::BrSplash);
  BrE->linkCanvas(&EffectsFbo);
  sp->linkEffectBr(BrE);
  sp->getBody()->setImageTextureFile("Hero");

  CanvasFbo.allocate(ofGetWidth(),ofGetHeight(),GL_RGB);
  CanvasFbo.begin();
  ofClear(255);
  CanvasFbo.end();
  EffectsFbo.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA32F);
  EffectsFbo.begin();
  ofClear(0,0,0,0);
  EffectsFbo.end();
   
  bShowDebug = true;
  GUI_Debug.setup("DrawGameGUI");  
  GUI_Debug.minimizeAll();  
  GUI_Debug.add(FPS.set("FPS",ofGetFrameRate(),0,100));  
  GUI_Debug.add(sp->getParameterGroup());
  GUI_Debug.add(Br->getParameterGroup());
  GUI_Debug.setPosition(ofGetWidth()-GUI_Debug.getWidth(),0);

  // 游戏界面初始化
  ofVec2f Ctr(ofGetWidth()/2,ofGetHeight()/2);
  Ctr += ofVec2f(0,ofGetWidth()/6); 
  pRetryBtn.reset(new DrawGame::GUITextButton(
    "GUI_Retry",
    "Retry",
    120,40,
    &ofxAssets::font("vag",30),
    Ctr));
 
  ofAddListener(
    pRetryBtn->GUIEvent,this,
    &ofApp::retryButtonCallback);
  pRetryBtn->setScale(1.5f);
  pRetryBtn->setVisible(false);
  pRetryBtn->setActive(false);

  ofPtr<DrawGame::GUIDataSlot> pHB;
  ofRectangle R(5,5,ofGetWidth()-10,30);
  string Tag2("GUI_HP"),Title2("HP");
  pHB.reset(new DrawGame::GUIDataSlot(
    spStatus->HP,
    spStatus->HPMax,
    Tag2,
    Title2,
    R,
    0.1f,
    &ofxAssets::font("vag",30),
    1000,
    2.0f));   

  GUIs.push_back(pRetryBtn);
  GUIs.push_back(pHB);

  SOUNDENGINE.playSound("BackgroundMusic");
}

//--------------------------------------------------------------
void ofApp::update(){
  float dt = ofGetLastFrameTime();
  //cout << "dt:" << dt << endl;
  
  if(bGameRunning)
  {
    randGenSprite(dt>0.01f?dt:0.01f);

    if(Sprites.size()>0)
    {
      for(auto it:Sprites)it->update();    
      vector<ofPtr<DrawGame::Sprite> >::iterator it;
      for(it = Sprites.begin();it<Sprites.end();it++)
      {
        if(!(*it)->isAlive())
        {
          Sprites.erase(it);
          if(Sprites.size()>0){it=Sprites.begin();}
          else{break;}
        }
      }
    }
    sp->update();
    sp->drawEffect();

    if(Keyboard[OF_KEY_UP])sp->changeSize(dt*100.0f);
    if(Keyboard[OF_KEY_DOWN])sp->changeSize(-dt*100.0f);
    if(Keyboard[OF_KEY_LEFT])sp->changeRot(-dt*360.0f);
    if(Keyboard[OF_KEY_RIGHT])sp->changeRot(dt*360.0f);

    if(spStatus->HP<=0)
    {
      bGameRunning = false;
      pRetryBtn->setVisible(true);
      pRetryBtn->setActive(true);
      SOUNDENGINE.stopSound("BackgroundMusic");
      SOUNDENGINE.playSound("Fail");
      Sprites.clear();    
    }
  }  

  EffectsFbo.begin();
  ofPushStyle();
  ofFloatColor C(0,0,0,dt*2.0f);
  ofSetColor(C);
  ofRect(0,0,ofGetWidth(),ofGetHeight());
  ofPopStyle();
  EffectsFbo.end();

  for(auto widget:GUIs)widget->update();

  INFORMER.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  CanvasFbo.draw(0,0,ofGetWidth(),ofGetHeight());
  EffectsFbo.draw(0,0,ofGetWidth(),ofGetHeight());
  if(bGameRunning)
  {
    for(auto it:Sprites)it->draw();
    sp->draw();
  }
  else
  {
    drawGameOver();
  }  
  for(auto widget:GUIs)widget->draw();

  if(bShowDebug)
  {
    FPS = ofGetFrameRate();
    GUI_Debug.draw();

    stringstream ss;
    ss << "F1: clear canvas" << endl;
    ss << "F2: reload Keyhole Lua Scripts" <<endl;
    ss << "F3: show/hide debug info" <<endl;
    ss << "F4: clear all sprites" << endl;
    ss << "F5: random create sprites "<< endl;
    ss << "up/down: +/- hero size" << endl;
    ss << "left/right: rotate left/right" << endl;
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofDrawBitmapString(ss.str(),6,20);
    ofDrawBitmapString(ss.str(),4,20);
    ofDrawBitmapString(ss.str(),5,21);
    ofDrawBitmapString(ss.str(),5,19);
    ofSetColor(ofColor::blue);
    ofDrawBitmapString(ss.str(),5,20);
    ofPopStyle();
  }  

  INFORMER.draw();
  drawDebug();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){  

  if(OF_KEY_F1==key)
  {
    CanvasFbo.begin();
    ofClear(255,255,255,255);
    CanvasFbo.end();
  }
  else if(OF_KEY_F2==key)
  {
    if(!Keyboard[key])khLuaScript::ofxLuaClear();
  }
  else if(OF_KEY_F3==key)
  {
    if(!Keyboard[key])bShowDebug = !bShowDebug;
  }
  else if(OF_KEY_F4==key)
  {
    Sprites.clear();
  }
  else if(OF_KEY_F5==key)
  {
    randGenSprite(1.0f);
  }

  Keyboard[key] = true;  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  Keyboard[key] = false;  
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  if(button==0)
  {    
    sp->moveToPos(ofVec2f(x,y));
    for(auto widget:GUIs)widget->dragged(x,y);
  } 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  if(button==0)
  {
    ofHideCursor();
    sp->jumpToPos(ofVec2f(x,y));
    for(auto widget:GUIs)widget->pressed(x,y);
  }  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  if(button==0)
  {
    ofShowCursor();
    sp->jumpToPos(sp->getPos());
    for(auto widget:GUIs)widget->released(x,y);
  }  
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  ofSetWindowShape(WindowSize.x,WindowSize.y);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofApp::ofApp()
{
  
}

ofApp::~ofApp()
{
  
}

void ofApp::exit()
{
  
}

void ofApp::randGenSprite(float dt)
{
  if(Sprites.size()>=80)return; 

  float randNum = ofRandom(0,1);
  float Thres = dt;
  if(randNum<Thres)
  {    
    float randNum2 = ofRandom(0,1);
    ofPtr<DrawGame::Sprite> newSp;
    newSp.reset(new DrawGame::Sprite());
    ofVec2f P(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
    newSp->jumpToPos(P);
    if(randNum2<0.3f)
    {      
      newSp->setSize(ofRandom(48,96));      
      ofPtr<DrawGame::Keyhole> KH;
      KH.reset(new DrawGame::khGetInSameCrCircle());
      newSp->linkKeyhole(KH);      
    }
    else
    {
      newSp->setWhite(false);
      newSp->setSize(ofRandom(8,32));      
      ofPtr<DrawGame::Keyhole> KH;
      KH.reset(new DrawGame::khLuaScript(
        "Lua\\testKH.lua","khMatch","khDraw"));
      newSp->linkKeyhole(KH);      
    }
    Sprites.push_back(newSp);       
  }
}

void ofApp::retryButtonCallback( DrawGame::GUIEventArgs &E )
{
  if(!E.opInside&&E.guiOpType!=GUI_PRESSED)return;
  bGameRunning = true;

  spStatus->revive();

  E.guiNode->setVisible(false);
  E.guiNode->setActive(false);

  CanvasFbo.begin();
  ofClear(ofColor::white);
  CanvasFbo.end();

  SOUNDENGINE.playSound("BackgroundMusic");
}

void ofApp::myTest()
{

}

void ofApp::drawDebug()
{}

void ofApp::drawGameOver()
{
  ofRectangle R(0,0,ofGetWidth(),ofGetHeight());
  R.scaleFromCenter(0.5f);
  ofPushStyle();
  ofSetColor(0);
  DrawGame::drawTxtByFontInRect(
    "Game Over",
    &ofxAssets::font("vag",24),
    R,0.0f);
  ofSetColor(255);
  DrawGame::drawTxtByFontInRect(
    "Game Over",
    &ofxAssets::font("vag",24),
    R,2.0f);
  ofPopStyle();
}
