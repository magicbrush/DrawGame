#include "Informer.h"

namespace DrawGame
{
  Informer::Informer()
  {
    timeLast = ofGetElapsedTimef();
  }

  Informer::~Informer()
  {}
  
  void Informer::update()
  {
    float timeNow = ofGetElapsedTimef();
    float dt = timeNow - timeLast;

    map<float,InfoStruct>::iterator it;
    for(it=I.begin();it!=I.end();it++)
    {
      if(it->second.duration<=0.0f)
      {
        map<float,InfoStruct>::iterator it2 = it;        
        I.erase(it2);
        break;
      }
    }
    
    for(auto &info:I)
    {
      InfoStruct& M = info.second;      
      if(M.delay>0)
      {
        M.delay -= dt;
      }
      else
      {
        float Dt = dt*M.speed;
        M.duration -= M.speed*M.delay;
        M.delay = 0.0f;
        M.duration -= Dt;
        M.iNode->draw();
      }
    }

    timeLast = timeNow;
  }

  void Informer::draw( float x, float y )
  {
    float wd = ofGetWidth();
    float ht = ofGetHeight();
    draw(x,y,wd,ht);
  }

  void Informer::draw( 
    float x, float y, float w, float h )
  {
    ofPushView();
    ofViewport(x,y,w,h);
    for(auto &info:I)
    {
      info.second.iNode->draw();
    }
    ofPopView();
  }

  float Informer::getHeight()
  {
    return ofGetWidth();
  }

  float Informer::getWidth()
  {
    return ofGetHeight();
  }

  void Informer::pushInfo( 
    ofPtr<ofNode> Info, 
    float duration /*= 1.0f*/, 
    float delay /*= 0.0f*/, 
    float zOrder /*= 0.0f*/, 
    float speed /*= 1.0f*/ )
  {
    speed = ofClamp(speed,0.01,100.0f);
    while(I.find(zOrder)!=I.end())
    {
      zOrder += 0.0000001f;
    }
    InfoStruct MSG;
    MSG.iNode = Info;
    MSG.duration = duration;
    MSG.delay = delay;
    MSG.speed = speed;
    I[zOrder] = MSG;
  }
}