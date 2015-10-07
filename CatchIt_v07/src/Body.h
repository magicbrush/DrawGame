#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Sprite;
  enum class BodyType
  {    
    CIRCLE=0,
    LINE=1,
    TRIANGLE=2,
    RECTANGLE=3
  };

  class Body
  {
  public:
    Body(Sprite* sp, BodyType AType = BodyType::CIRCLE);
    virtual ~Body();
    virtual void updateMesh()=0; 
    virtual void render();
    BodyType getBodyType() const;  
    void setImageTextureFile(string ImageName);
  
  protected:  
    ofMesh* getMesh();
    void _updateMesh(ofMesh* protoMesh);         
    void computeMeshFromProtoAndTF( 
      ofMesh &m, const ofMesh* protoMesh, ofMatrix4x4 T );
    ofMatrix4x4 getCurrentTransformMatrix();

  private:
    Sprite* spMaster;
    ofParameter<int> bodyType;
    ofMesh Mesh;
    ofMatrix4x4 TF;
    string imageName;
  };
}
