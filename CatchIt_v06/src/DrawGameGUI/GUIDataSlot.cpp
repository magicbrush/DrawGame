#include "GUIDataSlot.h"
#include "DrawGameUtils.h"

using namespace DrawGame;


vector<ofColor> DrawGame::GUIDataSlot::Crs;

DrawGame::GUIDataSlot::GUIDataSlot(  
  ofParameter<float>& p,
  ofParameter<float>& pmax,
  string tag,
  string title, 
  ofRectangle R,
  float TitleWdRatio,
  ofTrueTypeFont* font,
  float MaxValue,  
  float BarEdgeWidth,  
  ofColor CrTxt,
  ofColor CrBarEmpty,
  ofColor CrBarFill,
  ofColor CrBarEdge):
dataSrc(&p),
dataMaxSrc(&pmax),
GUIBase(tag),
pFont(font),
Title(title),
maxVal(MaxValue),
titleWdRatio(TitleWdRatio),
edgeWd(BarEdgeWidth),
CrText(CrTxt),
CrBG(CrBarEmpty),
CrFill(CrBarFill),
CrEdge(CrBarEdge)
{
  if(Crs.size()==0)
  {
    ofColor defCrs[10] = {
      ofColor::yellow,
      ofColor::green, 
      ofColor::darkGreen,
      ofColor::skyBlue,
      ofColor::cyan, 
      ofColor::blue, 
      ofColor::blueViolet,
      ofColor::violet,
      ofColor::chocolate,
      ofColor::black};
    for(int i=0;i<10;i++)
    {
      Crs.push_back(defCrs[i]);
    }
  }
  Rect.setFromCenter(ofVec2f(0,0),R.getWidth(),R.getHeight());
  ofNode::setPosition(R.getCenter());
}

bool DrawGame::GUIDataSlot::inside( int x, int y )
{
  bool bIn;
  ofVec3f PressPos(x,y,0);
  ofMatrix4x4 MyMat = ofNode::getGlobalTransformMatrix();
  ofMatrix4x4 MyMatI = MyMat.getInverse();
  ofVec2f PressPosT = PressPos*MyMatI;
  bIn = Rect.inside(PressPosT);
  return bIn;
}

void DrawGame::GUIDataSlot::linkParam( ofParameter<float>& p )
{
  dataSrc = &p;
}

void GUIDataSlot::_pressed( int x, int y )
{
  bool bIn = inside(x,y);  
  if(bIn)
  {
    bPressed = true;
    GUIEventArgs E(
      this,
      GUI_DATASLOT,
      GUI_PRESSED,
      getTag(),
      ofVec2f(x,y),
      bIn);
    ofNotifyEvent(GUIEvent,E);
  } 
}

void GUIDataSlot::_dragged( int x, int y )
{  
  if(bPressed)
  {
    bool bIn = inside(x,y);
    GUIEventArgs E(
      this,
      GUI_DATASLOT,
      GUI_DRAGGED,
      getTag(),
      ofVec2f(x,y),
      bIn);
    ofNotifyEvent(GUIEvent,E);
  }  
}

void GUIDataSlot::_release( int x, int y )
{
  if(bPressed)
  {
    bool bIn = inside(x,y);
    GUIEventArgs E(
      this,
      GUI_DATASLOT,
      GUI_RELEASED,
      getTag(),
      ofVec2f(x,y),
      bIn);
    ofNotifyEvent(GUIEvent,E);
    bPressed = false;
  }  
}

void GUIDataSlot::_customDraw()
{
  float ht = Rect.getHeight();
  float wd = Rect.getWidth();
  float minEdge = min(ht,wd);
  float Val = *dataSrc;
  float vMax = dataMaxSrc->get();
  float vMin = dataSrc->getMin();
  float Range = vMax-vMin;  
  float BarLenNorm = (Val-vMin)/min(maxVal,Range); 
  float SlotLenNorm = ofClamp(Range/maxVal,0,1);
  
  bool bOverFlow(false);
  if(BarLenNorm>Crs.size())
  { 
    bOverFlow = true;
    BarLenNorm = ofClamp(BarLenNorm,0,Crs.size());
  }

  float totalWd = Rect.getWidth();
  float ttlWd = totalWd*titleWdRatio;
  float barWd = totalWd-ttlWd;
  ofPushStyle();
  {    
    ofRectangle RBar(
      Rect.getX()+ttlWd,
      Rect.getY(),
      barWd*SlotLenNorm,
      Rect.getHeight());
    ofSetColor(CrBG);
    ofFill();  
    ofRect(RBar);
    int MaxBarNum = ceil(BarLenNorm);
   
    for(int i=0;i<MaxBarNum;i++)
    {
      float Len = (BarLenNorm-i);
      float wdNorm = ofClamp(Len,0,1);      
      ofRectangle RVal(RBar);
      RVal.setWidth(RBar.getWidth()*wdNorm); 
      ofColor C = Crs[i];
      ofSetColor(C);
      ofRect(RVal);
    }    
    ofNoFill();
    ofSetColor(CrEdge);
    ofSetLineWidth(edgeWd);
    ofRect(RBar);
  }  
  {
    ofRectangle RTitle(
      Rect.getX(),Rect.getY(),ttlWd,Rect.getHeight());
    ofSetColor(CrText);
    if(pFont==NULL)
    {
      ofVec2f PosTitle = 
        0.5f*(RTitle.getBottomLeft()+RTitle.getTopLeft());
      ofDrawBitmapString(Title,PosTitle);
    }
    else
    {
      ofVec2f PosTitle = RTitle.getBottomLeft();
      ofRectangle R = RTitle;
      R.setFromCenter(ofVec2f(0,0),20,20);

      float titleWd = pFont->stringWidth(Title);
      float titleHt = pFont->stringHeight(Title);

      R.setFromCenter(
        RTitle.getCenter(),
        R.getHeight()*titleWd/titleHt,
        titleHt);
      R.scaleFromCenter(0.9f);

      DrawGame::drawTxtByFontInRect(Title,pFont,R);      
    }
  }
  ofPopStyle(); 
}

void GUIDataSlot::update()
{
  
}
