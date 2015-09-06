#pragma once 

#ifndef $$GUIBASE$$
#define $$GUIBASE$$

#include "ofMain.h"

namespace DrawGame
{
  enum GUIType
  {
    GUI_TEXT_BUTTON
  };

  enum GUIOpType
  {
    GUI_PRESSED,
    GUI_DRAGGED,
    GUI_RELEASED
  };

  class GUIEventArgs:
    public ofEventArgs
  {
  public:
    GUIEventArgs( 
      ofNode* pGuiNode,
      GUIType Type, 
      GUIOpType OpType, 
      string Tag, 
      ofVec2f OpPos, 
      bool OpInside);
    ofNode* guiNode;
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
    GUIBase(string tag);
    virtual void pressed(int x, int y)=0;
    virtual void dragged(int x, int y)=0;
    virtual void release(int x, int y)=0;
    virtual bool inside(int x, int y)=0;

    ofEvent<GUIEventArgs> GUIEvent;

  protected:
    string getTag(){return Tag;};

  private:
    string Tag;
  };
}

#endif
