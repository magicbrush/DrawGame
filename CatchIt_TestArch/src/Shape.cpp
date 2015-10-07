#include "Shape.h"
#include "DrawGameUtils.h"

float DrawGame::Shape::diameter()
{
  return 2.0f*radius();
}

bool DrawGame::Shape::encompass( Shape* another )
{
  bool bFlag(false);

  ofVec3f Pos = getGlobalPosition();
  ofVec3f Scl = getGlobalScale();
  float Radius = max(Scl[0],Scl[1]);

  ofVec3f PosA = another->getGlobalPosition();
  ofVec3f SclA = another->getGlobalScale();
  float RadiusA = max(SclA[0],SclA[1]);

  float dist = PosA.distance(Pos);

  bool bF0 = Radius>=RadiusA;
  bool bF1 = dist<abs(Radius-RadiusA);

  bFlag = bF0&&bF1;
  return bFlag;
}

bool DrawGame::Shape::intersect( Shape* another )
{
  bool bFlag(false);

  ofVec3f Pos = getGlobalPosition();
  ofVec3f Scl = getGlobalScale();
  float Radius = max(Scl[0],Scl[1]);

  ofVec3f PosA = another->getGlobalPosition();
  ofVec3f SclA = another->getGlobalScale();
  float RadiusA = max(SclA[0],SclA[1]);

  float dist = PosA.distance(Pos);

  bFlag = dist <= Radius+RadiusA;

  return bFlag;
}

ofVec2f DrawGame::Shape::center()
{
  ofMesh* Msh = updateMesh();
  ofVec3f Ctr = Msh->getCentroid(); 
  return Ctr;
}

float DrawGame::Shape::radius()
{
  ofMesh* Msh = updateMesh();
  float Radius = DrawGame::getMeshRadius(Msh);

  return Radius;
}

float DrawGame::Shape::area()
{
  ofMesh* msh = updateMesh();
  float Area = DrawGame::getMeshArea(msh);
  return Area;
}


