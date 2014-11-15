#ifndef __TP_LOAD_H__
#define __TP_LOAD_H__

#include "cocos2d.h"
#include "JsonReader.h"

USING_NS_CC;

class LogoScene:public Layer{


public:

	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(LogoScene);

private:

	void loadRes();
};











#endif
