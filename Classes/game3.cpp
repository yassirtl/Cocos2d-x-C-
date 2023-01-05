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

#include "game3.h"
#include <string>
#include <string.h>
#include<iostream>
#include "Win3.h"
#include "Lose4.h"
using namespace cocos2d;
USING_NS_CC;
//

Scene* game3::createScene()
{
    auto scene = Scene::createWithPhysics();
    //  this for physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    auto layer = game3::create();
    // to edit the force of gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
       auto gravity = Vec2(0, -220.0f);
       world->setGravity(gravity);

    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool game3::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // call coin function
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(game3::addCoin), 3);
  
    // close button
    ui::Button* btnoff = ui::Button::create("btn-mini-exit.png");
     btnoff->setPosition( Vec2(100.f, 700.f) );
    btnoff->addTouchEventListener( CC_CALLBACK_1(game3::menuCloseCallback, this) );
     this->addChild(btnoff, 1);
    //Buttom map
    int A = 3.0;
      int B = 4.0;
      int C = B - A;
      int D = (rand() % C) + A;
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(game3::addMap), D);
    //
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //declaration of BG PNG
    sprite_BG = Sprite::create("lvl4bg.png");
    sprite_BG->setPosition(visibleSize.width*0.5, visibleSize.height * 0.5);
    
     this->addChild(sprite_BG, 0);
    //ground Sprite
    sprite_G1 = Sprite::create("4ground.png");
    sprite_G1->setPosition(visibleSize.width/2, visibleSize.height* 0.1);
    this->addChild(sprite_G1, 0);
    
    sprite_G2 = Sprite::create("4ground.png");
    sprite_G2->setPosition(visibleSize.width + visibleSize.width /2, visibleSize.height* 0.1);
    this->addChild(sprite_G2, 0);
    
    //creating physique for ground
    auto physicsBody = PhysicsBody::createBox(sprite_G1->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    sprite_G1->addComponent(physicsBody);
    physicsBody->setDynamic(false);
    
    auto physicsBody2 = PhysicsBody::createBox(sprite_G2->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    sprite_G2->addComponent(physicsBody2);
    physicsBody2->setDynamic(false);
    
    // target PNG
    targetS = Sprite::create("final-gift.png");
    targetS->setPosition(visibleSize.width*2.6, visibleSize.height* 0.5);
    this->addChild(targetS, 0);
    //creating physique for target
    auto targetBody = PhysicsBody::createBox(targetS->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    targetS->addComponent(targetBody);
    targetBody->setDynamic(false);
    
    //declaration of player PNG
    sprite_PL = Sprite::create("player4.png");
    sprite_PL->setScale(0.2);
    sprite_PL->setPosition(visibleSize.width*0.4, visibleSize.height * 0.7);
    this->addChild(sprite_PL, 0);
    //creating physique for player
    auto physicsBody1 = PhysicsBody::createBox(sprite_PL->getContentSize()*0.55, PhysicsMaterial(0.8f, 2.0f, 1.0f));
    physicsBody1->setDynamic(true);
    sprite_PL->addComponent(physicsBody1);
    
    // Score laberl
    int m_score=1;
    m_scoreLabel = Label::createWithTTF(std::to_string(m_score), "fonts/arial.ttf", 36);
    m_scoreLabel->setPosition(visibleSize.width*0.85, visibleSize.height* 0.85);
    this->addChild(m_scoreLabel,1);
    // Score bg
    auto m_scoreSP = Sprite::create("coinScorer.png");
    m_scoreSP->setPosition(visibleSize.width*0.84, visibleSize.height* 0.845);
    this->addChild(m_scoreSP, -0.5);
    
    // creating a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(game3::keyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
  
    this->scheduleUpdate();
    return true;
}

// because update triggers before instanciating the land
//auto land = NULL;

void game3::addMap(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    land = Sprite::create("level1-obs.png");
  auto landContentSize = (land->getContentSize());
  auto selfContentSize = this->getContentSize();
  int Y = 190.0f;

    land->setPosition(Vec2(visibleSize.width*1.1, Y));
    land->setScale( 0.2);
  this->addChild(land,0);
    auto landB = PhysicsBody::createBox(land->getContentSize(), PhysicsMaterial(1.0f, 0.3f, 1.0f));
    landB->setCollisionBitmask(3);
    landB->setDynamic(false);
    land->addComponent(landB);
    int randomDuration = 4.0;
  auto actionMove = MoveTo::create(randomDuration, Vec2(-landContentSize.width/2, Y));
  auto actionRemove = RemoveSelf::create();
    land->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}
void game3::addCoin(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    coin = Sprite::create("coin.png");// scale edit
  auto coinContentSize = coin->getContentSize();
  auto selfContentSize = this->getContentSize();
  int minY = visibleSize.height/4;
  
    coin->setPosition(Vec2(visibleSize.width*1.2, minY));
  this->addChild(coin,0);
    auto coinB = PhysicsBody::createBox(coin->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));
    coinB->setCollisionBitmask(3);
    coinB->setDynamic(false);
    coin->addComponent(coinB);
    // Speed
    int Speed = 4.0;
    //move Obstacles
  auto actionMove = MoveTo::create(Speed, Vec2(-coinContentSize.width/2, minY));
  auto actionRemove = RemoveSelf::create();
    coin->runAction(Sequence::create(actionMove,actionRemove, RemoveSelf::create(), nullptr));
}
void game3::update(float delta)
{
    // no rotation for player
    sprite_PL->setRotation(0.0);
    if(land != NULL && coin!=NULL)
    {
        //move ground
        
        //1
        Size visibleSize = Director::getInstance()->getVisibleSize();
        auto position = sprite_G1->getPosition();
        auto position2 = sprite_G2->getPosition();
        //2
        position.x -= 250 * delta;
        //3
        if (position.x  <  -(sprite_G1->getBoundingBox().size.width / 2))
            position.x = sprite_G1->getBoundingBox().size.width + sprite_G1->getBoundingBox().size.width/2 ;
        sprite_G1->setPosition(position);
        {
        //4
            if ((position.x  < (sprite_G1->getBoundingBox().size.width / 2)) || (position2.x> -(sprite_G1->getBoundingBox().size.width / 2))){
                position2.x -= 250 * delta;
            }
            sprite_G2->setPosition(position2);
        }
        {
        //5
            if (position2.x  < -visibleSize.width / 2){
                position2.x = visibleSize.width + visibleSize.width/2;
            }
            sprite_G2->setPosition(position2);
        }
        {
            // collision player LOSE
            Rect rect1 = sprite_PL->getBoundingBox();
            Rect rect2 = land->getBoundingBox();
            if (rect1.intersectsRect( rect2))
            {
                auto scene = Lose4::createScene();
                Director::getInstance()->replaceScene(scene);
            }
           
                // player win collision
                Rect rect11 = sprite_PL->getBoundingBox();
                Rect rect22 = coin->getBoundingBox();
                if (rect11.intersectsRect( rect22))
                {
                    int m_score=1;
                  
                    Counter(m_score);
                    coin->setPosition(visibleSize.width*1.2,visibleSize.height*-0.2);
                    
                }
            
          
            if ( sprite_PL->getPosition().x<-1.0f){
                auto scene = game3::createScene();
                Director::getInstance()->replaceScene(scene);
            }
            if(land!= NULL){
                Rect rect13 = land->getBoundingBox();
                Rect rect23 = sprite_PL->getBoundingBox();
                if ( rect13.intersectsRect( rect23))
                {
                    
                    int m_score=1;
                  
                    Counter(m_score);
                    land->setPosition(visibleSize.width*1.2,visibleSize.height*-0.2);
                    
                    
                    }
        }
    }
    
        }
}
void game3::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        auto jump = JumpBy::create( 1, Vec2(0, 100), 150.0f, 1);
           sprite_PL->runAction(jump);
    }else if(keyCode == EventKeyboard::KeyCode::KEY_D){
        auto action = MoveBy::create(2.0, Point(150, 0));
        sprite_PL->runAction(action);
    }else if(keyCode == EventKeyboard::KeyCode::KEY_A){
        auto action = MoveBy::create(2.0, Point(-150, 0));
        sprite_PL->runAction(action);}
    else if(keyCode == EventKeyboard::KeyCode::KEY_S){
        auto action = MoveBy::create(2.0, Point(-0, -100));
        sprite_PL->runAction(action);}
}
void game3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}
void game3::Counter(char mscore){
    
    m_score =m_score + 1 ;
    m_scoreLabel->setString(std::to_string(m_score));
}
