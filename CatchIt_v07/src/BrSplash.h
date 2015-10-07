#pragma once

#include "ofMain.h"
#include "Brush.h"

namespace DrawGame
{
  class Tracer;
  class BrSplash: 
    public Brush
  {
  public:   
    BrSplash();
    virtual ~BrSplash();  
    virtual void paintAtLenOnTrace(  float len, Tracer* T );
  };
}
