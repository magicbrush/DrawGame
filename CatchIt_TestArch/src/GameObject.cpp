#include "GameObject.h"
#include "Shape.h"
#include "Status.h"
#include "Control.h"
#include "Brush.h"

DrawGame::GameObject::GameObject(ofPtr<Shape> Comp)
{
  bAlive.set("bAlive",true);
  
  // create Geometry comp
  shape = Comp;

}

DrawGame::GameObject::~GameObject()
{

}

void DrawGame::GameObject::changeGeometry( 
  ofPtr<Shape> Comp )
{
  shape = Comp;
}

void DrawGame::GameObject::linkBrush( 
  ofPtr<Brush> Br )
{
  brush = Br;
}

void DrawGame::GameObject::linkStatus( 
  ofPtr<Status> S )
{
  status = S;
}

void DrawGame::GameObject::linkControl( 
  ofPtr<Control> Ctrl )
{
  control = Ctrl;
}

bool DrawGame::GameObject::isAlive()
{
  return bAlive;
}

bool DrawGame::GameObject::die()
{
  bAlive = false;
  return bAlive;
}

void DrawGame::GameObject::update()
{
  if(status.use_count()>0)
  {
    status->updateStatus(this);
  }

  if(control.use_count()>0)
  {
    control->controlling(this);
  }

  if(brush.use_count()>0)
  {
    // painting    
    
  }

}

void DrawGame::GameObject::draw()
{
  shape->draw();
}



