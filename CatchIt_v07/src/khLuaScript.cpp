#include "khLuaScript.h"
#include "Sprite.h"
#include "Status.h"
#include "SoundEngine.h"
#include "DrawGameDefs.h"

namespace DrawGame
{ 
  ofPtr<ofxLua> khLuaScript::L;
  set<ofFile> khLuaScript::ScriptFiles;
 
  khLuaScript::khLuaScript(
    string LuaFile,string MatchFcn, string DrawFcn)
  {
    luaFile = ofFile(LuaFile);
    matchFcn = MatchFcn;
    drawFcn = DrawFcn; 
    checkAndInitOfxLua();
  }

  void khLuaScript::draw()
  {
    // precluding judgment
    if(!Keyhole::contact(getAPtr(),getBPtr()))return;

    L->scriptFcn(drawFcn);
  }

  void khLuaScript::_match( Status* S, Sprite* Src, Sprite* Tgt )
  {
    // precluding judgment
    if(!Keyhole::contact(Src,Tgt))return;
    
    checkAndInitOfxLua();
    resetLuaOutput();
    
    // input Lua state    
    inputStatusProp(S,L.get());
    inputSpriteProp(Src,L.get(),"S_");
    inputSpriteProp(Tgt,L.get(),"T_");

    // call Lua function
    L->scriptFcn(matchFcn);

    // read Lua state        
    readSpriteProp(Src,L.get(),"S_");
    readSpriteProp(Tgt,L.get(),"T_"); 
    readStatusProp(S,L.get());

    // audio-visual feedback
    dispInfo();
    playSound();
  }
  
  void khLuaScript::inputStatusProp( Status* st, ofxLua* Lua )
  {
    Lua->setFloat("Exp",st->Exp);
    Lua->setFloat("HP",st->HP);
    Lua->setFloat("HPMax",st->HPMax);
    Lua->setFloat("Ki",st->Ki);
    /*Lua->setFloat("Lv",st->Lv);
    cout << "Input Lv:" << st->Lv << endl;*/
    Lua->setFloat("Mood",st->Mood);
  }

  void khLuaScript::readStatusProp( Status* st, ofxLua* Lua )
  {
    st->HP = Lua->getFloat("HP",st->HP);     
    st->HPMax = Lua->getFloat("HPMax",st->HPMax);    
    st->Ki = Lua->getFloat("Ki",st->Ki);
    /*st->Lv = Lua->getFloat("Lv",st->Lv);
    cout << "Read Lv:" << st->Lv << endl;*/
    st->Mood = Lua->getFloat("Mood",st->Mood);
    st->Exp = Lua->getFloat("Exp",st->Exp);
  }

  void khLuaScript::inputSpriteProp( Sprite* sp, ofxLua* Lua, string Pref )
  {
    ofVec2f PosSrc = sp->getPos();
    Lua->setFloat(Pref+"PosX",PosSrc.x);
    Lua->setFloat(Pref+"PosY",PosSrc.y);
    Lua->setFloat(Pref+"Size",sp->getSize());
    Lua->setFloat(Pref+"Rot",sp->getRot());
    Lua->setBool(Pref+"bWhite",sp->isWhite());
    Lua->setBool(Pref +"Alive",sp->isAlive());
  }

  void khLuaScript::readSpriteProp( Sprite* sp, ofxLua* Lua, string Pref )
  {
    ofVec2f PosSrc(sp->getPos());
    PosSrc.x = Lua->getFloat(Pref+"PosX",PosSrc.x);
    PosSrc.y = Lua->getFloat(Pref+"PosY",PosSrc.y);
    sp->setPos(PosSrc);
    float S(sp->getSize());
    S = Lua->getFloat(Pref+"Size",S);
    sp->setSize(S);
    float R(sp->getRot());
    R = Lua->getFloat(Pref+"Rot",R);
    sp->setRot(R);
    bool bW(sp->isWhite());
    bW = Lua->getBool(Pref+"bWhite",bW);
    sp->setWhite(bW);
    bool bA(sp->isAlive());
    bA = Lua->getBool(Pref+"Alive",bA);
    sp->setAlive(bA);    
  }

  void khLuaScript::reloadScript()
  {
    bool bScript = L->doScript(luaFile.getAbsolutePath());
  }

  void khLuaScript::ofxLuaClear()
  {
    L->clear();
  }

  void khLuaScript::checkAndInitOfxLua()
  {
    if(L.use_count()==0)L.reset(new ofxLua());
         
    bool toLoadScript = 
      (ScriptFiles.find(luaFile)==ScriptFiles.end());
    if(!L->isInited())
    {
      L->init(false,true,true);
      toLoadScript = true;
    }
    if(toLoadScript)
    {
      ScriptFiles.insert(luaFile);
      bool bScript = L->doScript(luaFile.getAbsolutePath());     
    }    
  }

  void khLuaScript::resetLuaOutput()
  {
    // info output
    L->setString("Info","");
    L->setFloat("InfoX",0);
    L->setFloat("InfoY",0);
    L->setFloat("IDuration",0.7f);
    L->setFloat("IDelay",0.02f);
    L->setFloat("IZOrder",0.0f);
    L->setString("IFontName","vag");
    L->setFloat("IFontSize",18.0f);
    for(int i=0;i<4;i++)
      L->setFloat("CF"+ofToString(i),255);
    L->setFloat("IEdgeSize",1.0f);
    for(int i=0;i<3;i++)
      L->setFloat("CF"+ofToString(i),0);
    L->setFloat("CF3",255);
    // sound output
    L->setBool("SoundPlay",false);
    L->setString("SoundName","");
    L->setFloat("SoundSpd",1.0f);
    L->setFloat("SoundVol",1.0f);
  }

  void khLuaScript::dispInfo()
  {
    // disp info
    string Info("");
    Info = L->getString("Info",Info);
    if(!Info.empty())
    {
      float IPosX(0),IPosY(0);
      float IDuration(0);
      float IDelay(0);
      float IZOrder(0);
      string IFontName("");
      float IFontSize(0);
      int CF[4] = {255,255,255,255};
      float IEdgeSize = 1.0f;
      int CE[4] = {0,0,0,255};

      IPosX = L->getFloat("InfoX");
      IPosY = L->getFloat("InfoY");
      IDuration = L->getFloat("IDuration");
      IDelay = L->getFloat("IDelay");
      IZOrder = L->getFloat("IZOrder");
      IFontName = L->getString("IFontName");
      IFontSize = L->getFloat("IFontSize");
      for(int i=0;i<4;i++)
        CF[i]=L->getFloat("CF"+ofToString(i));
      IEdgeSize = L->getFloat("IEdgeSize");
      for(int i=0;i<4;i++)
        CE[i]=L->getFloat("CE"+ofToString(i));

      pushTextInfo(
        Info,
        ofVec2f(IPosX,IPosY),
        IDuration,
        IDelay,
        IZOrder,
        IFontName,
        IFontSize,
        ofColor(CF[0],CF[1],CF[2],CF[3]),
        IEdgeSize,
        ofColor(CE[0],CE[1],CE[2],CE[3]));
    }
  }

  void khLuaScript::playSound()
  {
    // play sound
    bool bSound(false);
    bSound = L->getBool("SoundPlay",bSound);
    if(bSound)
    {
      string SName("");
      SName = L->getString("SoundName",SName);
      float SSpd(1.0f);
      SSpd = L->getFloat("SoundSpd",SSpd);
      float SVol(1.0f);
      SVol = L->getFloat("SoundVol",SVol);
      SOUNDENGINE.playSound(SName,SSpd,SVol);
    }
  }

}