#include "DrawGameUtils.h"

namespace DrawGame
{
  void DrawGame::drawScaledStringByFont( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofRectangle Rect )
  {
    // debug    
    float sh = pFont->stringHeight(Txt);
    float sw = pFont->stringWidth(Txt);

    ofRectangle R0(0,0,sw,-sh);   
   
    ofVec2f Trans = Rect.getCenter()-R0.getCenter();
    float sx,sy;
    sx = Rect.getWidth()/R0.getWidth();
    sy = -Rect.getHeight()/R0.getHeight();
        
    ofMatrix4x4 Mat;
    Mat.translate(-R0.getCenter());
    Mat.scale(sx,sy,1.0f);
   // Mat.translate(Rect.getCenter()/ofVec2f(sx,sy));
    Mat.translate(Rect.getCenter());
    ofMultMatrix(Mat);
    pFont->drawString(Txt,0,0); 
    ofMatrix4x4 MatI;
    MatI = Mat.getInverse();
    ofMultMatrix(MatI);

  }

  void drawScaledStringByFont( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    float width, 
    float height )
  {
    ofRectangle R;
    R.setFromCenter(Pos,width,height);
    drawScaledStringByFont(Txt,pFont,R);
  }

}
