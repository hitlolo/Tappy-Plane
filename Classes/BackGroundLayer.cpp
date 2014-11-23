
#include "BackGroundLayer.h"


bool BackGroundLayer::init()
{


	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	originPoint = Director::getInstance()->getVisibleOrigin();
	
	addElementsByState();

	return true;
}


void BackGroundLayer::addElementsByState()
{
	this->setCurState(GameController::getInstance()->getCurState());

	switch (curState)
	{
	case GAME_STATE::MENU:
		this->addBackGround();
		break;
	case GAME_STATE::READY:
	case GAME_STATE::GAMING:
		this->addBackGround();
		this->addLand();
		this->scheduleUpdate();
		break;
	default:
		break;
	}

}

void BackGroundLayer::addBackGround()
{
	auto backGround = Sprite::createWithSpriteFrameName(JsonReader::getInstance()->getPathFromJson("background"));
	backGround->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->addChild(backGround);
}

void BackGroundLayer::addLand()
{

	this->setCurLandType((LAND_TYPE)this->getRandomLand());
	std::string file_name;

	switch (getCurLandType())
	{
	case LAND_TYPE::GRASS:
		file_name = JsonReader::getInstance()->getPathFromJson("land_grass");
		break;
	case LAND_TYPE::DIRT:
		file_name = JsonReader::getInstance()->getPathFromJson("land_dirt");
		break;
	case LAND_TYPE::ROCK:
		file_name = JsonReader::getInstance()->getPathFromJson("land_rock");
		break;
	case LAND_TYPE::SNOW:
		file_name = JsonReader::getInstance()->getPathFromJson("land_snow");
		break;
	case LAND_TYPE::ICE:
		file_name = JsonReader::getInstance()->getPathFromJson("land_ice");
		break;
	}

	auto land_f = Sprite::createWithSpriteFrameName(file_name);
	auto land_s = Sprite::createWithSpriteFrameName(file_name);
	land_f->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + land_f->getContentSize().height / 2);
	land_s->setPosition(originPoint.x + visibleSize.width / 2 + land_f->getContentSize().width, originPoint.y + land_f->getContentSize().height / 2);

	auto groundBody_f = PhysicsBody::create();
	ShapeCacher::getInstance()->addShapesWithFile("groundShape.plist", groundBody_f);
	groundBody_f->setDynamic(false);
	groundBody_f->setGravityEnable(false);
	groundBody_f->setLinearDamping(0.0f);
	groundBody_f->setCategoryBitmask(COLLIDER_TYPE_LAND);
	groundBody_f->setCollisionBitmask(COLLIDER_TYPE_PLANE);
	groundBody_f->setContactTestBitmask(COLLIDER_TYPE_PLANE);
	land_f->setPhysicsBody(groundBody_f);

	auto groundBody_s = PhysicsBody::create();
	ShapeCacher::getInstance()->addShapesWithFile("groundShape.plist", groundBody_s);
	groundBody_s->setDynamic(false);
	groundBody_s->setGravityEnable(false);
	groundBody_s->setLinearDamping(0.0f);
	groundBody_s->setCategoryBitmask(COLLIDER_TYPE_LAND);
	groundBody_s->setCollisionBitmask(COLLIDER_TYPE_PLANE);
	groundBody_s->setContactTestBitmask(COLLIDER_TYPE_PLANE);
	land_s->setPhysicsBody(groundBody_s);

	//

	this->landVector.pushBack(land_f);
	this->landVector.pushBack(land_s);
	this->addChild(land_f);
	this->addChild(land_s);
	

}


void BackGroundLayer::addRocks()
{

}

void BackGroundLayer::landScrolling()
{
	for (auto land : landVector)
	{

		land->setPositionX(land->getPositionX() - 1.0f);
		float position_x = land->getPositionX();
		if (position_x < -(land->getContentSize().width / 2))
		{
			land->setPositionX(originPoint.x + visibleSize.width / 2 + land->getContentSize().width);
		}
	}
}


void BackGroundLayer::rockScrolling(){}





int  BackGroundLayer::getRandomLand()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	//std::default_random_engine random_e;
	std::uniform_int_distribution<int> dist(0, 4);
	return dist(mt);

}

void  BackGroundLayer::update(float time)
{
	this->landScrolling();

	switch (curState)
	{

	case GAME_STATE::MENU:
		return;
		break;
	case GAME_STATE::READY:
		this->landScrolling();
		break;
	case GAME_STATE::GAMING:
		this->landScrolling();
		this->rockScrolling();
		break;
	case GAME_STATE::OVER:
		return;
		break;
	}

}