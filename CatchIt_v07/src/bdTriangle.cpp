#include "bdTriangle.h"
#include "MeshPrototypes.h"

namespace DrawGame
{

  bdTriangle::bdTriangle( 
    Sprite* sp, BodyType T /*= BodyType::TRIANGLE*/ ):
  Body(sp,T)
  {

  }

  void bdTriangle::updateMesh(  )
  {
    _updateMesh((ofMesh*)MeshPrototypes::triangle());
  }
}