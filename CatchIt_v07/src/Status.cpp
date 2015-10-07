#include "Status.h"
#include "Sprite.h"
#include "DrawGameUtils.h"
#include "Keyhole.h"
#include "SoundEngine.h"
#include "DrawGameDefs.h"


namespace DrawGame
{

  Status::Status():
    spMaster(nullptr)
  {
    S.setName("Status");
    S.add(Lv.set("Lv",1,1,100));
    Lv.addListener(this,&Status::LvChanged);
    S.add(Exp.set("Exp",0,0,getLvUpExp()));
    Exp.addListener(this,&Status::expIncreased); 
    S.add(HPMax.set("HPMax",100.0f,0,10000.0f));
    S.add(HP.set("HP",100,0,HPMax));   
    HP.addListener(this,&Status::hpChanged);   
    S.add(Ki.set("Ki",0,0,getMaxKi()));
    S.add(Mood.set("Mood",0,0,3));   
    S.add(LvUpPowBase.set("LvUpPowBase",1.2f,1.0f,2.0f));   
  }

  Status::Status( ofXml& X )
  {
    X.deserialize(S);
  }

  Status::~Status()
  {

  }

  void Status::intarct( Sprite* me, Sprite* tgt )
  {   
    spMaster = me;
    ofPtr<Keyhole> kh = tgt->getKeyhole();
    kh->match(this,me,tgt);   
  }

  std::string Status::getMoodString()
  {
    string MoodS;
    int M = Mood;
    SpriteMood curMood = (SpriteMood)M;
    switch (curMood)
    {
    case DrawGame::SpriteMood::JOY:
      MoodS= "^_^";
      break;
    case DrawGame::SpriteMood::LAUGH:
      MoodS = "^o^";
      break;
    case DrawGame::SpriteMood::PAIN:
      MoodS = "*_*";
      break;
    case DrawGame::SpriteMood::SAD:
      MoodS = "T_T";
      break;
    default:
      break;
    }
    return MoodS;
  }

  ofParameterGroup Status::getParameterGroup()
  {
    return S;
  }

  void Status::LvChanged( int &L )
  {   
    Lv = ofClamp(Lv,Lv.getMin(),Lv.getMax());   
  }

  void Status::expIncreased( float &exp )
  {
    if(exp>=Exp.getMax())
    {
      lvUp(1);      
    }
  }

  void Status::hpChanged( float &hp )
  {
    HP = ofClamp(HP,HPMax.getMin(),HPMax);
  }

  float Status::getLvUpExp()
  {
    float expThres = 1000*pow(LvUpPowBase,Lv-1);
    return expThres;
  }

  float Status::getMaxKi()
  {
    float mKi = 100 + 20.0f*Lv;
    return mKi;
  }

  void Status::drawFace( Sprite* me )
  {
    ofPoint Pos = me->getPos();
    float S = me->getSize();
  }

  void Status::revive()
  {
    HP = HPMax;
    Mood = int(SpriteMood::JOY);
  }

  void Status::lvUp( int dLv/*=1*/ )
  {
    Lv = Lv+dLv;
   
    float expMax = Exp.getMax();
    Exp = Exp-expMax;
    float LvUpExpTHres = getLvUpExp();
    Exp.setMax(LvUpExpTHres);  

    HPMax += 20.0f;
    HP.setMax(HPMax);
    HP = HPMax;    

    // info
    if(spMaster!=nullptr)
    {
      ofVec2f Pos = spMaster->getPos();
      float scnSize = sqrt(ofGetWidth()*ofGetHeight());
      Pos.y -= scnSize/15.0f + spMaster->getSize();
      if(Pos.y<scnSize/10.0f)
      {
        Pos.y = scnSize/10.0f;
      }
      string Msg = "Level Up!";
       pushTextInfo(
         Msg,
         Pos,
         1.5f,0.01f,1.0f,
         "vag",30.0f,
         ofColor::gold,
         2.0f,
         ofColor::black);
    }   

    // sound
    SOUNDENGINE.playSound("Strengthen");
  }

}