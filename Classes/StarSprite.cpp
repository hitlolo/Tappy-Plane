

#include "StarSprite.h"

bool StarSprite::init()
{

	if (!Sprite::init())
	{
		return false;
	}

	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	initImage();
	initPhysics();
	return true;
}

void StarSprite::initImage()
{
	std::string file_name = JsonReader::getInstance()->getPathFromJson("star_gold");
	this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name));
	
	this->setTag(0);
}

void StarSprite::initPhysics()
{
	PhysicsBody *body = PhysicsBody::create();
	ShapeCacher::getInstance()->addShapesWithFile("starShape.plist", body);
	body->setCategoryBitmask(COLLIDER_TYPE_COIN);
	//	body->setCollisionBitmask(COLLIDER_TYPE_PLANE);
	body->setContactTestBitmask(COLLIDER_TYPE_PLANE);

	body->setDynamic(false);
	body->setLinearDamping(1.0f);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);
}

	
void StarSprite::runStarAction()
{
	this->setTag(1);
	auto move = MoveTo::create(0.6f, Point(-(visibleSize.width - 20), originPoint.y + visibleSize.height - 10));
	auto fade_out = FadeOut::create(0.3f);
	auto call_back = CCCallFunc::create(CC_CALLBACK_0(StarSprite::dispearCallback,this));
	auto my_action = Sequence::create(move, fade_out, call_back, nullptr);
	this->runAction(my_action);
}

void StarSprite::dispearCallback()
{
	this->removeFromParentAndCleanup(true);
}