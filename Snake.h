#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "cocos2d.h"
#include "Part.h"

class Snake
{
public:
	Snake(cocos2d::Layer *layer);
	void update();
	void updateDirection(cocos2d::EventKeyboard::KeyCode);
	boolean checkBodyCollision(cocos2d::Sprite *collision);
	boolean checkHeadCollision(cocos2d::Sprite *collision);
	boolean checkHeadHitBody();
	boolean checkGoOut();
	void addBody(cocos2d::Layer *layer);
	int getScore();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::string direction;
	std::vector<Part*> parts;
	std::vector<std::string> directions;
	std::vector<std::string>::iterator directionIterator;
	int score;

	Part *head;
};

#endif // __SNAKE_H__
