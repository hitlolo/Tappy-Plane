
#include "Stratosphere.h"


bool Stratosphere::init()
{

	if (!Layer::init()){
		return false;
	}

	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	cloudAcount = RandomCacher::getInstance()->getRandomByRange(5,8);  //cloud numbers need to show
	
	this->addClouds();
	this->addPlane();

	return true;
}



void  Stratosphere::addClouds()
{

	for (int i = 0; i < cloudAcount; i++){

		auto cloud = createCloud();

		this->cloudVector.pushBack(cloud);
		this->addChild(cloud, this->getRandomZorder());
	}

}

Sprite*  Stratosphere::createCloud()
{

	std::string filename = JsonReader::getInstance()->getPathFromJson("cloud");
	auto cloud = Sprite::createWithSpriteFrameName(filename);
	cloud->setPosition(getRandomPosition().x, getRandomPosition().y);
	float *speed = new float(this->getRandomSpeed());

	cloud->setUserData(speed);
#if 0
	CCLOG("%s:%f", "cloud position!!!", cloud->getPosition().x);
	CCLOG("%f:random scale", this->getRandomScale());
	CCLOG("%s:%f", "cloud speed!", *(float*)(cloud->getUserData()));
#endif

	cloud->setScale(this->getRandomScale());
	cloud->setOpacity(this->getRandomOpacity());
	//cloud->setRotation(this->getRandomRotation());
	return cloud;
	
}


Point Stratosphere::getRandomPosition()
{

	float positionX = RandomCacher::getInstance()->getRandomByRange(originPoint.x, originPoint.x + visibleSize.width);
	float positionY = RandomCacher::getInstance()->getRandomByRange(originPoint.y + visibleSize.height / 2, originPoint.y + visibleSize.height);
	Point point = ccp(positionX, positionY);
#if 0
	CCLOG("%f:random x,%f:random y******************", point.x, point.y);
#endif

	
	return point;
}

int  Stratosphere::getRandomOpacity()
{
	return RandomCacher::getInstance()->getRandomByRange(60, 170);
}

int  Stratosphere::getRandomZorder()
{

	return RandomCacher::getInstance()->getRandomByRange(0, 2);

}

float  Stratosphere::getRandomScale()
{
	return RandomCacher::getInstance()->getRandomByRange(0.2f, 0.5f);
}

float Stratosphere::getRandomSpeed()
{
	return RandomCacher::getInstance()->getRandomByRange(0.4f, 1.5f);
}


float  Stratosphere::getRandomRotation()
{
	int rotation = RandomCacher::getInstance()->getRandomByRange(0, 1);
	switch (rotation){
	case 0:
		return 0.0f;
		break;
	case 1:
		return 180.0f;
		break;
	default:
		return 0.0f;
		break;
	}

}

void  Stratosphere::cloudScroll()
{

	for (auto cloud : this->cloudVector) {
		cloud->setPositionX(cloud->getPositionX() - *(float*)(cloud->getUserData()));
#if 0
		CCLOG("%s:%f", "cloud position", cloud->getPosition().x);
#endif
		if (cloud->getPositionX() < -(cloud->getContentSize().width)) {
			Point nextPosition = getRandomPosition();
			cloud->setPosition(visibleSize.width + nextPosition.x, nextPosition.y);
			*(float*)(cloud->getUserData()) = this->getRandomSpeed();
			cloud->setScale(getRandomScale());
			cloud->setOpacity(getRandomOpacity());
		}

	}
}

void Stratosphere::update(float dt)
{

	//scroll clouds and added puff
	switch (this->getCurGameState())
	{

	case GAME_STATE::MENU:
		this->cloudScroll();
		this->puffScrollOut();
		break;
	case GAME_STATE::READY:
	case GAME_STATE::GAMING:
		this->cloudScroll();
		this->puffScrollOut();
		break;
	case GAME_STATE::OVER:
		break;
	default:
		break;
	}
	

}


void Stratosphere::startScrolling()
{
	/* typedef void (Ref::*SEL_SCHEDULE)(float);
	** #define CC_SCHEDULE_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)
	*/
	
	this->scheduleUpdate();
}


void Stratosphere::stopScrolling()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(Stratosphere::createPuff));
	this->unscheduleUpdate();
}


void Stratosphere::addPlane()
{

	planeSprite = PlaneSprite::create();
	this->addChild(planeSprite,3);
	
}

void  Stratosphere::runByState(GAME_STATE state)
{
	this->setCurGameState(state);
	switch (state)
	{

	case GAME_STATE::MENU:
		startGameMenu();
		break;
	case GAME_STATE::READY:
		startGameReady();
		break;
	case GAME_STATE::GAMING:
		startGameIng();
		break;
	case GAME_STATE::OVER:
		startGameOver();
		break;

	}
	
}

void Stratosphere::startGameMenu()
{
	this->startScrolling();
	this->schedule(CC_SCHEDULE_SELECTOR(Stratosphere::createPuff), 0.2f);
	this->getPlaneSprite()->runByState(PLANE_STATE::STATE_IDEL);
}

void Stratosphere::startGameReady()
{
	this->startScrolling();
	this->schedule(CC_SCHEDULE_SELECTOR(Stratosphere::createPuff), 0.2f);
	this->getPlaneSprite()->runByState(PLANE_STATE::STATE_READY);
}

void Stratosphere::startGameIng()
{
	this->getPlaneSprite()->runByState(PLANE_STATE::STATE_GAME);
}

void Stratosphere::startGameOver()
{
	this->stopScrolling();
	this->getPlaneSprite()->runByState(PLANE_STATE::STATE_CRASH);
}

void Stratosphere::createPuff(float delta)
{

	std::string file_name;
	Animation* puffAnimation = Animation::create();

	file_name = JsonReader::getInstance()->getPathFromJson("puff1");

	auto puffSprite = Sprite::createWithSpriteFrameName(file_name);
	puffSprite->setRotation(this->planeSprite->getRotation());	
	puffSprite->setPosition(planeSprite->getPosition().x - planeSprite->getContentSize().width/3 + 20, planeSprite->getPosition().y - planeSprite->getContentSize().height/3 + 20);
	
	FiniteTimeAction* scalePuff = ScaleTo::create(5.0f, 0.0f);
	FiniteTimeAction* fadePuff  = FadeOut::create(5.0f);
	puffSprite->runAction(Spawn::create(scalePuff,fadePuff,nullptr));
	this->puffVector.pushBack(puffSprite);
	this->addChild(puffSprite,0);
	
}

void Stratosphere::puffScrollOut()
{
	if (puffVector.empty())
		return;

	Vector<Sprite*> puffEraseVector;
	for (auto puff : this->puffVector)
	{

		if ((puff->getPositionX() < -(puff->getContentSize().width)) || puff->getOpacity() <= 0)
		{
			puffEraseVector.pushBack(puff);
		}
		else
			puff->setPositionX(puff->getPositionX() - 1.0f);
	}

	if (puffEraseVector.empty())
		return;
	else
	{
		for (auto puff : puffEraseVector)
		{
			
			puffVector.eraseObject(puff);
			this->removeChild(puff);
		}
	}
}



void Stratosphere::onExit()
{
	Layer::onExit();
	this->stopScrolling();

}

Stratosphere::~Stratosphere()
{
	//what have been newed! need to be deleted!
	for (auto cloud : this->cloudVector) {
		float* ptr = (float*)(cloud->getUserData());
		CC_SAFE_DELETE(ptr);
	}
	cloudVector.clear();
	puffVector.clear();
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}

