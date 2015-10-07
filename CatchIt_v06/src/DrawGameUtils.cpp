#include "DrawGameUtils.h"

namespace DrawGame
{
  void DrawGame::drawTxtByFontInRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofRectangle Rect )
  {        
    // ���Txt��(0,0)�������ʾ�����İ�Χ�о���R0
    ofRectangle R0 = 
      pFont->getStringBoundingBox(Txt,0,0);
    ofVec2f Ctr(R0.getCenter()); // ��������

    // ��Txt��(0,0)Ϊ������ʾ����Ļ�׼��Base
    ofVec2f Base(-Ctr.x,-Ctr.y);    
    
    // ��ô�R0�任������Rect�ı任����:
    // ƽ���� tx,ty;
    float tx,ty;
    tx = Rect.getCenter().x;
    ty = Rect.getCenter().y;     
    // ���ų߶�sx,sy 
    float sx,sy;
    sx = Rect.getWidth()/R0.getWidth();
    sy = Rect.getHeight()/R0.getHeight();

    // ����任����
    ofMatrix4x4 Mat;
    Mat.preMultTranslate(ofVec3f(tx,ty,0));
    Mat.preMultScale(ofVec3f(sx,sy,1.0f));   

    // �þ���Mat���б任����R0�任��Rect
    ofMultMatrix(Mat);

    //�ӻ�׼��Base��pFont�����ı�Txt
    pFont->drawString(Txt,Base.x,Base.y); 

    // ������任����Rect�任��R0
    ofMatrix4x4 MatI; // Mat�������ʵ��Mat�ķ���任
    MatI = Mat.getInverse();
    ofMultMatrix(MatI); // ʵ����任
  }

  void drawTxtByFontInRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    float width, 
    float height )
  {
    ofRectangle R; // ������
    // ��������Ϊ������Pos,����Ϊwidth��height�ľ���
    R.setFromCenter(Pos,width,height); 
    drawTxtByFontInRect(Txt,pFont,R);// Ƕ�׵���
  }

}
