#include "Body.h"
#include "DrawGameUtils.h"
#include "MeshPrototypes.h"
#include "ofxAssets.h"

namespace DrawGame
{
  Body::Body(Sprite* sp, BodyType AType):
    spMaster(sp),
    imageName("")
  {     
    ofDisableArbTex();
    bodyType.set("ShapeType",int(AType),0,3);
  }

  Body::~Body()
  {

  }

  void Body::render()
  {
    ofMesh* msh = getMesh();

    ofPushStyle();
    ofColor C = 
      spMaster->isWhite()?ofColor::white:ofColor::black;
    ofSetColor(C);
    if(imageName!="")
    {
      ofImage& I = ofxAssets::image(imageName);
      ofTexture& T = I.getTextureReference();
      T.bind();
    }    
    msh->draw();
    if(imageName!="")
    {
      ofImage& I = ofxAssets::image(imageName);
      ofTexture& T = I.getTextureReference();
      T.unbind();
    }
    if(imageName=="")
    {
      ofColor C2 = 
        spMaster->isWhite()?ofColor::black:ofColor::white;
      ofSetColor(C2);
      msh->drawWireframe();
    }    
    ofPopStyle();   
  }

  DrawGame::BodyType Body::getBodyType() const
  {
    return BodyType(bodyType.get());
  }

  void Body::setImageTextureFile( string ImageName )
  {
    imageName = ImageName;
  }

  ofMesh* Body::getMesh()
  {
    return &Mesh;
  }

  void Body::_updateMesh(ofMesh* protoMesh)
  {   
    ofMatrix4x4 TFCur=getCurrentTransformMatrix();   
    if(DrawGame::isIdentity(TFCur,TF))return;
    TF = TFCur;
    computeMeshFromProtoAndTF(Mesh,protoMesh,TF);   
  }

  void Body::computeMeshFromProtoAndTF( 
    ofMesh &m, 
    const ofMesh* protoMesh, 
    ofMatrix4x4 T )
  {
    m = *protoMesh;
    ofVec3f* vtp = m.getVerticesPointer();
    int NumVts = m.getNumVertices();
    for(int i=0;i<NumVts;i++)
    {
      ofVec3f& vt = *(vtp+i);      
      vt = vt*T;
    }    
  }

  ofMatrix4x4 Body::getCurrentTransformMatrix()
  {
    ofMatrix4x4 TFCur;   
    TFCur.rotate(spMaster->getRot(),0,0,1);
    float S = spMaster->getSize();
    TFCur.scale(ofVec2f(S,S));
    TFCur.translate(ofVec3f(spMaster->getPos()));  
    return TFCur;
  }

}