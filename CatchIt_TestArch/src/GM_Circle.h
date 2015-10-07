#pragma once

#include "ofMain.h"
#include "Shape.h"

namespace DrawGame
{
  class Circle:
    public Shape
  {
  public:
    Circle(int CircleResolution=18);
    
    virtual ofMesh* updateMesh();    

  private:
    ofParameter<int> circRes;
    void circResChanged(int &r);

    ofMesh MeshBase;
    ofMesh Mesh;
    ofMatrix4x4 TF;
  };

}
