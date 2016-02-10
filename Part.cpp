#include "Part.h"

USING_NS_CC;

Part::Part(cocos2d::Layer *layer, std::string type, Point position)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	if (type == "head")
	{
		sprite = Sprite::create("snakeHead.png");
	}
	else
	{
		sprite = Sprite::create("snakeBody.png");
	}

	sprite->setPosition(position);
	layer->addChild(sprite);
}	

void Part::move(std::string direction)
{
	auto position = sprite->getPosition();
	if (direction == "left")
	{
		position.x -= sprite->getContentSize().width;
	}
	else if (direction == "right")
	{
		position.x += sprite->getContentSize().width;
	}
	else if (direction == "up")
	{
		position.y += sprite->getContentSize().height;
	}
	else if (direction == "down")
	{
		position.y -= sprite->getContentSize().height;
	}
	sprite->setPosition(position);
	
}

boolean Part::checkBodyCollision(cocos2d::Sprite *collision) 
{
	if (collision->getPosition() == collision->getPosition())
		return true;
	else return false;
}

cocos2d::Sprite* Part::getSprite(){
	return sprite;
}
