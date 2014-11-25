#ifndef __TP_PLANE_SPRITE_H__
#define __TP_PLANE_SPRITE_H__

#include "cocos2d.h"
#include "ActionEllipse.h"
#include "ActionRotation.h"
#include "JsonReader.h"
#include "Data.h"
#include "ShapeCacher.h"
#include "RandomCacher.h"

USING_NS_CC;




class PlaneSprite :public Sprite{

public:

	CREATE_FUNC(PlaneSprite);

	virtual bool init() override;

	virtual void update(float time) override;

	CC_SYNTHESIZE(PLANE_STATE, curState, CurState);

	void runByState(PLANE_STATE);

	void flyUp();
private:

	Point originPoint;

	Size  visibleSize;

	Action* actionIdle;

	Action* actionEllipse;

	Action* actionSwing;

	PLANE_COLOR getRandomColor();

	Action* initEllipseAction();

	Action* initSwingAction();

	Action* initIdleActionByColor(PLANE_COLOR color);

	void createPlane();

	void initPhysicsAttributes();

	void initActions();

	void idle();
	
	void ready();

	void gaming();

	void crash();





};












#endif