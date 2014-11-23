
#ifndef __TP_BACK_LAYER_H__
#define __TP_BACK_LAYER_H__

#include "JsonReader.h"
#include "cocos2d.h"
#include "Data.h"
#include "GameController.h"
#include "ShapeCacher.h"

USING_NS_CC;

typedef enum class land_type{
	GRASS = 0,
	DIRT,
	SNOW,
	ICE,
	ROCK
}LAND_TYPE;

class BackGroundLayer : public Layer{

public:
	
	virtual bool init() override;

	CREATE_FUNC(BackGroundLayer);

	virtual void update(float time) override;

	CC_SYNTHESIZE(GAME_STATE, curState, CurState);
	
private:
	Size  visibleSize;

	Point originPoint;

	void  addBackGround();

	void  addRocks();

	void  addLand();

	void  rockScrolling();

	void  landScrolling();
	
	void  addElementsByState();

	int   getRandomLand();

	CC_SYNTHESIZE(LAND_TYPE, curLandType, CurLandType);

	Vector<Sprite*> landVector;

	void  runByState();

};


#endif
