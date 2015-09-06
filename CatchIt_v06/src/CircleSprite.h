#pragma once // ��֤ͷ�ļ�ֻ������һ��

#ifndef $$SPRITE$$
#define $$SPRITE$$

#include "ofMain.h"

namespace DrawGame
{
  enum SpriteMood
  {
    DRAWGAME_MOOD_ACTIVE,
    DRAWGAME_MOOD_BORING,
    DRAWGAME_MOOD_JOY,
    DRAWGAME_MOOD_EVIL
  };

	class CircleSprite
	{   
	public:
		CircleSprite(
      ofTrueTypeFont* font,
			ofVec2f Pos = ofVec2f(0,0),
			float size = 50.0f,			
			float rot = 0.0f,
			bool bWhite = false,
      SpriteMood defaultMood = DRAWGAME_MOOD_ACTIVE);
    virtual ~CircleSprite(void);

    ofVec2f getPosition();
		void jumpTo(ofVec2f Pos);
    void moveTo(ofVec2f Pos);

    void addTrace();

    void move(ofVec2f Trans);
		void setSize(float size);
    float getSize();
    void changeSize(float deltaSize);		
		void setRot(float degrees);	
    float getRot();
    void changeRot(float deltaRot);
		void setWhite(bool bWhite);
    bool getbWhite();
    void setMood(SpriteMood m);
    SpriteMood getMood();

    bool encompass(CircleSprite& Another);
    bool intersect(CircleSprite& Another);
    bool isSameColor(CircleSprite& Another);

    void draw();
   
    void paint();

  private:
    void drawFill();
    void drawEdge();
    void drawFace();
    string getModeString();
    void initTrace();
    void clearTrace();
    
	private:
		float X; // Բ�ε�x����
		float Y; // Բ�ε�y����
		float Size; // Բ�εĴ�С		
		float Rot; // ��ת�Ƕȣ��ȣ�
		bool White; // ɫ�ʣ��ڻ�ף�
    SpriteMood Mood;// ����
    ofTrueTypeFont* pFont; // ����  
    ofPolyline Trace; // �켣

	};
}

#endif
