#include "DrawGameUtils.h"

namespace DrawGame
{
  void DrawGame::drawScaledStringByFont( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofRectangle Rect )
  {
    // debug    
    float sh = pFont->stringHeight(Txt);
    float sw = pFont->stringWidth(Txt);

    ofRectangle R0(0,0,sw,-sh);   
   
    ofVec2f Trans = Rect.getCenter()-R0.getCenter();
    float sx,sy;
    sx = Rect.getWidth()/R0.getWidth();
    sy = -Rect.getHeight()/R0.getHeight();
        
    ofMatrix4x4 Mat;
    Mat.translate(-R0.getCenter());
    Mat.scale(sx,sy,1.0f);
   // Mat.translate(Rect.getCenter()/ofVec2f(sx,sy));
    Mat.translate(Rect.getCenter());
    ofMultMatrix(Mat);
    pFont->drawString(Txt,0,0); 
    ofMatrix4x4 MatI;
    MatI = Mat.getInverse();
    ofMultMatrix(MatI);
  }

  void drawScaledStringByFont( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    float width, 
    float height )
  {
    ofRectangle R;
    R.setFromCenter(Pos,width,height);
    drawScaledStringByFont(Txt,pFont,R);
  }

  float getMeshArea( ofMesh* msh )
  {
    vector<ofMeshFace> Fs = msh->getUniqueFaces();
    float Area(0);
    for(const auto& item:Fs) // C++ 11 feature
    {
      ofVec3f P0 = item.getVertex(0);
      ofVec3f P1 = item.getVertex(1);
      ofVec3f P2 = item.getVertex(2);

      ofVec3f P01 = P1-P0;
      ofVec3f P02 = P2-P0;

      ofVec3f C = P01.crossed(P02);
      float A = 0.5*C.length();
      Area += A;   
    }
    return Area;
  }

  bool getAllEdgesIds( ofMesh* msh, vector<pair<ofIndexType,ofIndexType> >& idPairs )
  {
    ofPrimitiveMode Mode = msh->getMode();

    throw "not implemented";
  }

  bool getInnerEdgesIds( ofMesh* msh, vector<pair<ofIndexType,ofIndexType> >& idPairs )
  {
    throw "not implemented";
  }

  bool getBoundaryEdgesIds( ofMesh* msh, vector<pair<ofIndexType,ofIndexType> >& idPairs )
  {
    throw "not implemented";
  }

  vector<pair<ofVec3f,ofVec3f> > getAllEdges( ofMesh* msh )
  {
    throw std::exception("getAllEdges is not implemented.");
  }

  vector<pair<ofVec3f,ofVec3f> > getInnerEdges( ofMesh* msh )
  {
    throw std::exception("getInnerEdges is not implemented.");
  }

  vector<pair<ofVec3f,ofVec3f> > getBoundaryEdges( ofMesh* msh )
  {
    throw std::exception("getBoundaryEdges is not implemented.");
  }

  float getMeshCircumference( ofMesh* msh )
  {
    throw std::exception("getMeshCircumference is not implemented.");
  }

  float getMeshSurfaceArea( ofMesh* msh )
  {
    throw std::exception("getMeshSurfaceArea is not implemented.");
  }

  float getMeshSumEdgeLength( ofMesh* msh )
  {
    throw std::exception("getMeshSumEdgeLength is not implemented.");
  }

  float getMeshRadius( ofMesh* msh )
  {
    ofVec3f C = msh->getCentroid();
    int NumVts = msh->getNumVertices();
    float Radius(0);
    for(int i=0;i<NumVts;i++)
    {
      ofVec3f Vt = msh->getVertex(i);
      float Dist = Vt.distance(C);
      Radius = Dist>Radius?Dist:Radius;
    }
    return Radius;
  }

  bool isIdentity( ofMatrix4x4& A, ofMatrix4x4& B )
  {
    for(int i=0;i<16;i++)
    {
      if(*(A.getPtr()+i)!=*(B.getPtr()+i))
      {
        return false;
      }
    }
    return true;
  }

}
