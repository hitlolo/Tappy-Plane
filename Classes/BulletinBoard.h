
#ifndef __TP_BOARD_LAYER_H__
#define __TP_BOARD_LAYER_H__


#include "cocos2d.h"
#include "JsonReader.h"
#include "BulletinDelegate.h"
#include "SimpleAudioEngine.h"
#include "GameController.h"


USING_NS_CC;

class BulletinBoard :public Layer, public BulletinDelegate{

public:

	CREATE_FUNC(BulletinBoard);

	virtual bool init() override;

	virtual void showBulletin(GAME_STATE);

	virtual void updateStarAcount() override;

private:

	Point   originPoint;

	Size    visibleSize;

	//menu
	Sprite* creditView;

	void    addCreditSprite();

	virtual void showStateMenu() override;
	//ready
	Sprite* readySprite;

	Sprite* tapSprite;

	Node*   tutorSprite; 

	virtual void showStateReady() override;

	void readyToGame(const std::function<void(void)> &callback);

	//gaming
	virtual void showStateGaming() override;
	//over
	virtual void showStateOver() override;

	//callbacks
	void startGame(Ref* sender);
	
	void showCreditsView(Ref* sender);


};








#endif