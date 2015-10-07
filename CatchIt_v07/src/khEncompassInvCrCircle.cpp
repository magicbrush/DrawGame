#include "khEncompassInvCrCircle.h"
#include "Sprite.h"
#include "Status.h"
#include "SingletonTemplate.h"
#include "SoundEngine.h"
#include "Body.h"

namespace DrawGame
{

  khEncompassInvCrCircle::khEncompassInvCrCircle()
  {

  }

  khEncompassInvCrCircle::~khEncompassInvCrCircle()
  {

  }

  void khEncompassInvCrCircle::_match( Status* AStatus, Sprite* A, Sprite* B )
  {
    // precluding judgment
    if(!Keyhole::contact(A,B))return;
    bool bSameColor = (A->isWhite()==B->isWhite());
    if(bSameColor)return;
    BodyType TTgt = B->getBody()->getBodyType();
    if(TTgt!=BodyType::CIRCLE)return;   

    // increase B size
    float dt = ofGetLastFrameTime();
    float S = B->getSize();
    S+=50.0f*dt;
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
    if(SizeMe<=SizeTgt)
    {
      bDie=true;
      dHp = -5-SizeMe/10;
      dExp = 3;
      SOUNDENGINE.playSound("Shrink");
    }
    else if(SizeMe>SizeTgt&&Dist<abs(SizeMe-SizeTgt))
    {
      bDie = true;     
      float SizeRatio = SizeTgt/SizeMe;
      dHp = 1+2*SizeRatio;
      dExp = 10+25*SizeRatio;
      SOUNDENGINE.playSound("Step");
    }    
    if(bDie)
    {
       B->die();
       AStatus->HP += dHp;
       AStatus->Exp += dExp;

      // to-do: display info
     
    }
   
   
  }

  void khEncompassInvCrCircle::draw()
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