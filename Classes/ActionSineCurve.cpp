
#include "ActionSineCurve.h"

ActionSineCurve* ActionSineCurve::create(float duration, const Vec2& deltaPosition)
{
	ActionSineCurve *ret = new (std::nothrow) ActionSineCurve();
	ret->initWithDuration(duration, deltaPosition);
	ret->autorelease();

	return ret;
}

bool ActionSineCurve::initWithDuration(float duration, const Vec2& deltaPosition)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_positionDelta = deltaPosition;
		return true;
	}

	return false;
}

ActionSineCurve* ActionSineCurve::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) ActionSineCurve();
	a->initWithDuration(_duration, _positionDelta);
	a->autorelease();
	return a;
}

void ActionSineCurve::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	_previousPosition = _startPosition = target->getPosition();
}

ActionSineCurve* ActionSineCurve::reverse() const
{
	return ActionSineCurve::create(_duration, Vec2(-_positionDelta.x, -_positionDelta.y));
}



void ActionSineCurve::update(float t)
{

//#if CC_ENABLE_STACKABLE_ACTIONS
		Vec2 currentPos = _target->getPosition();
		Vec2 diff = currentPos - _previousPosition;
		_startPosition = _startPosition + diff;
		Vec2 newPos = _startPosition + (_positionDelta * t);
		/*newPos.y =sin(t) * newPos.x;*/
		_target->setPosition(newPos);
		_previousPosition = newPos;
//#else
//		_target->setPosition(_startPosition + _positionDelta * t);
//#endif // CC_ENABLE_STACKABLE_ACTIONS

}


