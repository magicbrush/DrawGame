#include "GUITextButton.h"
#include "DrawGameUtils.h"

using namespace DrawGame;

DrawGame::GUITextButton::GUITextButton( 
  string tag,
  string title, 
  float wd, float ht, 
  ofTrueTypeFont* font, 
  ofVec2f Pos/*= ofVec2f(0,0)*/, 
  ofColor ColorText /*= ofColor::white*/, 
  ofColor ColorBG /*= ofColor::black*/ ):
GUIBase(tag),
pFont(font),
Rect(ofRectangle(-wd/2,-ht/2,wd,ht)),
Title(title),
CrText(ColorText),
CrBG(ColorBG)
{
  ofNode::setPosition(Pos);
}

bool DrawGame::GUITextButton::inside( int x, int y )
{
  bool bIn;
  ofVec3f PressPos(x,y,0);
  ofMatrix4x4 MyMat = ofNode::getGlobalTransformMatrix();
  ofMatrix4x4 MyMatI = MyMat.getInverse();
  ofVec2f PressPosT = PressPos*MyMatI;
  bIn = Rect.inside(PressPosT);
  return bIn;
}

void GUITextButton::_pressed( int x, int y )
{
  bool bIn = inside(x,y);  
  if(bIn)
  {
    bPressed = true;
    GUIEventArgs E(
      this,
      GUI_TEXT_BUTTON,
      GUI_PRESSED,
      getTag(),
      ofVec2f(x,y),
      bIn);
    ofNotifyEvent(GUIEvent,E);
  } 
}

void GUITextButton::_dragged( int x, int y )
{  
  if(bPressed)
  {
    bool bIn = inside(x,y);
    GUIEventArgs E(
      this,
      GUI_TEXT_BUTTON,
      GUI_DRAGGED,
      getTag(),
      ofVec2f(x,y),
      bIn);
    ofNotifyEvent(GUIEvent,E);
  }  
}

void GUITextButton::_release( int x, int y )
{
  if(bPressed)
  {
    bool bIn = inside(x,y);
    GUIEventArgs E(
      this,
      GUI_TEXT_BUTTON,
      GUI_RELEASED,
      getTag(),
      ofVec2f(x,y),
      bIn);
    ofNotifyEvent(GUIEvent,E);
    bPressed = false;
  }  
}

void GUITextButton::_customDraw()
{
  float ht = Rect.getHeight();
  float wd = Rect.getWidth();
  float minEdge = min(ht,wd);
  ofPushStyle();
  ofSetColor(CrBG);
  ofFill();
  ofRectRounded(Rect,minEdge/5.0f);
  ofPopStyle();

  ofPushStyle();
  ofSetColor(CrText);
  if(pFont==NULL)
  {
    ofVec2f PosTitle = 
      0.5f*(Rect.getBottomLeft()+Rect.getTopLeft());
    ofDrawBitmapString(Title,PosTitle);
  }
  else
  {
    ofVec2f PosTitle = Rect.getBottomLeft();
    ofRectangle R = Rect;
    R.scaleFromCenter(0.9f);

    float titleWd = pFont->stringWidth(Title);
    float titleHt = pFont->stringHeight(Title);

    R.setFromCenter(
      Rect.getCenter(),
      R.getHeight()*titleWd/titleHt,
      titleHt);
    R.scaleFromCenter(0.8f);

    DrawGame::drawTxtByFontInRect(Title,pFont,R);
  }
  ofPopStyle();

}

void GUITextButton::update()
{
  
}
