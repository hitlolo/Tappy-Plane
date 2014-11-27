
#ifndef __TP_COIN_LAYER_H__
#define __TP_COIN_LAYER_H__


#include "cocos2d.h"
#include "ShapeCacher.h"
#include "RandomCacher.h"
#include "Data.h"
#include "JsonReader.h"
#include "StarSprite.h"
USING_NS_CC;

class StarLayer:public Layer
{

public:

	CREATE_FUNC(StarLayer);

	virtual bool init() override;

	virtual void update(float) override;

	void startGame();

	void overGame();

	StarLayer();

private:
	Point originPoint;

	Size  visibleSize;
	
	void addMapLayer(float);

	void getObjectsAndSet(TMXTiledMap* map);

	StarSprite* createStarAndSet(float, float, float= 0.0f);

	void createMapByType(int);

	std::vector<int>  mapLevelVector;

	int mapIndex;

	TMXTiledMap* curMap;

	Vector<TMXTiledMap*> mapVector;
	
	~StarLayer();
};



#endif
