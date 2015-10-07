#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Tracer;
  class Brush
  {
  public:   
    Brush();
    virtual ~Brush();

    void linkCanvas(ofFbo* canvas);
    void paint(Tracer* T);
    void reset();

    virtual void paintAtLenOnTrace(  float len, Tracer* T );
    virtual ofParameterGroup getParameterGroup();

  private:
    ofFbo* pCanvas;
    float PassedDist;
    ofParameter<float> Speed;
    ofParameter<float> Step;    

  };
}
