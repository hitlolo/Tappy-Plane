#ifndef __TP_MENU_H__
#define __TP_MENU_H__

#include "cocos2d.h"
#include "BackGroundLayer.h"
#include "Stratosphere.h"
#include "BulletinBoard.h"



USING_NS_CC;

class MenuScene :public Layer{

public:
	
	static Scene* createScene();

	CREATE_FUNC(MenuScene);

	virtual bool init() override;

private:

	void addGameLayers();
};

#endif