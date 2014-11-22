#ifndef __TP_ACTION_SINE_H__
#define __TP_ACTION_SINE_H__


#include "cocos2d.h"
USING_NS_CC;
class ActionSineCurve :public MoveBy{

public:

	static ActionSineCurve* create(float duration, const Vec2& deltaPosition);

	
	ActionSineCurve* clone() const;

	virtual void update(float time) override;
	
	void startWithTarget(Node *target);

	ActionSineCurve* reverse() const;

private:
	bool initWithDuration(float duration, const Vec2& deltaPosition);
};






#endif