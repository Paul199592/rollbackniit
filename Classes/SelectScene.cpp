#include "SelectScene.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"
//#include <SimpleAudioEngine.h>

USING_NS_CC;

Scene* SelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectScene::init()
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
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setScale(visibleSize.width/bg->getContentSize().width);
    bg->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(bg);
    
    auto label = Label::createWithTTF("Select Case", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto labelItem1 = Label::createWithTTF("1-6", "fonts/Marker Felt.ttf", 20);
    auto item1 = MenuItemLabel::create(labelItem1, CC_CALLBACK_1(SelectScene::menuCloseCallback, this));
    item1->setPosition(Point(origin.x + visibleSize.width/5*4, origin.y + visibleSize.height/5));
    item1->setTag(1001);
    
    auto backLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 20);
    auto back = MenuItemLabel::create(backLabel, CC_CALLBACK_1(SelectScene::menuBackCallback, this));
    back->setPosition(Point(origin.x + visibleSize.width/8*1, origin.y + visibleSize.height/9));
    back->setTag(1000);
    auto menu = Menu::create(back, item1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}


void SelectScene::schCallBack(float delta){
    
}


void SelectScene::menuCloseCallback(Ref* pSender)
{
    auto sence = HelloWorld::createScene();
    auto transition = TransitionFade::create(2, sence);
    Director::getInstance()->replaceScene(transition);
}

void SelectScene::menuBackCallback(Ref* pSender)
{
    auto sence = MenuScene::createScene();
    auto transition = TransitionFade::create(2, sence);
    Director::getInstance()->replaceScene(transition);
}

