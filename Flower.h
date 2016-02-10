#ifndef __FLOWER_H__
#define __FLOWER_H__

#include "cocos2d.h"
#include "Snake.h"

class  Flower 
{

public:
	Flower();
	void RandomFlower(cocos2d::Layer *layer, Snake *snake, float screenSize);
	cocos2d::Sprite *getSprite();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *sprite;
};

#endif // __PART_H__
