#include "DrawGameUtils.h"

namespace DrawGame
{
  void DrawGame::drawTxtByFontInRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofRectangle Rect )
  {        
    // 获得Txt以(0,0)以起点显示所处的包围盒矩形R0
    ofRectangle R0 = 
      pFont->getStringBoundingBox(Txt,0,0);
    ofVec2f Ctr(R0.getCenter()); // 矩形中心

    // 将Txt以(0,0)为中心显示所需的基准点Base
    ofVec2f Base(-Ctr.x,-Ctr.y);    
    
    // 获得从R0变换到矩形Rect的变换参数:
    // 平移量 tx,ty;
    float tx,ty;
    tx = Rect.getCenter().x;
    ty = Rect.getCenter().y;     
    // 缩放尺度sx,sy 
    float sx,sy;
    sx = Rect.getWidth()/R0.getWidth();
    sy = Rect.getHeight()/R0.getHeight();

    // 计算变换矩阵
    ofMatrix4x4 Mat;
    Mat.preMultTranslate(ofVec3f(tx,ty,0));
    Mat.preMultScale(ofVec3f(sx,sy,1.0f));   

    // 用矩阵Mat进行变换：从R0变换到Rect
    ofMultMatrix(Mat);

    //从基准点Base用pFont绘制文本Txt
    pFont->drawString(Txt,Base.x,Base.y); 

    // 进行逆变换：从Rect变换到R0
    ofMatrix4x4 MatI; // Mat的逆矩阵：实现Mat的反向变换
    MatI = Mat.getInverse();
    ofMultMatrix(MatI); // 实现逆变换
  }

  void drawTxtByFontInRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    float width, 
    float height )
  {
    ofRectangle R; // 矩形类
    // 将矩形设为中心在Pos,长宽为width和height的矩形
    R.setFromCenter(Pos,width,height); 
    drawTxtByFontInRect(Txt,pFont,R);// 嵌套调用
  }

}
