#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class GameObject;
  class Control
  {
  public:
    Control();
    virtual ~Control();
    virtual void controlling(GameObject* obj);   

  };

}
