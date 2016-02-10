#include "Snake.h"
#include "Part.h"

USING_NS_CC;

Snake::Snake(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	score = 0;
	head = new Part(layer, "head", Point(visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y) );

}

void Snake::update()
{
	std::string tempDirection;
	head->move(direction);
	int i;
	for (i = 0; i < parts.size(); i++)
	{
		if (i == parts.size()-1)
		{
			tempDirection = directions.back();
			parts.at(i)->move(tempDirection);
			directions.pop_back();
			directions.push_back(direction);
		}
		else
		{
			tempDirection = directions.back();
			parts.at(i)->move(tempDirection);
			directions.pop_back();
			directionIterator = directions.begin();
			directions.insert(directionIterator, tempDirection);
		}
	}
}

void Snake::updateDirection(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		if (direction != "right")
			direction = "left";
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		if (direction != "left")
			direction = "right";
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		if (direction != "down")
			direction = "up";
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		if (direction != "up")
			direction = "down";
		break;
	}
}

boolean Snake::checkHeadHitBody()
{
	for (std::vector<Part*>::iterator partPos = parts.begin(); partPos != parts.end(); ++partPos)
	{
		auto positionA = head->getSprite()->getPosition();
		auto positionB = (*partPos)->getSprite()->getPosition();

		if (positionA.x == positionB.x && positionA.y == positionB.y)
		{
			return true;
		}
		//_world->DestroyBody(body);
	}
	return false;

	/*if (toDestroy.size() > 0) {
	[[SimpleAudioEngine sharedEngine] playEffect:@"hahaha.caf"];
	}*/
}

boolean Snake::checkBodyCollision(cocos2d::Sprite *collision)
{
	for (std::vector<Part*>::iterator partPos = parts.begin(); partPos != parts.end(); ++partPos) 
	{
		CCRect box1Rect = collision->boundingBox();
		CCRect box2Rect = (*partPos)->getSprite()->boundingBox();

		if (box1Rect.intersectsRect(box2Rect))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*if (toDestroy.size() > 0) {
		[[SimpleAudioEngine sharedEngine] playEffect:@"hahaha.caf"];
	}*/
}

boolean Snake::checkHeadCollision(cocos2d::Sprite *collision)
{
	CCRect box1Rect = collision->boundingBox();
	CCRect box2Rect = head->getSprite()->boundingBox();

	if (box1Rect.intersectsRect(box2Rect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

boolean Snake::checkGoOut()
{
	auto positionX = head->getSprite()->getPosition().x;
	auto positionY = head->getSprite()->getPosition().y;
	if (positionX < 0 || positionX > 480 || positionY < 0 || positionY > 480)
		return true;
	else
		return false;
}

void Snake::addBody(cocos2d::Layer *layer)
{
	Part *tempPart;
	auto position = head->getSprite()->getPosition();
	auto lastPosition = head->getSprite()->getPosition();

	score++;
	directionIterator = directions.begin();
	if (parts.size() != 0)
		lastPosition = parts.back()->getSprite()->getPosition();
	if (direction == "right")
	{

		directions.insert(directionIterator, "right");
		if (parts.size() == 0)
		{
			tempPart = new Part(layer, "body", Point(position.x - head->getSprite()->getBoundingBox().size.width, 
													 position.y));
			parts.push_back(tempPart);
		}
		else
		{
			tempPart = new Part(layer, "body", Point(lastPosition.x - head->getSprite()->getBoundingBox().size.width,
				lastPosition.y));
			parts.push_back(tempPart);
		}
	}
	else if (direction == "left")
	{
		directions.insert(directionIterator, "left");
		if (parts.size() == 0)
		{
			tempPart = new Part(layer, "body", Point(position.x + head->getSprite()->getBoundingBox().size.width,
				position.y));
			parts.push_back(tempPart);
		}
		else
		{
			tempPart = new Part(layer, "body", Point(lastPosition.x + head->getSprite()->getBoundingBox().size.width,
				lastPosition.y));
			parts.push_back(tempPart);
		}
	}
	else if (direction == "up")
	{
		directions.insert(directionIterator, "up");
		if (parts.size() == 0)
		{
			tempPart = new Part(layer, "body", Point(position.x,
				position.y - head->getSprite()->getBoundingBox().size.height));
			parts.push_back(tempPart);
		}
		else
		{
			tempPart = new Part(layer, "body", Point(lastPosition.x,
				lastPosition.y - head->getSprite()->getBoundingBox().size.height));
			parts.push_back(tempPart);
		}
	}
	else if (direction == "down")
	{
		directions.insert(directionIterator, "down");
		if (parts.size() == 0)
		{
			tempPart = new Part(layer, "body", Point(position.x,
				position.y + head->getSprite()->getBoundingBox().size.height));
			parts.push_back(tempPart);
		}
		else
		{
			tempPart = new Part(layer, "body", Point(lastPosition.x,
				lastPosition.y + head->getSprite()->getBoundingBox().size.height));
			parts.push_back(tempPart);
		}
	}
}

int Snake::getScore()
{
	return score;
}
