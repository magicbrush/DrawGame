#pragma  once
#ifndef $$DRAWGAMEUTILS_H$$
#define $$DRAWGAMEUTILS_H$$

#include "ofMain.h"

namespace DrawGame
{
  // �ھ���Rect��������pFont����ʾ�ı�Txt
  void drawScaledStringByFont(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofRectangle Rect);
  // ��PosΪ���ĵĿ��Ϊwidth���߶�Ϊheight�ľ��η�Χ�ڣ�
  // ������pFont��ʾ�ı�Txt
  void drawScaledStringByFont(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    float width,
    float height);
}

#endif