#include "Flower.h"
#include "Snake.h"
#include <random>
#include <iostream>
#include <ctime>

USING_NS_CC;


Flower::Flower() 
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Flower::RandomFlower(cocos2d::Layer *layer, Snake *snake, float screenSize) 
{
	/*std::srand(std::time(0)); // use current time as seed for random generator
	int random_variable = std::rand()%(int)(screenSize - visibleSize.width);
	std::srand(std::time(0)); // use current time as seed for random generator
	int random_variable2 = std::rand() % (int)(screenSize - visibleSize.width);*/

	sprite = Sprite::create("Flower.png");
	
	int random1 = rand() % (int)(screenSize - sprite->getContentSize().width);
	int random2 = rand() % (int)(screenSize - sprite->getContentSize().width);

	sprite->setPosition(random1, random2);
	layer->addChild(sprite, 40);
}

cocos2d::Sprite* Flower::getSprite(){
	return sprite;
}
