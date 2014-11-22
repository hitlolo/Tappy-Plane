
#include "GameScene.h"



Scene* GameScene::createScene()
{

	auto scene = Scene::create();
	auto game  = GameScene::create();
	scene->addChild(game,0,"game");
	return scene;
}

bool GameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	this->addGameLayers();
	this->runByState(GAME_STATE::READY);

	return true;


}


void GameScene::addGameLayers()
{

	Size visibleSize  = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();


	this->backLayer = BackGroundLayer::create();
	this->addChild(backLayer);
	
	this->stratoLayer = Stratosphere::create();
	this->addChild(stratoLayer); 
	

	auto bulletinLayer = BulletinBoard::create();
	bulletinDelegator = bulletinLayer;
	this->addChild(bulletinLayer);
	//
	
	auto touchLayer = TouchLayer::create();
	touchLayer->setDelegator(this);
	this->addChild(touchLayer);

}


void GameScene::runByState(GAME_STATE state)
{

	switch (state)
	{
	case GAME_STATE::MENU:

		break;
	case GAME_STATE::READY:
		this->stratoLayer->runByState(READY);
		this->bulletinDelegator->showBulletin(READY);
		break;
	case GAME_STATE::GAMING:
		this->bulletinDelegator->showBulletin(GAMING);
		break;
	case GAME_STATE::OVER:
		break;

	}

}


void GameScene::onTouch()
{

	GAME_STATE curState = GameController::getInstance()->getCurState();
	switch (curState)
	{
		case GAME_STATE::LOGO:
			return;
			break;
		case GAME_STATE::MENU:
			return;
			break;
		case GAME_STATE::READY:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop1.ogg");
			GameController::getInstance()->goState(GAMING);
			break;
		case GAME_STATE::GAMING:
			break;
		case GAME_STATE::OVER:
			break;

	}

}