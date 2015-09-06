#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

  public:
    void setup(); // 初始化
    void update(); // 更新状态
    void draw();// 绘制

    void keyPressed(int key);// 按键key按下
    void keyReleased(int key);// 按键key释放
    void mouseMoved(int x, int y ); // 鼠标移动
    void mouseDragged(int x, int y, int button);// 鼠标拖拽
    void moveCircleTo( int x, int y );
    void mousePressed(int x, int y, int button);// 鼠标键按下
    void mouseReleased(int x, int y, int button);// 鼠标键释放
    void windowResized(int w, int h); // 窗口大小改变
    void dragEvent(ofDragInfo dragInfo); // 拖动文件到窗口
    void gotMessage(ofMessage msg); // 接收到ofSendMessage()的消息
    
    ofTrueTypeFont Font; // 字体
    map<string,ofSoundPlayer> Sounds; // 音效

    // 记录键鼠状态
    map<int,bool> KeysState;
    map<int,bool> MouseKeyState;
    ofVec2f MousePos;

    bool bShowDebug; // 是否显示调试信息

    int windowSizeX, windowSizeY; //窗口尺寸
    
    // 主角的参数
    float X; // 圆形的x坐标
    float Y; // 圆形的y坐标
    float Size; // 圆形的大小		
    float Rot; // 旋转角度（度）

    
        
};
