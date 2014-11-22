
#ifndef __TP_BACK_LAYER_H__
#define __TP_BACK_LAYER_H__

#include "JsonReader.h"
#include "cocos2d.h"
#include "ActionEllipse.h"
#include "ActionRotation.h"
#include "ActionSineCurve.h"

USING_NS_CC;

class BackGroundLayer : public Layer{

public:
	
	virtual bool init() override;

	CREATE_FUNC(BackGroundLayer);
	
private:

	void addBackGround();
};


#endif
