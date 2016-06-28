#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("bg1.png");
    bg->setScale(visibleSize.width/bg->getContentSize().width);
    bg->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(bg);
    
    
    
    auto block1 = Sprite::create("block1.png");
    block1->setScale(visibleSize.width/block1->getContentSize().width/15, visibleSize.height/block1->getContentSize().height/10);
    block1->setAnchorPoint(Point(0, 0));
    block1->setPosition(Point(origin.x, origin.y));
    
    auto chara = Sprite::create("walk1.png");
    chara->setScale(visibleSize.height/block1->getContentSize().height/10);
    chara->cocos2d::Node::setAnchorPoint(Point(0.5, 0));
    chara->setPosition(origin.x + visibleSize.width/30 + visibleSize.width/15 * charInX,
                       origin.y + visibleSize.height/10*(10-charInY-1));
    this->addChild(chara, 1, 2001);
    
    auto finish = Sprite::create("endpoint.png");
    finish->setScale(visibleSize.height/block1->getContentSize().height/10);
    finish->cocos2d::Node::setAnchorPoint(Point(0.5, 0));
    finish->setPosition(origin.x + visibleSize.width/30 + visibleSize.width/15 * finishX,
                       origin.y + visibleSize.height/10*(10-finishY-1));
    this->addChild(finish, 1, 2002);
    
    
    
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 15; j++) {
            if(map[i][j] == 'b'){
                auto block1 = Sprite::create("block1.png");
                block1->setScale(visibleSize.width/block1->getContentSize().width/15, visibleSize.height/block1->getContentSize().height/10);
                block1->setAnchorPoint(Point(0, 0));
                block1->setPosition(Point(origin.x + visibleSize.width/15*j,
                                          origin.y + visibleSize.height/10*(10-i-1)));
                this->addChild(block1, 1, i*100+j);
            }else if(map[i][j] == 'm'){
                auto chara = Sprite::create("mon1down.png");
                chara->setScale(visibleSize.height/block1->getContentSize().height/10);
                chara->cocos2d::Node::setAnchorPoint(Point(0.5, 0));
                chara->setPosition(origin.x + visibleSize.width/30 + visibleSize.width/15 * j,
                                   origin.y + visibleSize.height/10*(10-i-1));
                this->addChild(chara, 1, 3000+i*100+j);
            }
        }
    }
    
    auto leftnormal = Sprite::create("rightclick.png");
    leftnormal->setScale(visibleSize.height/block1->getContentSize().height/10);
    auto lefttouch = Sprite::create("rightclick.png");
    lefttouch->setScale(visibleSize.height/block1->getContentSize().height/10*1.1);
    auto left = MenuItemSprite::create(leftnormal, lefttouch, CC_CALLBACK_1(HelloWorld::menuLeftCallback, this));
    left->setPosition(Point(origin.x,origin.y));
    left->setAnchorPoint(Point(0, 0));
    
    auto rightnormal = Sprite::create("leftclick.png");
    rightnormal->setScale(visibleSize.height/block1->getContentSize().height/10);
    auto righttouch = Sprite::create("leftclick.png");
    righttouch->setScale(visibleSize.height/block1->getContentSize().height/10*1.1);
    auto right = MenuItemSprite::create(rightnormal, righttouch, CC_CALLBACK_1(HelloWorld::menuRightCallback, this));
    right->setPosition(Point(origin.x + visibleSize.width/15*14,origin.y));
    right->setAnchorPoint(Point(0, 0));
    
    auto leftjumpnormal = Sprite::create("jumpclick.png");
    leftjumpnormal->setScale(visibleSize.height/block1->getContentSize().height/10);
    auto leftjumptouch = Sprite::create("jumpclick.png");
    leftjumptouch->setScale(visibleSize.height/block1->getContentSize().height/10*1.1);
    auto leftJump = MenuItemSprite::create(leftjumpnormal, leftjumptouch, CC_CALLBACK_1(HelloWorld::menuLeftJumpCallback, this));
    leftJump->setPosition(Point(origin.x + visibleSize.width/15*2,origin.y));
    leftJump->setAnchorPoint(Point(0,0));
    
    auto rightjumpnormal = Sprite::create("jumpclick.png");
    rightjumpnormal->setScale(visibleSize.height/block1->getContentSize().height/10);
    auto rightjumptouch = Sprite::create("jumpclick.png");
    rightjumptouch->setScale(visibleSize.height/block1->getContentSize().height/10*1.1);
    auto rightJump = MenuItemSprite::create(rightjumpnormal, rightjumptouch, CC_CALLBACK_1(HelloWorld::menuRightJumpCallback, this));
    rightJump->setPosition(Point(origin.x + visibleSize.width/15 * 12,origin.y));
    rightJump->setAnchorPoint(Point(0, 0));
    
    auto clickGroup = Menu::create(left, leftJump, rightJump, right, NULL);
    clickGroup->setPosition(Vec2::ZERO);
    this->addChild(clickGroup,2);
    
    return true;
}


