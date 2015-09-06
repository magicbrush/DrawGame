#pragma  once
#ifndef $$DRAWGAMEUTILS_H$$
#define $$DRAWGAMEUTILS_H$$

#include "ofMain.h"

namespace DrawGame
{
  void drawScaledStringByFont(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofRectangle Rect);
  void drawScaledStringByFont(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    float width,
    float height);

}

#endif