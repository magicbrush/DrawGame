#pragma once

#include "ofMain.h"
#include "Body.h"

namespace DrawGame
{
  class bdCircle:
    public Body
  {
  public:
    bdCircle(Sprite* sp, BodyType T = BodyType::CIRCLE);
    virtual void updateMesh( ) override;
  
  };
}
