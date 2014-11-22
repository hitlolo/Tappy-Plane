
#include "ActionEllipse.h"


ActionEllipse::ActionEllipse()
{
	_config.a = 0.0f;
	_config.b = 0.0f;
	_config.center = Point(0, 0);
	_config.isAnticlockwise = false;
	_config.zOrder = std::make_pair(0, 0);
}

ActionEllipse* ActionEllipse::create(float dt, const EllipseConfig& config)
{//利用之前定义的椭圆的参数初始化椭圆
	
	ActionEllipse *action = new ActionEllipse();
	action->initWithDurationAndConfig(dt, config);
	action->autorelease();

	return action;
}

bool ActionEllipse::initWithDurationAndConfig(float dt, const EllipseConfig& config)
{
	if (ActionInterval::initWithDuration(dt)){
		_config = config;
		return true;
	}

	return false;
}


/*
** x'= x*cos(n)+y*sin(n) 
** y'=-x*sin(n)+y*cos(n) 
*/

//x = a * cos(t)  t = [0, 2Pi]
float ActionEllipse::getEllipsePositionX(float psai)
{

	if (_config.isAnticlockwise == false){
		return _config.a * cos(2 * M_PI * (1 - psai)) * cos(_config.angle) + _config.b * sin(2 * M_PI * (1 - psai)) * sin(_config.angle);
	}
	else{
		return _config.a * cos(2 * M_PI * psai) * cos(_config.angle) + _config.b * sin(2 * M_PI * (psai)) * sin(_config.angle);;
	}

}

//y = b * sin(t)  t = [0, 2Pi]
float ActionEllipse::getEllipsePositionY(float psai)
{

	if (_config.isAnticlockwise == false){
		return -(_config.a * cos(2 * M_PI * (1 - psai))) * sin(_config.angle) + _config.b * sin(2 * M_PI * (1 - psai)) * cos(_config.angle);
	}
	else{
		return -(_config.a * cos(2 * M_PI * psai)) * sin(_config.angle) + _config.b * sin(2 * M_PI * (psai)) * cos(_config.angle);
	}
}


void ActionEllipse::update(float dt)
{  //t [0, 1]
	
	if (_target){
		float x = getEllipsePositionX(dt);
		float y = getEllipsePositionY(dt);
		Point newPosition = _config.center + Point(x, y);
		_target->setPosition(_config.center + Point(x, y));//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标

		if (dt <= 0.5){
			_target->setLocalZOrder(_config.zOrder.first);
		}
		else{
			_target->setLocalZOrder(_config.zOrder.second);
		}

#if 0
		CCDrawNode *node = CCDrawNode::create();
		node->drawDot(newPosition, 0.5f, ccc4f(17, 128,18, 60));
		_target->getParent()->addChild(node);
#endif

	}



}

ActionEllipse* ActionEllipse::clone() const
{
	auto action = new ActionEllipse();
	action->initWithDurationAndConfig(_duration, _config);
	action->autorelease();
	return action;
}

ActionEllipse* ActionEllipse::reverse() const
{
	EllipseConfig new_config;
	new_config.center = _config.center;
	new_config.a = _config.a;
	new_config.b = _config.b;
	new_config.isAnticlockwise = !(_config.isAnticlockwise);
	new_config.zOrder = _config.zOrder;
	return ActionEllipse::create(_duration, new_config);
}

void ActionEllipse::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
}