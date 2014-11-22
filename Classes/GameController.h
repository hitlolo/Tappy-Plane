#ifndef __TP_CONTROLLER_H__
#define __TP_CONTROLLER_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Data.h"

USING_NS_CC;

class GameController{

public:

	static GameController* getInstance();
	
	void goState(GAME_STATE);

	

private:

	~GameController();

	static GameController* _controller;

	CC_SYNTHESIZE(GAME_STATE, curState, CurState);

	CC_SYNTHESIZE(Scene*, curScene, CurScene);

	void nextScene(Scene*);

};








#endif