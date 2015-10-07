#pragma once 

#ifndef $$GUIBASE$$
#define $$GUIBASE$$

#include "ofMain.h"

namespace DrawGame
{
  enum GUIType
  {
    GUI_TEXT_BUTTON,
    GUI_DATASLOT
  };

  enum GUIOpType
  {
    GUI_PRESSED,
    GUI_DRAGGED,
    GUI_RELEASED
  };
  class GUIBase;
  class GUIEventArgs:
    public ofEventArgs
  {
  public:
    GUIEventArgs( 
      GUIBase* pGuiNode,
      GUIType Type, 
      GUIOpType OpType, 
      string Tag, 
      ofVec2f OpPos, 
      bool OpInside);
    GUIBase* guiNode;
    GUIType guiType;
    GUIOpType guiOpType;
    string tag;
    ofVec2f opPos;
    bool opInside;
  };

  class GUIBase:
    public ofNode,
    public ofBaseUpdates    
  {     
  public:
    GUIBase(
      string tag, 
      bool On = true, 
      bool bVisible=true);
    bool isActive();
    void setActive(bool On);
    bool isVisible();
    void setVisible(bool On);

    void pressed(int x, int y);
    void dragged(int x, int y);
    void released(int x, int y);
    virtual bool inside(int x, int y)=0; 

    ofEvent<GUIEventArgs> GUIEvent;

  protected:
    virtual void customDraw() final;
    virtual void _pressed(int x, int y)=0;
    virtual void _dragged(int x, int y)=0;
    virtual void _released(int x, int y)=0;    
    virtual void _customDraw()=0;

  protected:
    string getTag(){return Tag;};

  private:
    string Tag;
    bool bOn;
    bool bVis;
  };
}

#endif
