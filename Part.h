#ifndef __PART_H__
#define __PART_H__

#include "cocos2d.h"

class Part
{
public:
	Part(cocos2d::Layer *layer, std::string type, cocos2d::Point position);
	void move(std::string direction);
	boolean checkBodyCollision(cocos2d::Sprite *sprite);
	cocos2d::Sprite *getSprite();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *sprite;
};

#endif // __PART_H__
