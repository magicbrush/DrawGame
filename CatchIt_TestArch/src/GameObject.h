#pragma once

#include "ofMain.h"
#include "DrawGameDef.h"

namespace DrawGame
{
  class Shape;
  class Status;
  class Control;
  class Brush;

  class GameObject:
    public ofBaseUpdates
  {
  public:
    GameObject(ofPtr<Shape> Comp);
    ~GameObject();
   
    void changeGeometry(ofPtr<Shape> Comp);    
    void linkStatus(ofPtr<Status> S);
    void linkControl(ofPtr<Control> Ctrl);
    void linkBrush(ofPtr<Brush> Br);

    bool isAlive();
    bool die();

    virtual void update() final;
    void draw();

  private:
    ofPtr<Shape> shape;
    ofPtr<Status> status;
    ofPtr<Control> control;
    ofPtr<Brush> brush;    
    
    ofParameter<bool> bAlive;
  };

}