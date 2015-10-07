#pragma once

#include "ofMain.h"
#include "Keyhole.h"
namespace DrawGame
{
  class Status;
  class Sprite;

  class khEncompassInvCrCircle: 
    public Keyhole
  {
  public:
    khEncompassInvCrCircle();
    ~khEncompassInvCrCircle();
    virtual void _match(Status* AStatus, Sprite* A, Sprite* B) override;

    virtual void draw();

  private:
   
  };
}
