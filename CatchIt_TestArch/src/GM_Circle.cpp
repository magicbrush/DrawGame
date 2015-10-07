#include "GM_Circle.h"
#include "DrawGameUtils.h"
namespace DrawGame
{
  Circle::Circle( int CircleResolution/*=18*/ )
  {
    circRes.set("CircleResolution",CircleResolution,3,360);
    circResChanged(CircleResolution);
    circRes.addListener(this,&Circle::circResChanged);
  }

  ofMesh* Circle::updateMesh()
  {
    ofMatrix4x4 TFCur = getGlobalTransformMatrix();
    if(DrawGame::isIdentity(TFCur,TF))
    {     
      return &Mesh;
    }

    TF = TFCur;
    int VtNum = Mesh.getNumVertices();
    ofVec3f* vtPtr = Mesh.getVerticesPointer();
    ofVec3f* vtPtrBase = MeshBase.getVerticesPointer();
    for(int i=0;i<VtNum;i++)
    {
      ofVec3f & Vt = *(vtPtr+i);
      ofVec3f & VtB = *(vtPtrBase+i);
      Vt = VtB*TF;
    }
    return &Mesh;
  }

  void Circle::circResChanged( int &r )
  {
    MeshBase.clear();
    MeshBase.setMode(OF_PRIMITIVE_TRIANGLES);

    MeshBase.addVertex(ofVec3f(0,0,0));
    MeshBase.addTexCoord(ofVec2f(0.5f,0.5f));

    float radStep = 2.0f*PI/r;
    float radius = 1.0f;
    for(int i=0;i<r+1;i++)
    {
      float theta = i*radStep;
      float x = cos(theta)*radius;
      float y = sin(theta)*radius;
      MeshBase.addVertex(ofVec3f(x,y,0));

      ofVec2f TC(x,y);
      TC = 0.5f*(TC+ofVec2f(1,1));
      MeshBase.addTexCoord(TC);

      int Num = MeshBase.getNumVertices();
      if(Num>2)
      {
        MeshBase.addIndex(0);
        MeshBase.addIndex(Num-2);
        MeshBase.addIndex(Num-1);
      }
    }

    Mesh.clear();
    Mesh = MeshBase;
  }

}
