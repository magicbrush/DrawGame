#include "Sprite.h"
#include "DrawGameUtils.h"
#include "MeshPrototypes.h"
#include "Status.h"
#include "Keyhole.h"
#include "Tracer.h"
#include "Brush.h"
#include "Body.h"
#include "bdCircle.h"

namespace DrawGame
{
  set<Sprite*> Sprite::AllSprites;

  Sprite::Sprite(     
    bool _white /*=true*/, 
    ofVec2f _pos /*= ofVec2f(0,0)*/, 
    float _size /*= 40.0f*/, 
    float _rot /*= 0.0f*/,
    ofPtr<Keyhole> K,
    ofPtr<Status> S):
  bAlive(true),
  status(S),
  keyhole(K)
  {
    parameters.setName("Sprite");
   
    parameters.add(bWhite.set("bWhite",_white));    
    parameters.add(
      Pos.set("Position",_pos,ofVec2f(-1024),ofVec2f(1024)));
    parameters.add(
      Size.set("Size",_size,5.0f,1024.0f));
    parameters.add(
      Rot.set("Rot",_rot,-360.0f,360.0f));    

    body.reset(new bdCircle(this));
    tracer.reset(new Tracer);

    AllSprites.insert(this);
  }

  Sprite::~Sprite()
  {    
    AllSprites.erase(this);
  }

  bool Sprite::isAlive() const
  {
    return bAlive;
  }

  void Sprite::die()
  {
    bAlive = false;
  }

  ofParameter<bool> Sprite::isWhite() const
  {
    return bWhite;
  }

  void Sprite::setWhite( bool val )
  {
    bWhite = val;
  }

  void Sprite::setRot( float val )
  {
    Rot = val;
  }

  ofParameter<float> Sprite::getRot() const
  {
    return Rot;
  }

  void Sprite::setSize( float val )
  {
    Size = val;
  }

  ofParameter<float> Sprite::getSize() const
  {
    return Size;
  }

  void Sprite::jumpToPos( ofVec2f val )
  {
    Pos = val;
    tracer->traceClear();
    if(brush.use_count()>0)brush->reset();
    if(effectBr.use_count()>0)effectBr->reset();
  }
  
  void Sprite::moveToPos( ofVec2f pos )
  {
    Pos = pos;
    tracer->trace(Pos,Size,Rot);
  }

  ofParameter<ofVec2f> Sprite::getPos() const
  {
    return Pos;
  }

  void Sprite::update()
  {
    body->updateMesh();

    if(brush.use_count()>0)
    {
      brush->paint(tracer.get());
    }

    if(status.use_count()>0)
    {
      for(auto obj:AllSprites)
      {
        Sprite* spPtr = &(*obj);
        if(spPtr==this||spPtr->getKeyhole().use_count()==0)continue;
        status->intarct(this,spPtr);
      }      
    }
  }

  void Sprite::draw()
  {
    ofPushStyle();
    ofSetColor(ofColor::green);
    ofSetLineWidth(2.0f);
    tracer->draw();
    ofPopStyle();

    body->render();

    if(keyhole.use_count()>0)
    {
      keyhole->draw();
    }
  }

  ofParameterGroup Sprite::getParameterGroup()
  {
    parameters.clear();    
    parameters.add(bWhite);
    parameters.add(Pos);
    parameters.add(Size);
    parameters.add(Rot);
    if(status.use_count()>0)
    {
      ofParameterGroup pstatus = status->getParameterGroup();
      parameters.add(pstatus);
    }
    return parameters;
  }
  
  void Sprite::linkStatus( ofPtr<Status> S )
  {
    status = S;
  }

  void Sprite::linkKeyhole( ofPtr<Keyhole> KH )
  {
    keyhole = KH;
  }

  ofPtr<Keyhole> Sprite::getKeyhole()
  {
    return keyhole;
  }

  void Sprite::setAlive( bool bA )
  {
    bAlive = bA;
  }

  void Sprite::linkBrush( ofPtr<Brush> Br )
  {
    brush = Br;
  }

  void Sprite::changeSize( float dSize )
  {
    Size += dSize;
    Size = ofClamp(Size,Size.getMin(),Size.getMax());
  }

  void Sprite::changeRot( float dRot )
  {
    Rot += dRot;
    Rot = ofWrapDegrees(Rot);
  }

  void Sprite::linkEffectBr( ofPtr<Brush> Br )
  {
    effectBr = Br;
  }

  void Sprite::drawEffect()
  {
    if(effectBr.use_count()>0)
    {
      effectBr->paint(tracer.get());
    }
  }

  void Sprite::changeBody( ofPtr<Body> R )
  {
    body = R;
  }

  ofPtr<Body> Sprite::getBody()
  {
    return body;
  }

  void Sprite::setPos( ofVec2f pos )
  {
    Pos = pos;
  }

}