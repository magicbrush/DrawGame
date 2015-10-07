#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Sprite;
  class Tracer
  {
  public:

    void draw();

    void trace(ofVec2f Pos,float Size, float Rot);
    void traceClear();

    float getTotalLen();
    ofVec2f getPosAtLen(float d);
    float getSpdAtDist(float d);
    ofVec2f getVelocityAtLen(float d);
    float getSizeAtDist(float d);
    float getRotAtDist(float d);
    void getSizeRotAtDist(float &size, float &rot, float d);

  private:
    struct Trace
    {
      ofPolyline XY;
      ofPolyline TimeLen;
      ofPolyline SizeRot;
    }T;
    

  };
}
