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
#include "cocos2d.h"
#include "Win3.h"
#include "game.h"
#include "game2.h"
#include "game3.h"
#include "MainMenu.h"
#include "Difinitions.h"
#include<iostream>
using namespace cocos2d;
using namespace ui;
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC_EXT;
USING_NS_CC;


Scene* Win3::createScene()
{
    auto scene = Scene::createWithPhysics();
    //  this for physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    auto layer = Win3::create();
    // to edit the force of gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
       auto gravity = Vec2(0, -400.0f);
       world->setGravity(gravity);

    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool Win3::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // close button
   
    ui::Button* btnoff = ui::Button::create("btn-mini-exit.png");
    
     btnoff->setPosition( Vec2(100.f, 700.f) );
    btnoff->addTouchEventListener( CC_CALLBACK_1(Win3::menuCloseCallback, this) );
     this->addChild(btnoff, 1);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //BackGround
    auto bg = Sprite::create("Level3-Win.png");
    
        // position the sprite on the center of the screen
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(bg, -1);
    
    // start button
    ui::Button* btn = ui::Button::create("btn-next-level.png");
     btn->setPosition( Vec2(visibleSize.width*0.55, visibleSize.height*0.3) );
     btn->addTouchEventListener( CC_CALLBACK_0(Win3::buttonPressed, this) );
    btn->setScale(0.35);
     this->addChild(btn, 1);
    
    ui::Button* btn2 = ui::Button::create("btn-mini-PA.png");
     btn2->setPosition( Vec2(visibleSize.width*0.42, visibleSize.height*0.29) );
     btn2->addTouchEventListener( CC_CALLBACK_0(Win3::buttonPressed2, this) );
    btn2->setScale(0.14);
     this->addChild(btn2, 1);
   
    
    this->scheduleUpdate();
    return true;
}
void Win3::buttonPressed() {
    Scene *scene = game3::createScene();
    TransitionFade *transition = TransitionFade::create(SPLASH_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}
void Win3::buttonPressed2() {
    Scene *scene = game2::createScene();
    TransitionFade *transition = TransitionFade::create(SPLASH_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}
void Win3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
