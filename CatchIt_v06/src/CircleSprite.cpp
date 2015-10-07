#include "CircleSprite.h"
#include "DrawGameUtils.h"

DrawGame::CircleSprite::CircleSprite( 
  ofTrueTypeFont* font,
  ofVec2f Pos /*= ofVec2f(0,0)*/, 
  float size /*= 50.0f*/,   
  float rot /*= 0.0f*/,
  bool bWhite /*= false*/,
  SpriteMood defaultMood /* = DRAWGAME_MOOD_ACTIVE*/
  ):
pFont(font),
X(Pos.x),
Y(Pos.y),
Size(size),
Rot(rot),
White(bWhite),
Mood(defaultMood)
{

}

DrawGame::CircleSprite::~CircleSprite(void)
{

}

void DrawGame::CircleSprite::jumpTo( ofVec2f Pos )
{
  X = Pos.x;
  Y = Pos.y;  
  clearTrace();
  addTrace();
}

void DrawGame::CircleSprite::moveTo( ofVec2f Pos )
{
  X = Pos.x;
  Y = Pos.y;  
  addTrace();
}

void DrawGame::CircleSprite::setSize( float size )
{
  Size = ofClamp(size,3.0f,1024.0f);
}

void DrawGame::CircleSprite::setRot( float degrees )
{
  Rot = degrees;
  Rot = ofWrapDegrees(Rot);
}

void DrawGame::CircleSprite::setWhite( bool bWhite )
{
  White = bWhite;
}

void DrawGame::CircleSprite::draw()
{
  // 显示圆形	
  ofPushMatrix();	 
  ofTranslate(ofPoint(X,Y)); 
  ofRotate(Rot,0,0,1); 
  ofScale(Size,Size,1.0f);   
  drawFill();  
  drawEdge();  
  ofPopMatrix();

  // 显示表情
  ofPushMatrix();
  ofTranslate(ofPoint(X,Y));
  ofRotate(Rot,0,0,1);	 
  ofScale(Size,Size,1.0f);  
  drawFace();
  ofPopMatrix();
}

void DrawGame::CircleSprite::paint()
{
  if(Trace.size()<4)return;
  // 绘制路径
  ofSetLineWidth(Size/10);
  ofNoFill();
  ofPushMatrix();	 
  Trace.draw();
  ofPopMatrix();
}

void DrawGame::CircleSprite::drawFill()
{
  ofPushStyle();
  ofStyle S = ofGetStyle(); 
  S.bFill = true;	
  S.circleResolution = 36;
  S.color = White?ofColor::white:ofColor::black;
  ofSetStyle(S);
  ofCircle(0,0,1.0f);  
  ofPopStyle();
}

void DrawGame::CircleSprite::drawEdge()
{
  ofPushStyle();
  ofStyle S = ofGetStyle(); 
  S.bFill = false;	
  S.circleResolution = 36;
  S.color = White?ofColor::black:ofColor::white;
  S.lineWidth = 1.0f;
  ofSetStyle(S);
  ofCircle(0,0,1.0f);
  ofPopStyle();
}

ofVec2f DrawGame::CircleSprite::getPosition()
{
  return ofVec2f(X,Y);
}

float DrawGame::CircleSprite::getSize()
{
  return Size;
}

float DrawGame::CircleSprite::getRot()
{
  return Rot;
}

bool DrawGame::CircleSprite::getbWhite()
{
  return White;
}

void DrawGame::CircleSprite::move( ofVec2f Trans )
{
  X += Trans.x;
  Y += Trans.y;
  addTrace();
}

void DrawGame::CircleSprite::changeSize( float deltaSize )
{
  setSize(Size+deltaSize);
}

void DrawGame::CircleSprite::changeRot( float deltaRot )
{
  setRot(Rot+deltaRot);
}

void DrawGame::CircleSprite::setMood( SpriteMood m )
{
  Mood = m;
}

DrawGame::SpriteMood DrawGame::CircleSprite::getMood()
{
  return Mood;
}

std::string DrawGame::CircleSprite::getModeString()
{
  string S;
  if(DRAWGAME_MOOD_ACTIVE==Mood)
  {
    S="^o^";
  }
  else if(DRAWGAME_MOOD_BORING==Mood)
  {
    S="/_\\";
  }
  else if(DRAWGAME_MOOD_JOY==Mood)
  {
    S="^_^";
  }
  else if(DRAWGAME_MOOD_EVIL==Mood)
  {
    S="^w^";
  }
  return S;
}

bool DrawGame::CircleSprite::encompass( CircleSprite& Another )
{
  ofVec2f PAnother = Another.getPosition();
  float SizeAnother = Another.getSize();

  ofVec2f PThis = getPosition();
  float SizeThis = getSize();

  float dist = PAnother.distance(PThis);
  bool bLarger = SizeThis>SizeAnother;
  bool bNear = (dist<abs(SizeAnother-SizeThis));
  bool bEncompass = bLarger&&bNear;
  return bEncompass;
}

bool DrawGame::CircleSprite::intersect( CircleSprite& Another )
{
  ofVec2f PAnother = Another.getPosition();
  float SizeAnother = Another.getSize();

  ofVec2f PThis = getPosition();
  float SizeThis = getSize();

  float dist = PAnother.distance(PThis);
  bool bIntersect = dist<(SizeAnother+SizeThis);

  return bIntersect;
}

bool DrawGame::CircleSprite::isSameColor( CircleSprite& Another )
{
  bool bSame = (White==Another.getbWhite());
  return bSame;
}

void DrawGame::CircleSprite::drawFace()
{
  ofPushStyle();
  ofColor FaceColor = 
    White?ofColor::black:ofColor::white;
  ofSetColor(FaceColor);   
  DrawGame::drawTxtByFontInRect(
    getModeString(),pFont,ofVec2f(0,0),1.2f,1.2f);
  ofPopStyle();
}

void DrawGame::CircleSprite::clearTrace()
{
  Trace.clear();
}

void DrawGame::CircleSprite::addTrace()
{
  Trace.curveTo(ofVec2f(X,Y));
}

