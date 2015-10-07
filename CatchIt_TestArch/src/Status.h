#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class GameObject;

  class Status
  {
  public:
    virtual void updateStatus(GameObject* I)=0;
    virtual void affectBy(GameObject* I, GameObject* another)=0;
    
  };
}
