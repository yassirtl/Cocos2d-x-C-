/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __game1_H__
#define __game1_H__



#pragma once

#include "cocos2d.h"

class game1 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(game1);
    
    
    
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void addMap(float dt);
    void addMap2(float dt);
    
private:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float) override;
    cocos2d::Sprite* monster;
    cocos2d::Sprite* monster1;
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* sprite1;
    cocos2d::Sprite* obstacles1;
    cocos2d::Sprite* spriteObstacle;
    cocos2d::Sprite* targetS;
    //cocos2d::Sprite* monster;
    void setPhysicsWorld( cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    cocos2d::PhysicsWorld *sceneWorld;
    //bool onContactBegin(cocos2d::PhysicsContact &contact );
    //void SwitchToMainMenu( float dt );
    
};
    
    

#endif // __game1_H__
