#include "MenuScene.h"
#include "SelectScene.h"
//#include <SimpleAudioEngine.h>

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
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
    
    auto label = Label::createWithTTF("Roll Back", "fonts/Marker Felt.ttf", 28);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto labelItem = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 24);
    auto item1 = MenuItemLabel::create(labelItem, CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    item1->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/6));
    auto menu = Menu::create(item1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}


void MenuScene::schCallBack(float delta){
    
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    auto sence = SelectScene::createScene();
    auto transition = TransitionFade::create(2, sence);
    Director::getInstance()->replaceScene(transition);
}
