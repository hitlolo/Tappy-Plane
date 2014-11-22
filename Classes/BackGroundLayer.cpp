
#include "BackGroundLayer.h"


bool BackGroundLayer::init()
{


	if (!Layer::init())
	{
		return false;
	}

	
	this->addBackGround();
	
	return true;
}


void BackGroundLayer::addBackGround()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();


	auto backGround = Sprite::createWithSpriteFrameName(JsonReader::getInstance()->getPathFromJson("background"));
	backGround->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->addChild(backGround);
}