
#include "Stratosphere.h"


bool Stratosphere::init()
{

	if (!Layer::init()){
		return false;
	}

	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	cloudAcount = 5;  //cloud numbers need to show
	
	this->addClouds();
	this->addPlane();
	/*this->runByState(MENU);*/



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
	//C++11 new random
	//std::random_device rd;
//	std::mt19937 mt(rd());
//	std::default_random_engine random_e;
//	std::uniform_int_distribution<int> dist_x(originPoint.x, originPoint.x+visibleSize.width);
//	std::uniform_int_distribution<int> dist_y(originPoint.y + visibleSize.height / 2, originPoint.y + visibleSize.height);
	float positionX = this->getRandomByRange(originPoint.x, originPoint.x + visibleSize.width);
	float positionY = this->getRandomByRange(originPoint.y + visibleSize.height / 2, originPoint.y + visibleSize.height);
	Point point = ccp(positionX, positionY);
#if 0
	CCLOG("%f:random x,%f:random y******************", point.x, point.y);
#endif

	
	return point;
}

int  Stratosphere::getRandomOpacity()
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	////	std::default_random_engine random_e;
	//std::uniform_int_distribution<int> dist_o(60, 170);

	return getRandomByRange(60,170);
}

int  Stratosphere::getRandomZorder()
{

//	std::default_random_engine random_e;
	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::uniform_int_distribution<int> dist_z(0, 2);

#if 0
	CCLOG("%d:random zorder", dist_z(mt));
#endif
	return getRandomByRange(0, 2);

}

float  Stratosphere::getRandomScale()
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	///*std::uniform_int_distribution<int> dist_s(2, 5);
	//return float(dist_s(mt)/10.0f);*/
	//std::uniform_real_distribution<float> dist_s(0.2f, 0.5f);
	return getRandomByRange(0.2f, 0.5f);
}

float Stratosphere::getRandomSpeed()
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	////std::default_random_engine random_e;
	//std::uniform_int_distribution<> dist_s(4, 15);
	
#if 0
	CCLOG("%d:random speed", dist_s(mt));
#endif
	return getRandomByRange(0.4f, 1.5f);
}


float  Stratosphere::getRandomRotation()
{
	int rotation = getRandomByRange(0, 1);
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

int Stratosphere::getRandomByRange(int from, int to)
{
	
	std::mt19937 mt(rd());
	//std::default_random_engine random_e;
	std::uniform_int_distribution<int> dist(from, to);
	return dist(mt);
}

float Stratosphere::getRandomByRange(float from, float to)
{
	std::mt19937 mt(rd());
	//std::default_random_engine random_e;
	std::uniform_real_distribution<float> dist(from, to);
	return dist(mt);
}

void Stratosphere::update(float dt)
{
	//add puff


	//scroll cloud and added puff
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
		this->startScrolling();
		this->schedule(CC_SCHEDULE_SELECTOR(Stratosphere::createPuff), 0.2f);
		this->getPlaneSprite()->runByState(PLANE_STATE::STATE_IDEL);
		break;
	case GAME_STATE::READY:
		this->startScrolling();
		this->schedule(CC_SCHEDULE_SELECTOR(Stratosphere::createPuff), 0.2f);
		this->getPlaneSprite()->runByState(PLANE_STATE::STATE_GAME);
		break;
	case GAME_STATE::GAMING:
		this->getPlaneSprite()->runByState(PLANE_STATE::STATE_GAME);
		break;
	case GAME_STATE::OVER:
		this->stopScrolling();
		this->getPlaneSprite()->runByState(PLANE_STATE::STATE_CRASH);
		break;

	}
	
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
	for (auto puff : this->puffVector)
	{
		if (!puff->isRunning())
		{
			puffVector.eraseObject(puff);
			CC_SAFE_RELEASE(puff);
		}
		else
			puff->setPositionX(puff->getPositionX() - 1.0f);
	}

}



void Stratosphere::onExit()
{
	Layer::onExit();
	this->stopScrolling();

}

Stratosphere::~Stratosphere()
{
	

	for (auto cloud : this->cloudVector) {
		float* ptr = (float*)(cloud->getUserData());
		CC_SAFE_DELETE(ptr);
	}
	cloudVector.clear();
	puffVector.clear();
}

