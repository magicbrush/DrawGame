#pragma once

#include "ofMain.h"
#include "Keyhole.h"
namespace DrawGame
{
  class Status;
  class Sprite;

  class khGetInSameCrCircle: 
    public Keyhole
  {
  public:
    khGetInSameCrCircle();
    ~khGetInSameCrCircle();
    virtual void _match(Status* AStatus, Sprite* A, Sprite* B) override;

    virtual void draw();

  private:
   
  };
}
