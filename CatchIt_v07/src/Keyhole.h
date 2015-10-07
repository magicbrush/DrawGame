#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Status;
  class Sprite;

  class Keyhole
  {
  public:
    Keyhole();
    virtual ~Keyhole();
    void match(Status* AStatus, Sprite* A, Sprite* B);
    virtual void draw(){}

  protected:
    virtual void _match(Status* S, Sprite* A, Sprite* B)=0;

    void resetPtr(
      Status* S=nullptr, Sprite* A=nullptr, Sprite* B=nullptr);
    Status* getStatusPtr();
    Sprite* getAPtr();
    Sprite* getBPtr();
    
  private:
    Status* s;
    Sprite* a;
    Sprite* b;

  public:
    static bool contact(Sprite* a, Sprite* b);
    
  };
}
