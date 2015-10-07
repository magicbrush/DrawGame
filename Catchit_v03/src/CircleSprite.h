#pragma once // 1��֤ͷ�ļ�ֻ������һ��

#ifndef $$SPRITE$$ // 2�ú궨��ķ�ʽ���ô�ͷ�ļ�ֻ������һ��
#define $$SPRITE$$

#include "ofMain.h" // 3��Ҫ�õ�OF���ܣ�����������ļ�

namespace DrawGame // 4���½�������������ռ�DrawGame��
{
  enum SpriteMood // 22��ö������ʾ��ɫ������״̬
  {
    DRAWGAME_MOOD_ACTIVE, // ������
    DRAWGAME_MOOD_BORING, // ��Ȥ��
    DRAWGAME_MOOD_JOY, // ������
    DRAWGAME_MOOD_EVIL // а���
  };
  class CircleSprite // 5CircleSprite�ඨ��
  {   
  public: // 6 ���ʿ������ԣ�����
    // ******************** ��Ϊ ******************************//
    // --------------����/����-----------------//
    // 7���캯����������CircleSprite������½���ʱ��ʼ�����������
    CircleSprite(
      ofTrueTypeFont* font, // ��ʾ������������
      ofVec2f Pos = ofVec2f(0,0), // ��ʼλ��
      float size = 50.0f, // ��ʼ�ߴ�
      float rot = 0.0f, // ��ʼ����
      bool bWhite = false, // ��ɫ
      SpriteMood defaultMood = DRAWGAME_MOOD_ACTIVE); // ��ʼ��Ϊ���������ı���
    // 8����������������CircleSprite���������ʱ�����������
    // ����Ҫ�����̬�����࣬�ͽ�������������Ϊ����������
    virtual ~CircleSprite(void);

    // --------9��ʾ----------------------------//
    void draw(); 

    // -------------10��Ծ-----------------------//
    void setPosition(ofVec2f Pos); // ֱ�ӡ���Ծ����λ��Pos
    ofVec2f getPosition(); // �����ǰλ��

    // -------------11�ƶ�-----------------------//
    void move(ofVec2f Trans); // �ƶ�һ��λ����Trans

    // -------------12������С-------------------//
    void setSize(float size); // ���ô�С
    void changeSize(float deltaSize); // �ı��С
    float getSize(); // �����С

    // -------------13��ת-----------------------//
    void setRot(float degrees); //������ת�Ƕ�
    void changeRot(float deltaRot); //��תdeltaRot��
    float getRot(); // �����ת�Ƕ�

    // -------------14������ɫ-------------------//
    void setWhite(bool bWhite); // ������ɫ����false���true
    bool getbWhite(); // �����ɫ

    // -------------15�������������飩-----------//
    void setMood(SpriteMood m); // ��������
    SpriteMood getMood(); // �������

    // -------16�ж�����������Ĺ�ϵ-----------//
    bool encompass(CircleSprite& Another); // ������һ��CircleSprite����?
    bool intersect(CircleSprite& Another); // ����һ��CircleSprite���󽻲棿
    bool isSameColor(CircleSprite& Another);// ����һ��CircleSpriteͬɫ��

    // ------˽����Ϊ--------------------------//
  private: // 6���ʿ������ԣ�˽��
    void drawFill(); // ��ʾԲ��
    void drawEdge(); // ��ʾ����
    void drawFace(); // ��ʾ���飨����������ʾ��
    string getModeString(); // ����������ַ�������

    // ********����********************************************//
  private:// 6���ʿ������ԣ�˽��
    //---------17λ��----------------------------//
    float X; // Բ�ε�x����
    float Y; // Բ�ε�y����    
    //---------18��С----------------------------//
    float Size; // Բ�εĴ�С	    
    //---------19����----------------------------//
    float Rot; // ��ת�Ƕȣ��ȣ�    
    //---------20��ɫ----------------------------//
    bool White; // ɫ�ʣ��ڻ�ף�    
    //---------21����----------------------------//
    SpriteMood Mood;
    ofTrueTypeFont* pFont; // ����
  };
}


#endif
