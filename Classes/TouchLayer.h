#ifndef __TP_GAME_TOUCH_H__
#define __TP_GAME_TOUCH_H__


#include "cocos2d.h"
#include "TouchDelegate.h"


USING_NS_CC;

class TouchLayer :public Layer{

public:
	virtual bool init() override;

	CREATE_FUNC(TouchLayer);
	
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;

	CC_SYNTHESIZE(TouchDelegate*, touchDeleageted, Delegator);
};

#endif