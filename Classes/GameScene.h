
#ifndef __TP_GAME_H__
#define __TP_GAME_H__


#include "cocos2d.h"
#include "JsonReader.h"
#include "BackGroundLayer.h"
#include "Stratosphere.h"
#include "BulletinBoard.h"
#include "TouchLayer.h"

USING_NS_CC;

class GameScene :public Layer,TouchDelegate{

public:
	
	static Scene* createScene();

	virtual bool init() override;
	
	virtual void onTouch() override;

	CREATE_FUNC(GameScene);

	void runByState(GAME_STATE);

private:

	
	void addGameLayers();

	BackGroundLayer  *backLayer;

	Stratosphere     *stratoLayer;

	BulletinDelegate *bulletinDelegator;

};


#endif
