#include "GameScene.h"
#include "Snake.h"
#include "Flower.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto eatingAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	eatingAudio->preloadEffect("Eating.wav");

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	snake = new Snake(this);

	flower = new Flower();
	flower->RandomFlower(this, snake, Director::getInstance()->getVisibleSize().width);
	flower->getSprite()->setTag(99);

	scoreText = ("Score: 0");
	scoreLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", visibleSize.height * 0.05);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setPosition(Point(visibleSize.width * 0.9 + origin.x, visibleSize.height * 0.95 + origin.y));
	this->addChild(scoreLabel);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	scheduler = schedule_selector(GameScene::move);
	this->schedule(scheduler, 0.1);

	auto event = EventListenerKeyboard::create();
	event->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		snake->updateDirection(keyCode);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);

    return true;
}

void GameScene::move(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	snake->update();
	if (snake->checkHeadCollision(flower->getSprite()))
	{
		removeChildByTag(99);
		delete flower;
		flower = new Flower();
		flower->RandomFlower(this, snake, visibleSize.width);
		flower->getSprite()->setTag(99);
		snake->addBody(this);
		scoreText = ("Score: " + std::to_string(snake->getScore()));
		scoreLabel->setString(scoreText);
		auto eatingAudio = CocosDenshion::SimpleAudioEngine::getInstance();
		eatingAudio->playEffect("Eating.wav");
	}

	if (snake->checkHeadHitBody() || snake->checkGoOut())
	{
		unschedule(scheduler);
		auto newScene = GameScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, newScene));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Crash.aif");
	}

}

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