void HelloWorld::menuLeftCallback(Ref* pSender)
{
    if(isClickable){
        charInX++;
        int width = Director::getInstance()->getVisibleSize().width / 15;
        int height = Director::getInstance()->getVisibleSize().height / 10;
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        if(charInX >= 15){
//            CCLOG("DIE");
            charInX--;
            CCLOG("at edge");
        }else if(map[charInY][charInX] == 'm'){
            charInX--;
            CCLOG("DIE by MON");
        }else if(map[charInY][charInX] == 'b'){
            charInX--;
            CCLOG("at wall");
        }else if (map[charInY + 1][charInX] == 'n'){
            charInX--;
            CCLOG("DIE by FALL");
        }
        else if(map[charInY][charInX] == 'n'){
            isClickable = false;
            auto point = new Point(origin.x + width * charInX + width/2,
                                   origin.y + height * (10 - charInY - 1));
            auto move = MoveTo::create(1, *point);
            auto sprite = this->getChildByTag(2001);
            if(lastOP == 1 || lastOP == 3){
//                sprite->setScale(-1);
            }
            lastOP = 0;
            auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
            auto sequence = Sequence::create(move, func, NULL);
            sprite->runAction(sequence);
        }else{
            CCLOG("%c", map[charInY][charInX]);
            charInX++;
        }
    }
    //CCLOG("left click");
}

void HelloWorld::menuLeftJumpCallback(Ref* pSender)
{
    if(isClickable){
        int width = Director::getInstance()->getVisibleSize().width / 15;
        int height = Director::getInstance()->getVisibleSize().height / 10;
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        if (charInY > 0) {
            if (map[charInY][charInX+1] == 'b') {
                if(map[charInY-1][charInX+1] == 'm'){
                    CCLOG("DIE by MON");
                }else if(map[charInY-1][charInX+1]=='n'){
                    isClickable = false;
                    charInX++;
                    charInY--;
                    auto point = new Point(origin.x + width * charInX + width/2,
                                           origin.y + height * (10 - charInY - 1));
                    auto jump = JumpTo::create(1, *point, origin.y + height * (10 - charInY - 0.5), 1);
                    auto sprite = this->getChildByTag(2001);
                    if(lastOP == 0 || lastOP == 2){
                        //                        sprite->setScale(-1);
                    }
                    lastOP = 3;
                    auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
                    auto sequence = Sequence::create(jump, func, NULL);
                    sprite->runAction(sequence);
                }
            }else if(map[charInY+1][charInX+1]=='b'){
                if(map[charInY][charInX+2]=='b'){
                    CCLOG("Face Wall");
                }else if(map[charInY+1][charInX+2]=='b'){
                    if (map[charInY][charInX+2]=='n') {
                        isClickable = false;
                        CCLOG("%c", map[charInY-1][charInX-1]);
                        charInX+=2;
                        auto point = new Point(origin.x + width * charInX + width/2,
                                               origin.y + height * (10 - charInY - 1));
                        auto jump = JumpTo::create(1, *point, origin.y + height * (10 - charInY - 0.5), 1);
                        auto sprite = this->getChildByTag(2001);
                        if(lastOP == 0 || lastOP == 2){
                            //                        sprite->setScale(-1);
                        }
                        lastOP = 3;
                        auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
                        auto sequence = Sequence::create(jump, func, NULL);
                        sprite->runAction(sequence);
                    }else if (map[charInY][charInX+2]=='m'){
                        CCLOG("Kill a MON");
                    }
                }
            }else if (charInY + 2 < 15){
                if (map[charInY+2][charInX+1]=='b') {
                    if(map[charInY+1][charInX+1]=='n'){
                        isClickable = false;
                        charInY++;
                        charInX++;
                        auto point = new Point(origin.x + width * charInX + width/2,
                                               origin.y + height * (10 - charInY - 1));
                        auto jump = JumpTo::create(1, *point, origin.y + height * (10 - charInY - 0.5), 1);
                        auto sprite = this->getChildByTag(2001);
                        if(lastOP == 0 || lastOP == 2){
                            //                        sprite->setScale(-1);
                        }
                        lastOP = 3;
                        auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
                        auto sequence = Sequence::create(jump, func, NULL);
                        sprite->runAction(sequence);                    }
                }
            }else if(charInY+2>=15){
                CCLOG("FALL to DIE");
            }
        }
    }

}

