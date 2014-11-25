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

	virtual bool init() override;

	void startScrolling();

	void runByState(GAME_STATE);

	CREATE_FUNC(Stratosphere);

	CC_SYNTHESIZE(PlaneSprite*, planeSprite, PlaneSprite);

	CC_SYNTHESIZE(GAME_STATE, curGameState, CurGameState);

private:

	Point originPoint;

	Size  visibleSize;

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

	void    stopScrolling();

	virtual void update(float dt) override;

	//plane
	void    addPlane();
	//puff
	Vector<Sprite*> puffVector;

	void createPuff(float delta);

	void puffScrollOut();

	//deconstructor delete usrdata
	void onExit() override;

	~Stratosphere();
};


#endif