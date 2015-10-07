#pragma  once
#ifndef $$DRAWGAMEUTILS_H$$
#define $$DRAWGAMEUTILS_H$$

#include "ofMain.h"

namespace DrawGame
{
  // 在矩形Rect中以字体pFont来显示文本Txt
  void drawTxtByFontInRect(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofRectangle Rect);
  // 以Pos为中心的宽度为width，高度为height的矩形范围内，
  // 用字体pFont显示文本Txt
  void drawTxtByFontInRect(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    float width,
    float height);
}

#endif