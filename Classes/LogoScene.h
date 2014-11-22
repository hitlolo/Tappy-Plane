#ifndef __TP_LOAD_H__
#define __TP_LOAD_H__

#include "cocos2d.h"
#include "JsonReader.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class LogoScene:public Layer{


public:

	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(LogoScene);

	

private:

	virtual void onExit() override;

	void addLogo();

	void loadRes();

	void loadImageOver(Texture2D* texture);

	void loadMusic();

	void startGame();

	void nextScene();
};











#endif
