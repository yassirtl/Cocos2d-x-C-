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

#ifndef __Win3_H__
#define __Win3_H__



#pragma once

#include "cocos2d.h"

class Win3 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(Win3);
    
    
    
    
private:
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void addMonster(float dt);
    cocos2d::Sprite* bg;
    cocos2d::Sprite* sprite;
    void buttonPressed();
    void buttonPressed2();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setPhysicsWorld( cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    cocos2d::PhysicsWorld *sceneWorld;
    
};
    
    

#endif // __Win3_H__
