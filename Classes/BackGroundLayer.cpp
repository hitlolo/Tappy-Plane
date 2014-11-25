
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

void  BackGroundLayer::runByState(GAME_STATE state)
{

	this->setCurState(state);

	switch (curState)
	{
	case GAME_STATE::MENU:
		return;
		break;
	case GAME_STATE::READY:
		this->scheduleUpdate();
		break;
	case GAME_STATE::GAMING:
		this->schedule(CC_SCHEDULE_SELECTOR(BackGroundLayer::addRocks), 3.2f);
		break;
	case GAME_STATE::OVER:
		this->unschedule(CC_SCHEDULE_SELECTOR(BackGroundLayer::addRocks));
		this->unscheduleUpdate();
	default:
		return;
	}
}

void BackGroundLayer::addBackGround()
{
	auto backGround = Sprite::createWithSpriteFrameName(JsonReader::getInstance()->getPathFromJson("background"));
	backGround->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->addChild(backGround);
}

int  BackGroundLayer::getRandomLandType()
{
	int land_type = RandomCacher::getInstance()->getRandomByRange(0, 4);
	return land_type;

}

void BackGroundLayer::addLand()
{

	this->setCurLandType((LAND_TYPE)this->getRandomLandType());
	std::string file_name;

	switch (getCurLandType())
	{
	case LAND_TYPE::ROCK:
	case LAND_TYPE::GRASS:
		file_name = JsonReader::getInstance()->getPathFromJson("land_grass");
		break;
	case LAND_TYPE::DIRT:
		file_name = JsonReader::getInstance()->getPathFromJson("land_dirt");
		break;
	//too ugly
	//case LAND_TYPE::ROCK:
	//	file_name = JsonReader::getInstance()->getPathFromJson("land_rock");
	//	break;
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
	land_s->setPosition(originPoint.x + visibleSize.width / 2 + land_f->getContentSize().width - 5, originPoint.y + land_f->getContentSize().height / 2);

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
	this->addChild(land_f,3);
	this->addChild(land_s,3);
	
	
	//prepare for add rocks
	this->setRockNameAfterLandAdded();
}

void  BackGroundLayer::setRockNameAfterLandAdded()
{
	switch (getCurLandType())
	{
	case LAND_TYPE::DIRT:
		rockNameUp   = JsonReader::getInstance()->getPathFromJson("rock_dirt_up");
		rockNameDown = JsonReader::getInstance()->getPathFromJson("rock_dirt_down");
		break;
	case LAND_TYPE::ROCK:
	case LAND_TYPE::GRASS:
		rockNameUp   = JsonReader::getInstance()->getPathFromJson("rock_grass_up");
		rockNameDown = JsonReader::getInstance()->getPathFromJson("rock_grass_down");
		break;
	case LAND_TYPE::SNOW:
		rockNameUp   = JsonReader::getInstance()->getPathFromJson("rock_snow_up");
		rockNameDown = JsonReader::getInstance()->getPathFromJson("rock_snow_down");
		break;
	case LAND_TYPE::ICE:
		rockNameUp   = JsonReader::getInstance()->getPathFromJson("rock_ice_up");
		rockNameDown = JsonReader::getInstance()->getPathFromJson("rock_ice_down");
		break;

	}

}

int   BackGroundLayer::getRandomRockType()
{
	int rock_type = RandomCacher::getInstance()->getRandomByRange(0, 4);
	return rock_type;

}

Node* BackGroundLayer::createRockByType(ROCK_TYPE type)
{
	Node* rock = nullptr;
	switch (type)
	{
	case ROCK_TYPE::SINGLE_DOWN:
		rock = rockSingleDown();
		break;
	case ROCK_TYPE::SINGLE_UP:
		rock = rockSingleUp();
		break;
	case ROCK_TYPE::UP_DOWN:
		rock = rockUpandDown();
		break;
	case ROCK_TYPE::TWINS_UP:
		rock = rockTwinsUp();
		break;
	case ROCK_TYPE::TWINS_DOWN:
		rock = rockTwinsDown();
		break;
	}
	return rock;
}

void  BackGroundLayer::initRockPhysics(Node* rock,bool is_up)
{
	auto rockBody = PhysicsBody::create();
	if (is_up)
	{
		ShapeCacher::getInstance()->addShapesWithFile("rockShape.plist", rockBody);
	}
	else if (!is_up)
	{
		ShapeCacher::getInstance()->addShapesWithFile("rockDownShape.plist", rockBody);
	}	
	rockBody->setDynamic(false);
	rockBody->setGravityEnable(false);
	rockBody->setLinearDamping(0.0f);
	rockBody->setCategoryBitmask(COLLIDER_TYPE_ROCK);
	rockBody->setCollisionBitmask(COLLIDER_TYPE_PLANE);
	rockBody->setContactTestBitmask(COLLIDER_TYPE_PLANE);
	rock->setPhysicsBody(rockBody);
}

Node*  BackGroundLayer::rockSingleDown()
{
	auto rock = Sprite::createWithSpriteFrameName(this->rockNameUp);
	this->initRockPhysics(rock,true);
	float x = originPoint.x + visibleSize.width + rock->getContentSize().width / 2;
	float y = RandomCacher::getInstance()->getRandomByRange(70.0F, rock->getContentSize().height/2);
	rock->setPosition(x, y);
	return rock;
}

Node*  BackGroundLayer::rockSingleUp()
{
	auto rock = Sprite::createWithSpriteFrameName(this->rockNameDown);
	this->initRockPhysics(rock, false);
	float x = originPoint.x + visibleSize.width + rock->getContentSize().width / 2;
	float from = originPoint.y + visibleSize.height - rock->getContentSize().height / 2;
	float to   = originPoint.y + visibleSize.height - rock->getContentSize().height / 2 + 20;
	float y = RandomCacher::getInstance()->getRandomByRange(from,to);
	rock->setPosition(x, y);
	return rock;

}

Node*  BackGroundLayer::rockUpandDown()
{
	auto rockNode = Node::create();
	auto rockUp   = Sprite::createWithSpriteFrameName(this->rockNameUp);
	auto rockDown = Sprite::createWithSpriteFrameName(this->rockNameDown);
	this->initRockPhysics(rockUp, true);
	this->initRockPhysics(rockDown, false);
	
	rockUp->setPosition(0, -(rockUp->getContentSize().height/2));
	rockDown->setPosition(0, THROUGH_PASS + rockDown->getContentSize().height/2);
	rockNode->addChild(rockUp);
	rockNode->addChild(rockDown);

	float x = originPoint.x + visibleSize.width + rockNode->getContentSize().width / 2;
	float y = visibleSize.height / 2 - RandomCacher::getInstance()->getRandomByRange(0, 120);;

	rockNode->setPosition(x, y);
	rockNode->setContentSize(rockUp->getContentSize());
	return rockNode;
}

Node*  BackGroundLayer::rockTwinsUp()
{
	auto rockNode = Node::create();
	auto rock_f = Sprite::createWithSpriteFrameName(this->rockNameDown);
	auto rock_s = Sprite::createWithSpriteFrameName(this->rockNameDown);
	this->initRockPhysics(rock_f, false);
	this->initRockPhysics(rock_s, false);
	float scale = RandomCacher::getInstance()->getRandomByRange(0.5f, 1.2f);
	rock_s->setScale(scale);
	rock_s->setPositionX(rock_f->getContentSize().width / 2);
	rock_s->setPositionY(rock_f->getContentSize().height / 2 - rock_s->getContentSize().height * scale / 2 );
	
	rockNode->addChild(rock_f);
	rockNode->addChild(rock_s);
	rockNode->setContentSize(rock_f->getContentSize());
	float x = originPoint.x + visibleSize.width + rockNode->getContentSize().width / 2;
	float y = originPoint.y + visibleSize.height - rockNode->getContentSize().height / 2;
	rockNode->setPosition(x,y);
	rockNode->setContentSize(rock_f->getContentSize() * 2);
	return rockNode;
}

Node*  BackGroundLayer::rockTwinsDown()
{
	auto rockNode = Node::create();
	auto rock_f = Sprite::createWithSpriteFrameName(this->rockNameUp);
	auto rock_s = Sprite::createWithSpriteFrameName(this->rockNameUp);
	this->initRockPhysics(rock_f, true);
	this->initRockPhysics(rock_s, true);
	float scale = RandomCacher::getInstance()->getRandomByRange(0.5f, 1.4f);
	rock_s->setScale(scale);
	rock_s->setPositionX(rock_f->getContentSize().width / 2);
	rock_s->setPositionY(-(rock_f->getContentSize().height / 2) + rock_s->getContentSize().height * scale / 2);

	rockNode->addChild(rock_f);
	rockNode->addChild(rock_s);
	rockNode->setContentSize(rock_f->getContentSize());
	float x = originPoint.x + visibleSize.width + rockNode->getContentSize().width / 2;
	float y = RandomCacher::getInstance()->getRandomByRange(70.0F, rockNode->getContentSize().height / 2);;
	rockNode->setPosition(x, y);
	rockNode->setContentSize(rock_f->getContentSize() * 2);
	return rockNode;
}

void BackGroundLayer::addRocks(float time)
{
	ROCK_TYPE type = static_cast<ROCK_TYPE>(this->getRandomRockType());

	auto rock = this->createRockByType(type);
	this->rockVector.pushBack(rock);
	this->addChild(rock,2);

}

void BackGroundLayer::landScrolling()
{
	for (auto land : landVector)
	{

		land->setPositionX(land->getPositionX() - 1.0f);
		float position_x = land->getPositionX();
		if (position_x < -(land->getContentSize().width / 2))
		{
			land->setPositionX(originPoint.x + visibleSize.width / 2 + land->getContentSize().width - 5);
		}
	}
}


void BackGroundLayer::rockScrolling()
{
	if (rockVector.empty())
		return;

	Vector<Node*> rockEraser;
	for (auto rock : rockVector)
	{
		float position_x = rock->getPositionX();
		rock->setPositionX(rock->getPositionX() - 1.8f);

		if (position_x < -(rock->getContentSize().width /2))
		{
			rockEraser.pushBack(rock);
		}
		
			
	}

	if (rockEraser.empty())
		return;
	else
	{
		for (auto rock : rockEraser)
		{
			CCLOG("%f,!!!%f,%f!", rock->getPositionX(), rock->getContentSize().width, rock->getContentSize().height);
			rockVector.eraseObject(rock);
			this->removeChild(rock);
		}
	}
}

void  BackGroundLayer::update(float time)
{

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

BackGroundLayer::~BackGroundLayer()
{
	this->landVector.clear();
	this->rockVector.clear();
}