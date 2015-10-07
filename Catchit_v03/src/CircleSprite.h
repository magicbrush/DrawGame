#pragma once // 1保证头文件只被编译一次

#ifndef $$SPRITE$$ // 2用宏定义的方式，让此头文件只被编译一次
#define $$SPRITE$$

#include "ofMain.h" // 3需要用到OF功能，必须包含此文件

namespace DrawGame // 4将新建的类放在命名空间DrawGame下
{
  enum SpriteMood // 22用枚举来表示角色的情绪状态
  {
    DRAWGAME_MOOD_ACTIVE, // 积极的
    DRAWGAME_MOOD_BORING, // 无趣的
    DRAWGAME_MOOD_JOY, // 欢快了
    DRAWGAME_MOOD_EVIL // 邪恶的
  };
  class CircleSprite // 5CircleSprite类定义
  {   
  public: // 6 访问控制属性：公开
    // ******************** 行为 ******************************//
    // --------------构造/析构-----------------//
    // 7构造函数，用于在CircleSprite类对象新建立时初始化对象的属性
    CircleSprite(
      ofTrueTypeFont* font, // 显示表情的字体对象
      ofVec2f Pos = ofVec2f(0,0), // 初始位置
      float size = 50.0f, // 初始尺寸
      float rot = 0.0f, // 初始方向
      bool bWhite = false, // 黑色
      SpriteMood defaultMood = DRAWGAME_MOOD_ACTIVE); // 初始化为”积极“的表情
    // 8析构函数，用于在CircleSprite类对象消除时进行清除操作
    // 多需要定义多态的子类，就将析构函数定义为虚析构函数
    virtual ~CircleSprite(void);

    // --------9显示----------------------------//
    void draw(); 

    // -------------10跳跃-----------------------//
    void setPosition(ofVec2f Pos); // 直接”跳跃“到位置Pos
    ofVec2f getPosition(); // 输出当前位置

    // -------------11移动-----------------------//
    void move(ofVec2f Trans); // 移动一个位移量Trans

    // -------------12调整大小-------------------//
    void setSize(float size); // 设置大小
    void changeSize(float deltaSize); // 改变大小
    float getSize(); // 输出大小

    // -------------13旋转-----------------------//
    void setRot(float degrees); //设置旋转角度
    void changeRot(float deltaRot); //旋转deltaRot度
    float getRot(); // 输出旋转角度

    // -------------14设置颜色-------------------//
    void setWhite(bool bWhite); // 设置颜色：黑false或白true
    bool getbWhite(); // 输出颜色

    // -------------15设置情绪（表情）-----------//
    void setMood(SpriteMood m); // 设置情绪
    SpriteMood getMood(); // 输出情绪

    // -------16判定与其他对象的关系-----------//
    bool encompass(CircleSprite& Another); // 包含另一个CircleSprite对象?
    bool intersect(CircleSprite& Another); // 与另一个CircleSprite对象交叉？
    bool isSameColor(CircleSprite& Another);// 与另一个CircleSprite同色？

    // ------私有行为--------------------------//
  private: // 6访问控制属性：私有
    void drawFill(); // 显示圆形
    void drawEdge(); // 显示边线
    void drawFace(); // 显示表情（根据情绪显示）
    string getModeString(); // 获得情绪的字符串描述

    // ********属性********************************************//
  private:// 6访问控制属性：私有
    //---------17位置----------------------------//
    float X; // 圆形的x坐标
    float Y; // 圆形的y坐标    
    //---------18大小----------------------------//
    float Size; // 圆形的大小	    
    //---------19方向----------------------------//
    float Rot; // 旋转角度（度）    
    //---------20颜色----------------------------//
    bool White; // 色彩（黑或白）    
    //---------21情绪----------------------------//
    SpriteMood Mood;
    ofTrueTypeFont* pFont; // 字体
  };
}


#endif
