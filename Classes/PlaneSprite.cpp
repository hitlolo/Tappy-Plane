
#include "PlaneSprite.h"

bool PlaneSprite::init()
{
	
	if (!Sprite::init())
	{
		return false;
	}

	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	this->createPlane();
	this->initPhysicsAttributes();
	return true;

}


void PlaneSprite::createPlane()
{
	

	this->initActions();
	this->initPhysicsAttributes();
//	this->runByState(PLANE_STATE::STATE_IDEL);

}

PLANE_COLOR PlaneSprite::getRandomColor()
{
	
	std::random_device rd;
	std::mt19937 mt(rd());
	//std::default_random_engine random_e;
	std::uniform_int_distribution<int> dist_color(0, 3);
	return (PLANE_COLOR)dist_color(mt);
}

void PlaneSprite::initActions()
{
	PLANE_COLOR color;

	color = getRandomColor();
	actionIdle    = this->initIdleActionByColor(color);
	actionEllipse = this->initEllipseAction();
	actionSwing   = this->initSwingAction();

	

}

Action* PlaneSprite::initIdleActionByColor(PLANE_COLOR color)
{
	
	std::string file_name;
	std::string file_format;
	switch (color)
	{
		case PLANE_COLOR::BLUE:
			file_name = JsonReader::getInstance()->getPathFromJson("plane_blue_1");
			file_format = "plane_blue_%d";
			break;
		case PLANE_COLOR::GREEN:
			file_name = JsonReader::getInstance()->getPathFromJson("plane_green_1");
			file_format = "plane_green_%d";
			break;
		case PLANE_COLOR::RED:
			file_name = JsonReader::getInstance()->getPathFromJson("plane_red_1");
			file_format = "plane_red_%d";
			break;
		case PLANE_COLOR::YELLOW:
			file_name = JsonReader::getInstance()->getPathFromJson("plane_yellow_1");
			file_format = "plane_yellow_%d";
			break;
	}

	this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name));
	
	int img_count = 2;

	Animation* animation = Animation::create();
	for (int i = 0; i < img_count; i++)
	{
		String* file_name  = String::createWithFormat(file_format.c_str(), i + img_count);
		std::string file   = JsonReader::getInstance()->getPathFromJson(file_name->getCString());
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	Animate* animate = Animate::create(animation);
	//bind
	return( RepeatForever::create(animate) );

}

Action* PlaneSprite::initEllipseAction()
{
	EllipseConfig config;
	config.center = Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 10 * 7);
	config.a = 240;
	config.b = 120;
	config.angle = CC_DEGREES_TO_RADIANS(-45);
	config.isAnticlockwise = false;
	config.zOrder = std::make_pair(1, 3);
	auto moveAction = RepeatForever::create(ActionEllipse::create(10.0, config));
	/*cloud->runAction(RepeatForever::create(moveAction));*/
	auto rotationAction = ActionRotation::create(moveAction);

	return rotationAction;
}

Action* PlaneSprite::initSwingAction()
{
	// create the swing action
	ActionInterval* up = CCMoveBy::create(0.4f, Point(0, 8));
	ActionInterval* upBack = up->reverse();
	//bind
	return( RepeatForever::create(Sequence::create(up, upBack, nullptr)) );
}


void PlaneSprite::initPhysicsAttributes()
{


	PhysicsBody *body = PhysicsBody::create();
	ShapeCacher::getInstance()->addShapesWithFile("planeShape.plist", body);
	body->setCategoryBitmask(COLLIDER_TYPE_PLANE);
	body->setCollisionBitmask(COLLIDER_TYPE_LAND | COLLIDER_TYPE_ROCK);
	body->setContactTestBitmask(COLLIDER_TYPE_LAND | COLLIDER_TYPE_ROCK);

	body->setDynamic(true);
	body->setLinearDamping(1.0f);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);


}


void PlaneSprite::idle()
{
	this->stopAllActions();
	this->getPhysicsBody()->setGravityEnable(false);
	this->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->runAction(this->actionIdle);
	this->runAction(this->actionEllipse);

}


void PlaneSprite::ready()
{
	this->stopAllActions();
	this->setZOrder(1);  //make plane can cover by  clouds randomly.
	this->runAction(this->actionIdle);
	this->runAction(this->actionSwing);
	this->setPosition(originPoint.x + visibleSize.width / 4, originPoint.y + visibleSize.height / 2);
	this->getPhysicsBody()->setGravityEnable(false);	
}

void PlaneSprite::gaming()
{
	this->getPhysicsBody()->setGravityEnable(true);
	this->scheduleUpdate();
}

void PlaneSprite::crash()
{
	
	this->unscheduleUpdate();
	this->stopAllActions();
	this->getPhysicsBody()->setGravityEnable(true);
	this->setRotation(90);
	this->runAction(FadeOut::create(0.9f));
}

void PlaneSprite::runByState(PLANE_STATE state)
{

	this->setCurState(state);

	switch (state)
	{
		case PLANE_STATE::STATE_IDEL:
			this->idle();
			break;
		case PLANE_STATE::STATE_READY:
			this->ready(); 
			break;
		case PLANE_STATE::STATE_GAME:
			this->gaming();
			break;
		case PLANE_STATE::STATE_CRASH:
			this->crash();
			break;
	}
}

void PlaneSprite::update(float time)
{

	//set the angle of the bird depends on the velocity.
	this->setRotation(this->getPhysicsBody()->getVelocity().y*-0.1);
}

void PlaneSprite::flyUp()
{
	this->getPhysicsBody()->setVelocity(VELOCITY);
}