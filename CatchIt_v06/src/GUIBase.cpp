#include "GUIBase.h"


DrawGame::GUIEventArgs::GUIEventArgs(
  ofNode* pGuiNode, 
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

  DrawGame::GUIBase::GUIBase( string tag ):Tag(tag)
  {
    
  }
