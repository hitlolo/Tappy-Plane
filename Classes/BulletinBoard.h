
#ifndef __TP_BOARD_LAYER_H__
#define __TP_BOARD_LAYER_H__


#include "cocos2d.h"
#include "JsonReader.h"
#include "BulletinDelegate.h"
#include "SimpleAudioEngine.h"
#include "GameController.h"
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ� 
#include "cocostudio/CocoStudio.h"//��CocosStudio.h ͷ�ļ����Ѿ�������Studio����Ҫ�ĸ���ͷ�ļ�(��CocosGUI)�������ʹ��Studio����Ҫ�������Ϳ���


USING_NS_CC;

class BulletinBoard :public Layer, public BulletinDelegate{

public:
	~BulletinBoard();

	CREATE_FUNC(BulletinBoard);

	virtual bool init() override;

	virtual void showBulletin(GAME_STATE);

	virtual void updateStarAcount() override;
	
	virtual void updateScore() override;

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

	Label*  scoreLabel;

	Sprite* starSprite;

	Label*  starLabel;

	Node*   starNode;

	ui::Text* scoreNumLabel;
//
	ui::Text* starNumLabel;

	CC_SYNTHESIZE(int, curStar, CurStar);

	CC_SYNTHESIZE(int, curScore, CurScore);
	//over
	virtual void showStateOver() override;

	//callbacks
	void startGame(Ref* sender);

	void showCreditsView(Ref* sender);

	void addScoreAnimation(float);

	void addStarAnimation(float);

};








#endif
