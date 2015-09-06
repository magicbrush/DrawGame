#pragma once 

#ifndef $$GUITEXTBUTTON$$
#define $$GUITEXTBUTTON$$

#include "ofMain.h"
#include "GUIBase.h"

namespace DrawGame
{
  class GUITextButton:
    public GUIBase
  {   
  public:
    GUITextButton(
      string tag,
      string title, 
      float wd,
      float ht,
      ofTrueTypeFont* font=NULL,
      ofVec2f Pos= ofVec2f(0,0),
      ofColor ColorText = ofColor::white,
      ofColor ColorBG = ofColor::black);

    virtual void update();

    virtual void pressed( int x, int y );
    virtual void dragged( int x, int y );
    virtual void release( int x, int y );
    virtual bool inside( int x, int y );

  protected:
    virtual void customDraw();

  private:
    ofTrueTypeFont* pFont;
    ofRectangle Rect;
    string Title;
    ofColor CrText,CrBG;

    bool bPressed;
  };
}

#endif
