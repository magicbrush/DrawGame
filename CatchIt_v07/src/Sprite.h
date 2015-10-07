#pragma once

#include "ofMain.h"

namespace DrawGame
{
  class Status;
  class Keyhole;
  class Tracer;
  class Brush;
  class Body; 

  class Sprite:    
    public ofBaseUpdates
  { 
  public:
    Sprite(      
      bool _white=true,
      ofVec2f _pos = ofVec2f(0,0),
      float _size = 40.0f,
      float _rot = 0.0f,
      ofPtr<Keyhole> K = ofPtr<Keyhole>(),
      ofPtr<Status> S = ofPtr<Status>());
    virtual ~Sprite();

    bool isAlive() const;
    void die();    
    void setAlive(bool bA);
    ofParameter<bool> isWhite() const;
    void setWhite(bool val);
   
    ofParameter<ofVec2f> getPos() const;
    void jumpToPos(ofVec2f val);    
    void moveToPos(ofVec2f pos);
    void setPos(ofVec2f pos);
    ofParameter<float> getSize() const;
    void setSize(float val);
    void changeSize(float dSize);
    ofParameter<float> getRot() const;
    void setRot(float val);
    void changeRot(float dRot);

    void changeBody(ofPtr<Body> R);
    ofPtr<Body> getBody();
    void linkStatus(ofPtr<Status> S);
    void linkKeyhole(ofPtr<Keyhole> KH);
    ofPtr<Keyhole> getKeyhole();
    void linkBrush(ofPtr<Brush> Br);
    void linkEffectBr(ofPtr<Brush> Br);
    
    virtual void update();
    void draw();
    void drawEffect();
    virtual ofParameterGroup getParameterGroup(); 

  private:
    bool bAlive;    
    
    ofParameter<bool> bWhite;    
    ofParameter<ofVec2f> Pos;   
    ofParameter<float> Size;    
    ofParameter<float> Rot;  

    ofPtr<Body> body;
    ofPtr<Status> status;
    ofPtr<Keyhole> keyhole;
    ofPtr<Tracer> tracer;
    ofPtr<Brush> brush;
    ofPtr<Brush> effectBr;
    
    ofParameterGroup parameters;

  private:
    static set<Sprite*> AllSprites;
  };
}
