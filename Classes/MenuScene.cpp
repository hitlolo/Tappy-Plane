
#include "MenuScene.h"

Scene* MenuScene::createScene()
{

	auto scene = Scene::create();
	auto menu = MenuScene::create();
	scene->addChild(menu);
	return scene;
}

bool MenuScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	addGameLayers();
	return true;

}


void MenuScene::addGameLayers()
{
	auto backLayer = BackGroundLayer::create();
	this->addChild(backLayer);

	auto stratoLayer = Stratosphere::create();
	this->addChild(stratoLayer);
	stratoLayer->runByState(GAME_STATE::MENU);

	auto bulletinLayer = BulletinBoard::create();
	this->addChild(bulletinLayer);
	bulletinLayer->showBulletin(GAME_STATE::MENU);
}