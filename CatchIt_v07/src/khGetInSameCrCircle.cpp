#include "khGetInSameCrCircle.h"
#include "Sprite.h"
#include "Status.h"
#include "SoundEngine.h"
#include "Body.h"
#include "DrawGameDefs.h"

namespace DrawGame
{

  khGetInSameCrCircle::khGetInSameCrCircle()
  {

  }

  khGetInSameCrCircle::~khGetInSameCrCircle()
  {

  }

  void khGetInSameCrCircle::_match( Status* AStatus, Sprite* A, Sprite* B )
  {
    // precluding judgment
    if(!Keyhole::contact(A,B))return;
    bool bSameColor = (A->isWhite()==B->isWhite());
    if(!bSameColor)return;
    BodyType TTgt = B->getBody()->getBodyType();
    if(TTgt!=BodyType::CIRCLE)return;   

    // reduce B size
    float dt = ofGetLastFrameTime();
    float S = B->getSize();
    S-=10.0f*dt;
    B->setSize(S);

    // get necessary parameters
    ofVec2f PosMe = A->getPos();
    float SizeMe = A->getSize();

    ofVec2f PosTgt = B->getPos();
    float SizeTgt = B->getSize();

    float Dist = PosMe.distance(PosTgt);

    // actual judgment
    bool bDie(false);
    float dHp(0),dExp(1.0f);
    float soundSpd(1.0f),soundVol(1.0f);
    if(SizeMe>=SizeTgt)
    {
      bDie=true;
      soundSpd = 0.66f;
      soundVol = 0.1f;
    }
    else if(SizeMe<SizeTgt&&Dist<abs(SizeMe-SizeTgt))
    {
      bDie = true;     
      float SizeRatio = SizeMe/SizeTgt;
      dHp = 2+8*SizeRatio;
      dExp = 5+15*SizeRatio;
      soundSpd = 1.5f;
      soundVol = 1.0f;
    }    
    if(bDie)
    {
      B->die();
      AStatus->HP += dHp;
      AStatus->Exp += dExp;

      // to-do: display info
      float ScnSize = sqrt(ofGetWidth()*ofGetHeight());
      float dhp = int(10.0f*dHp)/10.0f;
      ofVec2f DPos = PosMe+ofVec2f(0,-SizeMe-ScnSize*0.02f);
      if(DPos.y<ScnSize/10.0f)DPos.y = ScnSize/10.0f;
      pushTextInfo(
        dhp,
        DPos,
        0.8f,
        0.01f,
        0.0f,
        "vag",18.0f,
        ofColor::yellow,
        1.0f,
        ofColor::black);

      // to-do: play audio
      SOUNDENGINE.playSound("GetScore",soundSpd,soundVol);
    }  
   
  }

  void khGetInSameCrCircle::draw()
  {
    Status* S = getStatusPtr();
    Sprite* A = getAPtr();
    Sprite* B = getBPtr();

    if(!Keyhole::contact(A,B))return;

    ofPoint PA = A->getPos();
    ofPoint PB = B->getPos();

    ofVec2f D = PA-PB;
    D *= 0.618f;

    ofPushMatrix();
    ofPushStyle();
    ofSetColor(ofColor::limeGreen);
    //ofLine(PA,PB);
    ofSetLineWidth(3.0f);
    ofDrawArrow(PB+D,PB,5.0f);
    ofSetLineWidth(1.0f);
    ofNoFill();
    ofCircle(PB,A->getSize());
    ofPopStyle();  
    ofPopMatrix();
  }


}