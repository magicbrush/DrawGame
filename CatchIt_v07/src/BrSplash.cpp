#include "BrSplash.h"
#include "Tracer.h"
#include "DrawGameUtils.h"

namespace DrawGame
{

  BrSplash::BrSplash()
  {
  }

  BrSplash::~BrSplash()
  {
  }

  void BrSplash::paintAtLenOnTrace(  float len, Tracer* T )
  {
    ofVec2f paintPos = T->getPosAtLen(len); 
    float s,r;
    T->getSizeRotAtDist(s,r,len);
    ofFill();
    ofPushMatrix();
    ofTranslate(paintPos);    
    for(int i=0;i<s/7+1;i++)
    {
      float rx = 1.0f*s*DrawGame::sampleNormal();
      float ry = 1.0f*s*DrawGame::sampleNormal();
      float rr = pow(DrawGame::sampleNormal(),2.0f)*1.0f;
      int GrayScale = ofRandom(0,255);
      ofSetColor(
        GrayScale,GrayScale,GrayScale,
        ofRandom(100,200));
      ofCircle(ofPoint(rx,ry,0),rr);
    }    
    ofPopMatrix();

  }

}