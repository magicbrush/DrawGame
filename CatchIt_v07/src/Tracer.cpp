#include "Tracer.h"

namespace DrawGame
{

  void Tracer::draw()
  {
    T.XY.draw();
  }

  void Tracer::trace( ofVec2f Pos,float Size, float Rot )
  {
    float tNow = ofGetElapsedTimef();    
    T.XY.curveTo(Pos);
    int num = T.XY.size();    
    if(num<2)
    {
      T.TimeLen.curveTo(ofVec2f(tNow,0),8);
    }
    else
    {
      float Len = T.XY.getLengthAtIndex(num);
      T.TimeLen.curveTo(ofVec2f(tNow,Len),8);
    }
    T.SizeRot.curveTo(Size,Rot);
  }

  void Tracer::traceClear()
  {
    T.XY.clear();
    T.TimeLen.clear();
    T.SizeRot.clear();
  }

  float Tracer::getTotalLen()
  {
    int num = T.XY.size();
    if(num<2)return 0.0f;
    float len = T.XY.getLengthAtIndex(num-1);
    return len;
  }

  ofVec2f Tracer::getPosAtLen(float d)
  {
    ofVec2f P = T.XY.getPointAtLength(d);
    return P;
  }

  float Tracer::getSpdAtDist(float d)
  {
    float idf = T.XY.getIndexAtLength(d);   
    ofVec3f TgTD = T.TimeLen.getTangentAtIndex(idf);

    float spd = TgTD.y/TgTD.x;
    return spd;
  }

  ofVec2f Tracer::getVelocityAtLen(float d)
  {
    float idf = T.XY.getIndexAtLength(d);
    ofVec3f TgXY = T.XY.getTangentAtIndexInterpolated(idf);
    float spd = getSpdAtDist(d);
    ofVec2f Vel = TgXY*spd;
    return Vel;
  }

  float Tracer::getSizeAtDist( float d )
  {
    float idf = T.XY.getIndexAtLength(d);
    ofVec2f SR = T.SizeRot.getPointAtIndexInterpolated(idf);
    return SR.x;
  }

  float Tracer::getRotAtDist( float d )
  {    
    float idf = T.XY.getIndexAtLength(d);
    ofVec2f SR = T.SizeRot.getPointAtIndexInterpolated(idf);
    return SR.y;
  }

  void Tracer::getSizeRotAtDist( float &size, float &rot, float d )
  {
    float idf = T.XY.getIndexAtLength(d);
    ofVec2f SR = T.SizeRot.getPointAtIndexInterpolated(idf);
    size = SR.x;
    rot = SR.y;
  }

}