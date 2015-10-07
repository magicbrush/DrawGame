#include "bdCircle.h"
#include "MeshPrototypes.h"

namespace DrawGame
{

  bdCircle::bdCircle( 
    Sprite* sp,
    BodyType T /*= BodyType::CIRCLE*/ ):
    Body(sp,T)
  {
     
  }

  void bdCircle::updateMesh( )
  {
    _updateMesh((ofMesh*)MeshPrototypes::circle());
  }
}