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
#include "Win1.h"
#include "game1.h"

#include "MainMenu.h"
#include "game.h"
#include "Difinitions.h"
#include<iostream>
using namespace cocos2d;
using namespace ui;
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC_EXT;
USING_NS_CC;


Scene* Win1::createScene()
{
    auto scene = Scene::createWithPhysics();
    //  this for physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    auto layer = Win1::create();
    // to edit the force of gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
       auto gravity = Vec2(0, -400.0f);
       world->setGravity(gravity);

    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool Win1::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // close button
   
    ui::Button* btnoff = ui::Button::create("btn-mini-exit.png");
    
     btnoff->setPosition( Vec2(100.f, 700.f) );
    btnoff->addTouchEventListener( CC_CALLBACK_1(Win1::menuCloseCallback, this) );
    btnoff->setScale(0.5);
     this->addChild(btnoff, 1);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //BackGround
    auto bg = Sprite::create("Level1-Win.png");
    
        // position the sprite on the center of the screen
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(bg, -1);
    
    // start button
    ui::Button* btn = ui::Button::create("btn-next-level.png");
     btn->setPosition( Vec2(visibleSize.width*0.55, visibleSize.height*0.25) );
     btn->addTouchEventListener( CC_CALLBACK_0(Win1::buttonPressed, this) );
    btn->setScale(0.4);
     this->addChild(btn, 1);
    
    ui::Button* btn2 = ui::Button::create("btn-mini-PA.png");
     btn2->setPosition( Vec2(visibleSize.width*0.4, visibleSize.height*0.241) );
     btn2->addTouchEventListener( CC_CALLBACK_0(Win1::buttonPressed2, this) );
    btn2->setScale(0.16);
     this->addChild(btn2, 1);
   
    
    this->scheduleUpdate();
    return true;
}
void Win1::buttonPressed() {
    Scene *scene = game1::createScene();
    TransitionFade *transition = TransitionFade::create(SPLASH_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}
void Win1::buttonPressed2() {
    Scene *scene = game::createScene();
    TransitionFade *transition = TransitionFade::create(SPLASH_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
    
}
void Win1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}
