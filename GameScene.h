#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Snake.h"
#include "Flower.h"
#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	void move(float);
	void menuCloseCallback(cocos2d::Ref* pSender);

    virtual bool init();

private:
	Snake *snake;
	Flower *flower;
	cocos2d::Label *scoreLabel;
	std::string scoreText;
	cocos2d::SEL_SCHEDULE scheduler;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
