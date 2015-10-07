#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Sprite;
  enum class SpriteMood
  {
    JOY,
    LAUGH,
    PAIN,
    SAD
  };

  class Status
  {
  public:
    ofParameter<int> Lv;
    ofParameter<float> Exp;
    ofParameter<float> HP;
    ofParameter<float> HPMax;
    ofParameter<float> Ki;
    ofParameter<int> Mood;
    ofParameter<float> LvUpPowBase;
    ofParameterGroup S;

  public:    
    Status();
    Status(ofXml& X);
    virtual ~Status();

    void revive();
    void drawFace(Sprite* me);
    void intarct(Sprite* me, Sprite* tgt);
    ofParameterGroup getParameterGroup();

  private:
    Sprite* spMaster;
    string getMoodString();

    void lvUp(int dLv=1);
    
    //----------- parameter callbacks -----------//
    void LvChanged(int &L);
    void expIncreased(float &exp);
    void hpChanged(float &hp);

    //----------- get rule params ---------------//
    float getLvUpExp();
    float getMaxKi();
 

  };
}
