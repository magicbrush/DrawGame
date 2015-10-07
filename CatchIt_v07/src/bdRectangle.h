#pragma once

#include "ofMain.h"
#include "Body.h"

namespace DrawGame
{
  class bdRectangle:
    public Body
  {
  public:
    bdRectangle(Sprite* sp, BodyType T = BodyType::RECTANGLE);
    virtual void updateMesh() override;
    
  };
}
