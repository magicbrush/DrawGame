#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "DrawGameGUI.h"

namespace DrawGame
{
	class Sprite;
  class Status;
  class GUIBase;
  class GUITextButton;
}

class ofApp : public ofBaseApp{

	public:
		ofApp();
		~ofApp();

		void setup();
		void update();
    void randGenSprite(float dt);
		void draw();
    void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();

    void retryButtonCallback(
      DrawGame::GUIEventArgs &E );
    
    void drawGameOver();
    void drawDebug();
    void myTest();

    ofVec2f WindowSize;

    bool bGameRunning;

		ofPtr<DrawGame::Sprite> sp; 
    ofPtr<DrawGame::Status> spStatus;

		vector<ofPtr<DrawGame::Sprite> > Sprites;

    ofFbo CanvasFbo;
    ofFbo EffectsFbo;
		
    map<int,bool> Keyboard;

    bool bShowDebug;   
    ofParameter<float> FPS;
    ofxPanel GUI_Debug;

    vector<ofPtr<DrawGame::GUIBase> > GUIs;
    ofPtr<DrawGame::GUITextButton> pRetryBtn;

};
