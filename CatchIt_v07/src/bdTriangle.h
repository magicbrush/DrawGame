#pragma once

#include "ofMain.h"
#include "Body.h"

namespace DrawGame
{
  class bdTriangle:
    public Body
  {
  public:
    bdTriangle(Sprite* sp, BodyType T = BodyType::TRIANGLE);
    virtual void updateMesh() override;
 
  };
}
