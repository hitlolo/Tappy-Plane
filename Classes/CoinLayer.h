
#ifndef __TP_COIN_LAYER_H__
#define __TP_COIN_LAYER_H__


#include "cocos2d.h"
#include "ShapeCacher.h"
#include "RandomCacher.h"
#include "Data.h"
#include "JsonReader.h"

USING_NS_CC;

class CoinLayer:public Layer
{

public:

	CREATE_FUNC(CoinLayer);

	virtual bool init() override;

	CoinLayer();

private:
	void addMapLayer();

	void getObjectsAndSet(TMXTiledMap* map);

	Sprite* createStarAndSet(float, float, float= 0.0f);

	void setStarPhysics(Sprite* star);

	void setObjectsAction();

	void createMapByType(int);

	std::vector<int>  mapIndex;

	TMXTiledMap* curMap;

	Vector<TMXTiledMap*> mapVector;

	Vector<Sprite*>      starVector;
	
	~CoinLayer();
};



#endif
