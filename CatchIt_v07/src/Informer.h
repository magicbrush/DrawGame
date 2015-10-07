#pragma once

#include "ofMain.h"
#include "SingletonTemplate.h"
#define INFORMER (singleton<Informer>::instance())

namespace DrawGame
{
  class Informer:
    public ofBaseUpdates,
    public ofBaseDraws
  {
  public:
    struct InfoStruct
    {
      ofPtr<ofNode> iNode;
      float delay;
      float duration;
      float speed;
    };

  public:
    Informer();
    ~Informer();

    void pushInfo(ofPtr<ofNode> Info, 
      float duration = 1.0f,
      float delay = 0.0f,
      float zOrder = 0.0f,
      float speed = 1.0f);
    void update() final;    
    void draw( float x = 0, float y = 0 ) final;

  private:
    virtual void draw( 
      float x, float y, float w, float h ) final;
    virtual float getHeight() final;
    virtual float getWidth() final;
    
  private:
    map<float,InfoStruct> I;

    float timeLast;
  };
  
}
