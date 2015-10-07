#pragma once

#include "ofMain.h"
#include "ofxAssets.h"
#include "Informer.h"
#include "TextNode.h"

namespace DrawGame
{
  template<typename T>
  void pushTextInfo(
    T msg,
    ofVec2f pos, 
    float duration = 0.618f,
    float delay = 0.0f,
    float zOrder = 0.0f,
    string fontName="vag",
    float FontSize=18.0f,
    ofColor CrFill = ofColor::white,
    float edgeSize = 1.0f,
    ofColor CrEdge = ofColor::black
    );
}

template<typename T>
void DrawGame::pushTextInfo( 
  T msg, 
  ofVec2f pos, 
  float duration /*= 0.618f*/, 
  float delay /*= 0.0f*/, 
  float zOrder,
  string fontName/*="vag"*/, 
  float FontSize/*=18.0f*/, 
  ofColor CrFill /*= ofColor::white*/, 
  float edgeSize /*= 1.0f*/, 
  ofColor CrEdge /*= ofColor::black */ )
{  
  ofPtr<TextNode> TN= 
    TextNode::create(
    ofToString(msg),
    &ofxAssets::font(fontName,FontSize),
    pos,
    CrFill,
    edgeSize,
    CrEdge);
  INFORMER.pushInfo(TN,duration,delay,zOrder);
}
