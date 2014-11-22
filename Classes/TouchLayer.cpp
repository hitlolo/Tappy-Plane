#include "TouchLayer.h"

bool TouchLayer::init(){

	if (!Layer::init()){
		return false;
	}

	this->setTouchEnabled(true);
	this->setSwallowsTouches(true);

	return true;

}

void TouchLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{

	this->getDelegator()->onTouch();

}