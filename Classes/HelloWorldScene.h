#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuLeftCallback(cocos2d::Ref* pSender);
    void menuLeftJumpCallback(cocos2d::Ref* pSender);
    void menuRightCallback(cocos2d::Ref* pSender);
    void menuRightJumpCallback(cocos2d::Ref* pSender);
    
    void checkFunction();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    char map[10][15] = {
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'b', 'b', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'b', 'n', 'n', 'b', 'n', 'n', 'n', 'n', 'n', 'b', 'b', 'n', 'n', 'n', 'n'},
        {'m', 'n', 'n', 'n', 'b', 'n', 'm', 'n', 'b', 'n', 'n', 'b', 'n', 'n', 'n'},
        {'b', 'n', 'n', 'n', 'n', 'b', 'b', 'b', 'n', 'n', 'n', 'n', 'b', 'b', 'b'}
                            };
    
    bool isClickable = true;
    int charInX = 14;
    int charInY = 8;
    
    int finishX = 0;
    int finishY = 6;
    /*
     *0: left
     *1: right
     *2: left jump
     *3: right jump
     */
    int lastOP = 0;
};

#endif // __HELLOWORLD_SCENE_H__
