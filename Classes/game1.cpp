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

#include "game1.h"

#include<iostream>
#include "Win2.h"
#include "Lose2.h"
using namespace cocos2d;
USING_NS_CC;
//

Scene* game1::createScene()
{
    auto scene = Scene::createWithPhysics();
    //  this for physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    auto layer = game1::create();
    // to edit the force of gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
       auto gravity = Vec2(0, -20.0f);
       world->setGravity(gravity);

    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool game1::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // close button
    ui::Button* btnoff = ui::Button::create("btn-mini-exit.png");
    
     btnoff->setPosition( Vec2(100.f, 700.f) );
    btnoff->addTouchEventListener( CC_CALLBACK_1(game1::menuCloseCallback, this) );
     this->addChild(btnoff, 1);
    
    //Buttom obstacle map
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(game1::addMap), 4);
    //
    //Top obstacle  map
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(game1::addMap2), 3);
    // declaring
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //BackGround
    auto bg = Sprite::create("Level-2-bg.png");
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(bg, -1);
    //declaration of ground PNG
    sprite = Sprite::create("lvl2-ground.png");
    sprite->setPosition(visibleSize.width/2, visibleSize.height* 0);
    this->addChild(sprite, 0);
    //creating physique for ground
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    sprite->addComponent(physicsBody);
    physicsBody->setDynamic(false);
    
    // target PNG
    targetS = Sprite::create("final-gift.png");
    targetS->setScale(0.8);
    targetS->setPosition(visibleSize.width*2, visibleSize.height* 0.45);
    this->addChild(targetS, 0);
    //creating physique for target
    auto targetBody = PhysicsBody::createBox(targetS->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    targetS->addComponent(targetBody);
    targetBody->setDynamic(false);
    
    //declaration of player PNG
    sprite1 = Sprite::create("Plane.png");
    sprite1->setScale(0.1);
    sprite1->setPosition(visibleSize.width*0.4, visibleSize.height * 0.5);
    this->addChild(sprite1, 0);
    sprite1->setScale(0.5);
    //creating physique for player
    auto physicsBody1 = PhysicsBody::createBox(sprite1->getContentSize() -sprite1->getContentSize()/10, PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody1->setDynamic(true);
    sprite1->addComponent(physicsBody1);
    
    // creating a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(game1::keyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
   
    this->scheduleUpdate();
    return true;
}

// because update triggers before instanciating the monster
//auto monster = NULL;

void game1::addMap(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    monster = Sprite::create("Level2-buttom-obs.png");
    monster->setScale(0.8);
  auto monsterContentSize = (monster->getContentSize());
  auto selfContentSize = this->getContentSize();
  int minY = 190.0f;
    // obstacle collider
    monster->setPosition(Vec2(visibleSize.width*1.1, minY));
  this->addChild(monster,0);
    auto monsterB = PhysicsBody::createBox(monster->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));
    monsterB->setCollisionBitmask(3);
    monsterB->setDynamic(false);
    monster->addComponent(monsterB);

  int minDuration = 4.0;
    int randomDuration = minDuration;
    // obstacle mover
  auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, minY));
  auto actionRemove = RemoveSelf::create();
  monster->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}
void game1::addMap2(float dt) // the same code of addMap function
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    monster1 = Sprite::create("lvl2-top-obs.png");
    monster1->setScale(4);
  auto monsterContentSize = (monster1->getContentSize());
  auto selfContentSize = this->getContentSize();
  int minY = 700.0f;

    monster1->setPosition(Vec2(visibleSize.width*1.1, minY));
  this->addChild(monster1,0);
    auto monsterB = PhysicsBody::createBox(monster1->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));
    monsterB->setCollisionBitmask(3);
    monsterB->setDynamic(false);
    monster1->addComponent(monsterB);

  int minDuration = 4.0;
    int randomDuration = minDuration;

  auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, minY));
  auto actionRemove = RemoveSelf::create();
  monster1->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

void game1::update(float delta)
{
    
    if(monster != NULL)
    {
        //move ground
        auto position = sprite->getPosition();
        position.x -= 250 * delta;
        sprite->setPosition(position);
        
        //position win target
        auto position1 = targetS->getPosition();
        position1.x -= 250 * delta;
        targetS->setPosition(position1);
        
        
        //disable rtotation for the player
        sprite1->setRotation(0.0f);
        
        // collision with land
        Rect rect14 = sprite1->getBoundingBox();
        Rect rect24 = sprite->getBoundingBox();
        if (rect14.intersectsRect( rect24))
        {
            auto scene = Lose2::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        // collision player LOSE
        
        Rect rect1 = sprite1->getBoundingBox();
        Rect rect2 = monster->getBoundingBox();
        if (rect1.intersectsRect( rect2))
        {
            auto scene = Lose2::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        // player collision with top map
        Rect rect13 = sprite1->getBoundingBox();
        Rect rect23 = monster1->getBoundingBox();
   
        if (rect13.intersectsRect( rect23))
        {
            auto scene = Lose2::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        // player win collision
        Rect rect11 = sprite1->getBoundingBox();
        Rect rect22 = targetS->getBoundingBox();
      
        if (rect11.intersectsRect( rect22))
        {
            auto scene = Win2::createScene();
            Director::getInstance()->replaceScene(scene);
            
            log(" Youuuuu Wiiiiin ");
        }
        // if player passed win target
        if ( sprite->getPosition().x<-1575.0f){
            auto scene = Lose2::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        // if player out of screen
        if ( sprite1->getPosition().x<-1.0f){
            auto scene = game1::createScene();
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void game1::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        auto jump = JumpBy::create( 1.4, Vec2(0, 100), 50.0f, 1);
           sprite1->runAction(jump);
    }
}
void game1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

