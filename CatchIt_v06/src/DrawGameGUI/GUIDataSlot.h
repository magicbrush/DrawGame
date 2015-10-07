#pragma once 

#ifndef $$GUIDATABAR$$
#define $$GUIDATABAR$$

#include "ofMain.h"
#include "GUIBase.h"

namespace DrawGame
{
  class GUIDataSlot:
    public GUIBase
  {   
  public:
    GUIDataSlot(      
      ofParameter<float>& p,
      ofParameter<float>& pmax,
      string tag="GUIDataBar",
      string title=" ", 
      ofRectangle R=ofRectangle(),
      float TitleWdRatio = 0.1f,
      ofTrueTypeFont* font=NULL,
      float MaxValue=800.0f,
      float BarEdgeWidth=1.0f,        
      ofColor CrTxt = ofColor::black,
      ofColor CrBarEmpty = ofColor(100,100,100,100),
      ofColor CrBarFill = ofColor::green,
      ofColor CrBarEdge = ofColor::black);
    void linkParam(ofParameter<float>& p);

    virtual void update() override;
    virtual bool inside( int x, int y ) override;

  protected:
    virtual void _pressed( int x, int y ) override;
    virtual void _dragged( int x, int y ) override;
    virtual void _release( int x, int y ) override;
    virtual void _customDraw() override;

  private:
    ofTrueTypeFont* pFont;
    ofRectangle Rect;
    string Title;
    float maxVal;
    float titleWdRatio;
    float edgeWd;
    ofColor CrText,CrBG,CrFill,CrEdge;
    ofParameter<float>* dataSrc;
    ofParameter<float>* dataMaxSrc;

    bool bPressed;

    static vector<ofColor> Crs;
  };
}

#endif
