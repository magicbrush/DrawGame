#pragma once

#include "ofMain.h"
#include "Body.h"

namespace DrawGame
{
  class bdLine:
    public Body
  {
  public:
    bdLine(Sprite* sp, BodyType T = BodyType::LINE);
    virtual void updateMesh( ) override; 
  };
}
