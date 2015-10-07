#include "Keyhole.h"
#include "Sprite.h"

namespace DrawGame
{
  bool Keyhole::contact( Sprite* a, Sprite* b )
  {
    ofVec2f PMe = a->getPos();
    float SMe = a->getSize();
    ofVec2f PT = b->getPos();
    float ST = b->getSize();
    float D = PMe.distance(PT);
    bool bFlag = D<SMe+ST;
    return bFlag;
  }

  Keyhole::Keyhole()
  {
    resetPtr();
  }

  Keyhole::~Keyhole()
  {

  }

  Status* Keyhole::getStatusPtr()
  {
    return s;
  }

  Sprite* Keyhole::getAPtr()
  {
    return a;
  }

  Sprite* Keyhole::getBPtr()
  {
    return b;
  }

  void Keyhole::match( Status* AStatus, Sprite* A, Sprite* B )
  {
    resetPtr(AStatus,A,B);
    _match(s,a,b);
  }

  void Keyhole::resetPtr( 
    Status* S/*=nullptr*/, 
    Sprite* A/*=nullptr*/, 
    Sprite* B/*=nullptr*/ )
  {
    s = S;
    a = A;
    b = B;
  }

}