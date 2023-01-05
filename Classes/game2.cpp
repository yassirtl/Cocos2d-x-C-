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

#include "game2.h"
#include <string>
#include <string.h>
#include<iostream>
#include "Win3.h"
#include "Lose3.h"
using namespace cocos2d;
USING_NS_CC;
//

Scene* game2::createScene()
{
    auto scene = Scene::createWithPhysics();
    //  this for physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    auto layer = game2::create();
    // to edit the force of gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
       auto gravity = Vec2(0, -220.0f);
       world->setGravity(gravity);

    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool game2::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // close button
    ui::Button* btnoff = ui::Button::create("btn-mini-exit.png");
     btnoff->setPosition( Vec2(100.f, 700.f) );
    btnoff->addTouchEventListener( CC_CALLBACK_1(game2::menuCloseCallback, this) );
     this->addChild(btnoff, 1);
    //Buttom map
    int A = 2.0;
      int B = 3.0;
      int C = B - A;
      int D = (rand() % C) + A;
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(game2::addMap), D);
    //
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //BackGround
    auto bg = Sprite::create("Level3-bg.png");
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(bg, -1);
    //declaration of ground PNG
    sprite = Sprite::create("lvl3-ground.png");
    sprite->setPosition(visibleSize.width/2, visibleSize.height* 0.1);
    this->addChild(sprite, 0);
    //creating physique for ground
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() , PhysicsMaterial(1.0f, 1.0f, 1.0f));
    sprite->addComponent(physicsBody);
    physicsBody->setDynamic(false);
    
    // target PNG
    targetS = Sprite::create("final-gift.png");
    targetS->setPosition(visibleSize.width*2.6, visibleSize.height* 0.5);
    this->addChild(targetS, 0);
    //creating physique for target
    auto targetBody = PhysicsBody::createBox(targetS->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    targetS->addComponent(targetBody);
    targetBody->setDynamic(false);
    
    //declaration of player PNG
    sprite1 = Sprite::create("lvl3-player.png");
    sprite1->setScale(0.2);
    sprite1->setPosition(visibleSize.width*0.4, visibleSize.height * 0.7);
    this->addChild(sprite1, 0);
    //creating physique for player
    auto physicsBody1 = PhysicsBody::createBox(sprite1->getContentSize()*0.55, PhysicsMaterial(0.8f, 2.0f, 1.0f));
    physicsBody1->setDynamic(true);
    sprite1->addComponent(physicsBody1);
    // Score laberl
    int m_score=1;
    m_scoreLabel = Label::createWithTTF(std::to_string(m_score), "fonts/arial.ttf", 36);
    m_scoreLabel->setPosition(visibleSize.width*0.85, visibleSize.height* 0.85);
    this->addChild(m_scoreLabel,1);
    // creating a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(game2::keyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
  
    this->scheduleUpdate();
    return true;
}

// because update triggers before instanciating the land
//auto land = NULL;

void game2::addMap(float dt)
{
    // Create obstacle Sprite
    Size visibleSize = Director::getInstance()->getVisibleSize();
    land = Sprite::create("Level3-Land.png");
  auto landContentSize = (land->getContentSize());
  auto selfContentSize = this->getContentSize();
  int Y = 250.0f;
    land->setPosition(Vec2(visibleSize.width*1.1, Y));
  this->addChild(land,0);
    // creating the physics
    auto landB = PhysicsBody::createBox(land->getContentSize(), PhysicsMaterial(1.0f, 0.3f, 1.0f));
    landB->setCollisionBitmask(3);
    landB->setDynamic(false);
    land->addComponent(landB);
    // Creating movement
    int randomDuration = 2.0;
  auto actionMove = MoveTo::create(randomDuration, Vec2(-landContentSize.width/2, Y));
  auto actionRemove = RemoveSelf::create();
    land->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}
void game2::update(float delta)
{
    if(land != NULL)
    {
        //move ground
        auto position = sprite->getPosition();
        position.x -= 250 * delta;
        sprite->setPosition(position);
        //position win target
        auto position1 = targetS->getPosition();
        position1.x -= 250 * delta;
        targetS->setPosition(position1);
        // No rotation
        sprite1->setRotation(0.0f);
    
        // collision player LOSE
        Rect rect1 = sprite1->getBoundingBox();
        Rect rect2 = sprite->getBoundingBox();
        if (rect1.intersectsRect( rect2))
        {
            auto scene = Lose3::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        //collision with ground
        
        Rect rect14 = sprite1->getBoundingBox();
        Rect rect24 = land->getBoundingBox();
        if (rect14.intersectsRect( rect24))
        {
            int m_score=1;
          
            Counter(m_score);
        }
        // player win collision
        Rect rect11 = sprite1->getBoundingBox();
        Rect rect22 = targetS->getBoundingBox();
        if (rect11.intersectsRect( rect22))
        {
            auto scene = Win3::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        if ( sprite->getPosition().x<-2500.0f){
            auto scene = Lose3::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        if ( sprite1->getPosition().x<-1.0f){
            auto scene = game2::createScene();
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void game2::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        auto jump = JumpBy::create( 2, Vec2(0, 100), 150.0f, 1);
           sprite1->runAction(jump);
    }else if(keyCode == EventKeyboard::KeyCode::KEY_D){
        auto action = MoveBy::create(2.0, Point(150, 0));
        sprite1->runAction(action);
    }else if(keyCode == EventKeyboard::KeyCode::KEY_A){
        auto action = MoveBy::create(2.0, Point(-150, 0));
        sprite1->runAction(action);}
    else if(keyCode == EventKeyboard::KeyCode::KEY_S){
        auto action = MoveBy::create(2.0, Point(-0, -100));
        sprite1->runAction(action);}
}
void game2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}
void game2::Counter(char mscore){
    
    m_score =m_score + 1 ;
    m_scoreLabel->setString(std::to_string(m_score));
}
