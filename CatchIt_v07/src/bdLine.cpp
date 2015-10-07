#include "bdLine.h"
#include "MeshPrototypes.h"

namespace DrawGame
{
  bdLine::bdLine( 
    Sprite* sp,
    BodyType T /*= BodyType::LINE*/ ):
  Body(sp,T)
  {

  }
  void bdLine::updateMesh(  )
  {
    _updateMesh((ofMesh*)MeshPrototypes::line());
  }

}