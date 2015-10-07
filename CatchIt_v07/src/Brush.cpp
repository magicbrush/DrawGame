#include "Brush.h"
#include "Tracer.h"

namespace DrawGame
{

  Brush::Brush():
    pCanvas(nullptr)
  {
    PassedDist = 0.0f;
    Speed.set("Speed",3000.0f,10.0f,10000.0f);
    Step.set("Step",0.05f,0.001f,16.0f);
  }

  Brush::~Brush()
  {

  }

  void Brush::paint( Tracer* T )
  {
    if(pCanvas==nullptr||!pCanvas->isAllocated())return;

    float Len = T->getTotalLen();
    if(PassedDist>=Len)return;

    pCanvas->begin();    
    ofPushStyle();
    while(PassedDist<Len)
    {
      paintAtLenOnTrace(PassedDist,T);
      float s = T->getSizeAtDist(PassedDist);
      PassedDist+=min(Step*s,1.0f);
    }
    ofPopStyle();   
    pCanvas->end();
  }

  void Brush::reset()
  {
    PassedDist = 0;
  }
  
  void Brush::linkCanvas( ofFbo* canvas )
  {
    pCanvas = canvas;
  }

  void Brush::paintAtLenOnTrace(  float len, Tracer* T )
  {
    ofVec2f paintPos = T->getPosAtLen(len); 
    float s,r;
    T->getSizeRotAtDist(s,r,len);
    ofSetColor(0);
    ofFill();
    ofPushMatrix();
    ofTranslate(paintPos);
    ofRotateZ(r);
    ofScale(1.0f,2.0f,1.0f);
    ofCircle(ofPoint(0,0,0),s/10.0f);
    ofPopMatrix();
  }

  ofParameterGroup Brush::getParameterGroup()
  {
    ofParameterGroup G;
    G.setName("Brush");    
    G.add(Speed);
    G.add(Step);
    return G;
  }

}