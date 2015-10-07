#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Shape:
    public ofNode
  {
  public:
    virtual ofMesh* updateMesh()=0;
    virtual ofVec2f center();
    virtual float radius();
    float diameter();
    virtual float area();     
   
    virtual bool encompass(Shape* another);
    virtual bool intersect(Shape* another);
  };
}