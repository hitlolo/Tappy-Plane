
#ifndef __TP_GAME_H__
#define __TP_GAME_H__


#include "cocos2d.h"
#include "JsonReader.h"
#include "BackGroundLayer.h"
#include "Stratosphere.h"
#include "BulletinBoard.h"
#include "TouchLayer.h"
#include "StarSprite.h"

USING_NS_CC;

class GameScene :public Layer,TouchDelegate{

public:
	
	static Scene* createScene();

	CREATE_FUNC(GameScene);

	virtual bool init() override;
	
	virtual void onTouch() override;

	void runByState(GAME_STATE);

	void updateScore();

private:

	Size  visibleSize;

	Point originPoint;
	
	void addGameLayers();

	void addPhysicsContactListener();

	bool onContact(PhysicsContact& contact);

	void readyGame();

	void startGame(); 

	void overGame();

	void updateStarAcount();
	//³¬Ç°ÒýÓÃ
	class BackGroundLayer  *backLayer;

	Stratosphere           *stratoLayer;

	BulletinDelegate       *bulletinDelegator;

	~GameScene();

};


#endif
