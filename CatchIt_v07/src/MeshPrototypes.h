#pragma once

#include "ofMain.h"
#include "Sprite.h"

namespace DrawGame
{
  class MeshPrototypes:
    public Sprite
  {
  public:    
   const static ofMesh* rectangle();
   const static ofMesh* line();
   const static ofMesh* circle();
   const static ofMesh* triangle();

  private:
    static const ofMesh MRectangle;
    static const ofMesh MLine;
    static const ofMesh MCircle;
    static const ofMesh MTriangle;

  };
}
