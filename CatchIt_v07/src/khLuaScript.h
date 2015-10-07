#pragma once

#include "ofMain.h"
#include "Keyhole.h"
#include "ofxLua.h"

namespace DrawGame
{
  class khLuaScript:
    public Keyhole
  { 
  public:
    khLuaScript(
      string LuaFile, 
      string MatchFcn, 
      string DrawFcn);

    void checkAndInitOfxLua();

    void reloadScript();
    virtual void draw() final;

    static void ofxLuaClear();

  protected:
    virtual void _match( 
      Status* S, Sprite* Src, Sprite* Tgt ) final;

    void playSound();

    void dispInfo();

    void resetLuaOutput();

  private:
    void inputStatusProp(
      Status* st, ofxLua* Lua);
    void readStatusProp(
      Status* st, ofxLua* Lua);
    void inputSpriteProp(
      Sprite* sp, ofxLua* Lua, string Pref);
    void readSpriteProp(
      Sprite* sp, ofxLua* Lua, string Pref);

  private:  
    ofFile luaFile;
    string matchFcn,drawFcn;

    static ofPtr<ofxLua> L;
    static set<ofFile> ScriptFiles;
  };
}
