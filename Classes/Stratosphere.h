#ifndef __TP_STRATO_LAYER_H__
#define __TP_STRATO_LAYER_H__

#include "cocos2d.h"
#include "JsonReader.h"
#include <random>
#include "PlaneSprite.h"
#include "RandomCacher.h"


USING_NS_CC;

class Stratosphere :public Layer{

public:

	CREATE_FUNC(Stratosphere);

	virtual bool init() override;

	void runByState(GAME_STATE);

	CC_SYNTHESIZE(PlaneSprite*, planeSprite, PlaneSprite);

private:
	
	Point originPoint;

	Size  visibleSize;

	CC_SYNTHESIZE(GAME_STATE, curGameState, CurGameState);

	//clouds
	//decide how many clouds need to show
	int   cloudAcount;

	Vector<Sprite*> cloudVector;

	void    addClouds();

	Sprite* createCloud();

	Point   getRandomPosition();

	int     getRandomOpacity();

	int     getRandomZorder();

	float   getRandomScale();

	float   getRandomSpeed();

	float   getRandomRotation();

	void    cloudScroll();

	void    startScrolling();

	void    stopScrolling();

	virtual void update(float dt) override;

	//plane
	void    addPlane();
	//puff
	Vector<Sprite*> puffVector;

	void createPuff(float delta);

	void puffScrollOut();

	//controll

	void startGameMenu();

	void startGameReady();

	void startGameIng();

	void startGameOver();

	//deconstructor delete usrdata
	void onExit() override;

	~Stratosphere();
};


#endif