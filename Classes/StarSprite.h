#ifndef __TP_STAR_SPRITE_H__
#define __TP_STAR_SPRITE_H__

#include "cocos2d.h"
#include "JsonReader.h"
#include "Data.h"
#include "ShapeCacher.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class StarSprite :public Sprite
{

public:
	CREATE_FUNC(StarSprite);

	virtual bool init() override;

	void runStarAction();
private:

	Point originPoint;

	Size  visibleSize;

	void initImage();

	void initPhysics();

	void dispearCallback();

};

#endif