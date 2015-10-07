#pragma  once
#ifndef $$DRAWGAMEUTILS_H$$
#define $$DRAWGAMEUTILS_H$$

#include "ofMain.h"

namespace DrawGame
{
  void drawScaledStringByFont(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofRectangle Rect);
  void drawScaledStringByFont(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    float width,
    float height);

  float getMeshArea(ofMesh* msh);  
  bool getAllEdgesIds(ofMesh* msh,
    vector<pair<ofIndexType,ofIndexType> >& idPairs);
  bool getInnerEdgesIds(ofMesh* msh,
    vector<pair<ofIndexType,ofIndexType> >& idPairs);
  bool getBoundaryEdgesIds(ofMesh* msh,
    vector<pair<ofIndexType,ofIndexType> >& idPairs);
  vector<pair<ofVec3f,ofVec3f> > getAllEdges(ofMesh* msh);
  vector<pair<ofVec3f,ofVec3f> > getInnerEdges(ofMesh* msh);
  vector<pair<ofVec3f,ofVec3f> > getBoundaryEdges(ofMesh* msh);
  float getMeshCircumference(ofMesh* msh);
  float getMeshSurfaceArea(ofMesh* msh);
  float getMeshSumEdgeLength(ofMesh* msh);
  float getMeshRadius(ofMesh* msh);
  
  bool isIdentity(ofMatrix4x4& A, ofMatrix4x4& B);

}

#endif