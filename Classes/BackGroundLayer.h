
#ifndef __TP_BACK_LAYER_H__
#define __TP_BACK_LAYER_H__

#include "JsonReader.h"
#include "cocos2d.h"
#include "Data.h"
#include "GameController.h"
#include "ShapeCacher.h"
#include "RandomCacher.h"
#include "StarLayer.h"

USING_NS_CC;

typedef enum class land_type{
	GRASS = 0,
	DIRT,
	SNOW,
	ICE,
	ROCK
}LAND_TYPE;

typedef enum class rock_type{
	SINGLE_UP = 0,
	SINGLE_DOWN,
	UP_DOWN,
	TWINS_DOWN,
	TWINS_UP
}ROCK_TYPE;

class BackGroundLayer : public Layer{

public:
	
	CREATE_FUNC(BackGroundLayer);

	virtual bool init() override;

	virtual void update(float time) override;

	CC_SYNTHESIZE(GAME_STATE, curState, CurState);
	
private:

	Size  visibleSize;

	Point originPoint;

	StarLayer*  StarLayer;

	std::string rockNameUp;
	
	std::string rockNameDown;

	//back ground
	void  addBackGround();
	
	//stars
	void  addStarLayer();

	//land
	void  addLand();

	int   getRandomLandType();

	CC_SYNTHESIZE(LAND_TYPE, curLandType, CurLandType);

	Vector<Sprite*> landVector;

	//rocks
	Vector<Node*>   rockVector;

	void  setRockNameAfterLandAdded();

	int   getRandomRockType();

	Node* createRockByType(ROCK_TYPE);

	Node* rockSingleDown();

	Node* rockSingleUp();

	Node* rockUpandDown();

	Node* rockTwinsUp();

	Node* rockTwinsDown();

	void  initRockPhysics(Node*, bool);

	void  addRocks(float);
	
	//controll
	void  addElementsByState();

	void  runByState(GAME_STATE);

	void  readyGame();

	void  startGame();

	void  overGame();

	void  rockScrolling();

	void  landScrolling();

	//point check
	void  getPoint();

	bool  isGetPoint(Node*);

	//deconstructor
	~BackGroundLayer();

};


#endif
