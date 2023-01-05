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

#include "game.h"

#include<iostream>
#include "Win1.h"
#include<iostream>
#include "Lose1.h"
using namespace cocos2d;
USING_NS_CC;
//

Scene* game::createScene()
{
    auto scene = Scene::createWithPhysics();
    //  this for physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    auto layer = game::create();
    // to edit the force of gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
       auto gravity = Vec2(0, -400.0f);
       world->setGravity(gravity);

    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool game::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    
    //monstre init
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(game::addMonster), 1.5);
    //
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //BackGround
    auto bg = Sprite::create("bg-lvl1.png");
    
        // position the sprite on the center of the screen
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(bg, -1);
    
    
    //declaration of ground PNG
    sprite = Sprite::create("off-level1-bg.png");
    sprite->setPosition(visibleSize.width/2, visibleSize.height* 0.1);
    this->addChild(sprite, 0);
    
    // target PNG
    targetS = Sprite::create("llife.png");
    targetS->setPosition(visibleSize.width*2, visibleSize.height* 0.2);
    this->addChild(targetS, 0);
    //creating physique for target
    auto targetBody = PhysicsBody::createBox(targetS->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    targetS->addComponent(targetBody);
    targetBody->setDynamic(false);
    
    //declaration of player PNG
    sprite1 = Sprite::create("runner.png");
    sprite1->setPosition(visibleSize.width*0.4, visibleSize.height * 0.2);
    this->addChild(sprite1, 0);
    sprite1->setScale(0.5);
    
    //creating physique for ground
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() , PhysicsMaterial(1.0f, 0.0f, 1.0f));
    sprite->addComponent(physicsBody);
    physicsBody->setDynamic(false);
    
    //creating physique for player
    
    auto physicsBody1 = PhysicsBody::createBox(sprite1->getContentSize() -sprite1->getContentSize()/10, PhysicsMaterial(1.0f, 1.0f, 1.0f));
    
    physicsBody1->setDynamic(true);
    sprite1->addComponent(physicsBody1);
    
    //keyboard test
    
    // creating a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(game::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(game::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    // use if your version is below cocos2d-x 3.0alpha.1
    // use this: Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this); if you are using cocos2d-x 3.0alpha.1 and later!
    
    
    /*auto contactListener =EventListenerPhysicsContact::create();
    //contactListener->onContactBegin =CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    */
    this->scheduleUpdate();
    return true;
}

// because update triggers before instanciating the monster
auto monster = NULL;

void game::addMonster(float dt)
{
    monster = Sprite::create("obs1.png");
  // 1
  auto monsterContentSize = monster->getContentSize();
  auto selfContentSize = this->getContentSize();
  int minY = monsterContentSize.height*2.3;

    // monster box collider
  //monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, minY));
    monster->setPosition(Vec2(monsterContentSize.width*13, minY));
  this->addChild(monster,0);
    auto monsterB = PhysicsBody::createBox(monster->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));
    monsterB->setCollisionBitmask(3);
    monsterB->setDynamic(true);
    monster->addComponent(monsterB);
    
  // 2
  int minDuration = 2.0;

 
  
    int randomDuration = minDuration;
    
  // 3
  auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, minY));
  auto actionRemove = RemoveSelf::create();
  monster->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

void game::update(float delta)
{
    //move ground
    if(monster != NULL)
    {
        auto position = sprite->getPosition();
        position.x -= 250 * delta;
        if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
            position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width/2;
        sprite->setPosition(position);
        
        //position win target
        auto position1 = targetS->getPosition();
        position1.x -= 250 * delta;
        if (position1.x  < 0 - (targetS->getBoundingBox().size.width / 2))
            position1.x = this->getBoundingBox().getMaxX() + targetS->getBoundingBox().size.width/2;
        targetS->setPosition(position1);
        
        
        //disable rtotation for the player
        sprite1->setRotation(0.0f);
        
        // collision player LOSE
        
        Rect rect1 = sprite1->getBoundingBox();
        Rect rect2 = monster->getBoundingBox();
        
        //std::cout<<rect1.origin.x<<"   "<<rect2.origin.x<<std::endl;
        //std::cout<<rect1.size.width<<"   "<<rect2.size.width<<std::endl;
        //std::cout<<rect1.size.height<<"   "<<rect2.size.height<<std::endl;
        if (rect1.intersectsRect( rect2))
        {
            auto scene = Lose1::createScene();
            Director::getInstance()->replaceScene(scene);
            //std::cout<<rect1.origin.x<<std::endl;
            
            log(" collided");
        }
        else
        {
            //log("not collided");
        }
        
        // player win collision
        Rect rect11 = sprite1->getBoundingBox();
        Rect rect22 = targetS->getBoundingBox();
        
        //std::cout<<rect1.origin.x<<"   "<<rect2.origin.x<<std::endl;
        //std::cout<<rect1.size.width<<"   "<<rect2.size.width<<std::endl;
        //std::cout<<rect1.size.height<<"   "<<rect2.size.height<<std::endl;
        if (rect11.intersectsRect( rect22))
        {
            auto scene = Win1::createScene();
            Director::getInstance()->replaceScene(scene);
            
            log(" Youuuuu Wiiiiin ");
        }
        else
        {
            //log("not collided");
        }
    }
    //move obstacle
    //auto position1 = sprite1->getPosition();
    //position1.x -= 250 * delta;
    //if (position1.x  < 0 - (sprite1->getBoundingBox().size.width / 2))
    // position1.x = this->getBoundingBox().getMaxX() + sprite1->getBoundingBox().size.width/2;
    //sprite1->setPosition(position1);
}

void game::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        auto jump = JumpBy::create(0.5f, Vec2(50, 50), 200.0f, 1);
           sprite1->runAction(jump);
    }
}
void game::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

}

/*bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    if ( (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() )
    {
        CCLOG("collieded");
    }
    
}*/
