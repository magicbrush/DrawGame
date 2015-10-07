#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Brush
  {
  public:
    
    virtual void painting(
      ofMesh* shape, 
      ofMatrix4x4 TF=ofMatrix4x4());



  };

}
