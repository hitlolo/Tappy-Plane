
#include "ActionRotation.h"

ActionRotation* ActionRotation::create(Action* action)
{

	ActionRotation* self = new ActionRotation();
	if (self && self->initWithAction(action)){
		self->autorelease();
		return self;
	}
	CC_SAFE_DELETE(self);
	return nullptr;

}

bool ActionRotation::initWithAction(Action* action)
{

	action->retain();
	this->targetAction = action;
	return true;

}

void ActionRotation::startWithTarget(Node* target)
{

#if 0
	CCLOG("HERE I COME!");
#endif
	
	targetNode = target;
	ActionInterval::startWithTarget(target);
	targetAction->startWithTarget(target);

}


bool ActionRotation::isDone() const
{

	return targetAction->isDone();

}

void ActionRotation::step(float dt)
{
	
	Point prePosition = targetNode->getPosition();
	targetAction->step(dt);
	Point curPosition = targetNode->getPosition();

	float tan    =  - (curPosition.y - prePosition.y)  / (curPosition.x - prePosition.x) ;
	float degree = atan(tan);
	float offsetDegree = 0;
	//first quadrant
	if (((curPosition.y - prePosition.y) < 0) && ((curPosition.x - prePosition.x) > 0)){
		offsetDegree = 0;
	}
	//fouth quadrant
	if (((curPosition.y - prePosition.y) < 0) && ((curPosition.x - prePosition.x) < 0)){
		offsetDegree = 180;
	}
	//third quadrant
	if (((curPosition.y - prePosition.y) > 0) && ((curPosition.x - prePosition.x) < 0)){
		offsetDegree = 180;
	}
	//second quadrant
	if (((curPosition.y - prePosition.y) > 0) && ((curPosition.x - prePosition.x) > 0)){
		offsetDegree = 360;
	}
	degree = offsetDegree + CC_RADIANS_TO_DEGREES(degree);
	//degree = offsetDegree + (degree / M_PI * 180);

	targetNode->setRotation(degree);

#if 0
	CCLOG("%f:degree!",degree);
#endif

}

ActionRotation::~ActionRotation()
{

	CC_SAFE_RELEASE(targetAction);

}
