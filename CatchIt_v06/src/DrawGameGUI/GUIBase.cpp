#include "GUIBase.h"


DrawGame::GUIEventArgs::GUIEventArgs(
  GUIBase* pGuiNode, 
  GUIType Type, 
  GUIOpType OpType, 
  string Tag, 
  ofVec2f OpPos, 
  bool OpInside ) :
  guiNode(pGuiNode),
  guiType(Type),
  guiOpType(OpType),
  tag(Tag),
  opPos(OpPos),
  opInside(OpInside)
{}

  DrawGame::GUIBase::GUIBase( 
    string tag, 
    bool On,
    bool bVisible):
  Tag(tag),
  bOn(On),
  bVis(bVisible)
  {
    
  }

  bool DrawGame::GUIBase::isActive()
  {
    return bOn;
  }

  void DrawGame::GUIBase::setActive( bool On )
  {
    bOn = On;
  }

  bool DrawGame::GUIBase::isVisible()
  {
    return bVis;
  }

  void DrawGame::GUIBase::setVisible( bool On )
  {
    bVis = On;
  }

  void DrawGame::GUIBase::pressed( int x, int y )
  {
    if(bOn)_pressed(x,y);
  }

  void DrawGame::GUIBase::dragged( int x, int y )
  {
    if(bOn)_dragged(x,y);
  }

  void DrawGame::GUIBase::release( int x, int y )
  {
    if(bOn)_release(x,y);
  }

  void DrawGame::GUIBase::customDraw()
  {
    if(bVis)_customDraw();
  }



