
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
	
	virtual bool init() override;

	CREATE_FUNC(BackGroundLayer);

	virtual void update(float time) override;

	CC_SYNTHESIZE(GAME_STATE, curState, CurState);
	
private:
	Size  visibleSize;

	Point originPoint;

	StarLayer*  StarLayer;

	std::string rockNameUp;
	
	std::string rockNameDown;

	void  addBackGround();

	void  addLand();

	int   getRandomLandType();

	CC_SYNTHESIZE(LAND_TYPE, curLandType, CurLandType);

	Vector<Sprite*> landVector;

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

	void  rockScrolling();

	void  landScrolling();
	
	void  addElementsByState();

	void  runByState(GAME_STATE);

	void  getPoint();

	bool  isGetPoint(Node*);

	void  addStarLayer();

	void  readyGame();

	void  startGame();

	void  overGame();

	~BackGroundLayer();

};


#endif
