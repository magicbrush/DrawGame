#include "MeshPrototypes.h"
#include "DrawGameUtils.h"

namespace DrawGame
{
  const ofMesh* MeshPrototypes::rectangle()
  {
    return &MRectangle;
  }

  const  ofMesh* MeshPrototypes::line()
  {
    return &MLine;
  }

  const  ofMesh* MeshPrototypes::circle()
  {
    return &MCircle;
  }

  const  ofMesh* MeshPrototypes::triangle()
  {
    return &MTriangle;
  }

  const ofMesh MeshPrototypes::MRectangle = 
    DrawGame::genRectMesh(
    -sqrt(2.0f)/2.0f,-sqrt(2.0f)/2.0f,sqrt(2.0f),sqrt(2.0f));
  
  const ofMesh MeshPrototypes::MLine =
    DrawGame::genLineMesh(ofPoint(0,-1),ofPoint(0,1));
  
  const ofMesh MeshPrototypes::MCircle =
    DrawGame::genCircleMesh(ofPoint(0,0),1,18);

  const ofMesh MeshPrototypes::MTriangle =
    DrawGame::genTriangleMesh(ofPoint(0,0),1,30.0f);

}