void HelloWorld::menuRightCallback(Ref* pSender)
{
//    CCLOG("right click");
    if(isClickable){
        charInX--;
        int width = Director::getInstance()->getVisibleSize().width / 15;
        int height = Director::getInstance()->getVisibleSize().height / 10;
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        if(charInX >= 15){
            //            CCLOG("DIE");
            CCLOG("at edge");
            charInX++;
        }else if(map[charInY][charInX] == 'm'){
            CCLOG("DIE by MON");
            charInX++;
        }else if(map[charInY][charInX] == 'b'){
            CCLOG("at wall");
            charInX++;
        }else if (map[charInY + 1][charInX] == 'n'){
            CCLOG("DIE by FALL");
            charInX++;
        }else if(map[charInY][charInX] == 'n'){
            isClickable = false;
            auto point = new Point(origin.x + width * charInX + width/2,
                                   origin.y + height * (10 - charInY - 1));
            auto move = MoveTo::create(1, *point);
            auto sprite = this->getChildByTag(2001);
            if(lastOP == 0 || lastOP == 2){
//                sprite->setScale(-1);
            }
            lastOP = 1;
            auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
            auto sequence = Sequence::create(move, func, NULL);
            sprite->runAction(sequence);
        }else{
            CCLOG("%c", map[charInY][charInX]);
            charInX--;
        }
    }

}

void HelloWorld::menuRightJumpCallback(Ref* pSender)
{
    if(isClickable){
        int width = Director::getInstance()->getVisibleSize().width / 15;
        int height = Director::getInstance()->getVisibleSize().height / 10;
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        if (charInY > 0) {
            if (map[charInY][charInX-1] == 'b') {
                if(map[charInY-1][charInX-1] == 'm'){
                    CCLOG("DIE by MON");
                }else if(map[charInY-1][charInX-1]=='n'){
                    isClickable = false;
                    charInX--;
                    charInY--;
                    auto point = new Point(origin.x + width * charInX + width/2,
                                           origin.y + height * (10 - charInY - 1));
                    auto jump = JumpTo::create(1, *point, origin.y + height * (10 - charInY - 0.5), 1);
                    auto sprite = this->getChildByTag(2001);
                    if(lastOP == 0 || lastOP == 2){
//                        sprite->setScale(-1);
                    }
                    lastOP = 3;
                    auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
                    auto sequence = Sequence::create(jump, func, NULL);
                    sprite->runAction(sequence);
                }
            }else if(map[charInY+1][charInX-1]=='b'){
                if(map[charInY][charInX-2]=='b'){
                    CCLOG("Face Wall");
                }else if(map[charInY+1][charInX-2]=='b'){
                    if (map[charInY][charInX-2]=='n') {
                        isClickable = false;
                        CCLOG("%c", map[charInY-1][charInX-1]);
                        charInX-=2;
                        auto point = new Point(origin.x + width * charInX + width/2,
                                               origin.y + height * (10 - charInY - 1));
                        auto jump = JumpTo::create(1, *point, origin.y + height * (10 - charInY - 0.5), 1);
                        auto sprite = this->getChildByTag(2001);
                        if(lastOP == 0 || lastOP == 2){
                            //                        sprite->setScale(-1);
                        }
                        lastOP = 3;
                        auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
                        auto sequence = Sequence::create(jump, func, NULL);
                        sprite->runAction(sequence);
                    }else if (map[charInY][charInX-2]=='m'){
                        CCLOG("Kill a MON");
                    }
                }
            }else if (charInY + 2 < 15){
                if (map[charInY+2][charInX-1]=='b') {
                    if(map[charInY+1][charInX-1]=='n'){
                        isClickable = false;
                        charInY++;
                        charInX--;
                        auto point = new Point(origin.x + width * charInX + width/2,
                                               origin.y + height * (10 - charInY - 1));
                        auto jump = JumpTo::create(1, *point, origin.y + height * (10 - charInY - 0.5), 1);
                        auto sprite = this->getChildByTag(2001);
                        if(lastOP == 0 || lastOP == 2){
                            //                        sprite->setScale(-1);
                        }
                        lastOP = 3;
                        auto func = CallFunc::create(this, callfunc_selector(HelloWorld::checkFunction));
                        auto sequence = Sequence::create(jump, func, NULL);
                        sprite->runAction(sequence);
                    }
                }
            }else if(charInY+2>=15){
                CCLOG("FALL to DIE");
            }
        }
    }
    
}

void HelloWorld::checkFunction(){
    isClickable = true;
    if (finishY==charInY && finishX==charInX) {
        CCLOG("WIN");
        isClickable = false;
    }
}