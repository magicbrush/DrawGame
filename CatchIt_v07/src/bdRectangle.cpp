#include "bdRectangle.h"
#include "MeshPrototypes.h"

namespace DrawGame
{

  bdRectangle::bdRectangle( 
    Sprite* sp, BodyType T /*= BodyType::RECTANGLE*/ ):
    Body(sp,T)
  {

  }

  void bdRectangle::updateMesh(  )
  {
    _updateMesh((ofMesh*)MeshPrototypes::rectangle());
  }

}