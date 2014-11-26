#include "GameController.h"


GameController* GameController::_controller = nullptr;

GameController::~GameController()
{
	CC_SAFE_DELETE(_controller);
}


GameController* GameController::getInstance()
{
	if (_controller == nullptr)
	{
		_controller = new GameController();
		if (!_controller)
		{
			CC_SAFE_DELETE(_controller);
			CCLOG("_controller  INIT FAIL£¡");
		}
		return _controller;
	}
	else
		return _controller;

}

void GameController::goState(GAME_STATE state)
{
	Scene* scene;
	this->setCurState(state);
	switch (state)
	{
	case GAME_STATE::LOGO:
		break;
	case GAME_STATE::MENU:
		
		scene = MenuScene::createScene();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("MonkeyIslandBand.mp3", true);
		break;
	case GAME_STATE::READY:
		this->playSceneSwitchEffect();
		scene = GameScene::createScene();
		break;
	case GAME_STATE::GAMING:
		{
			scene = this->getCurScene();
			if (scene)
			{
				auto game_layer = dynamic_cast<GameScene*>(scene->getChildByName("game"));
				game_layer->runByState(GAMING);
				return;
			}
		}		
		break;
	case GAME_STATE::OVER:
		{
			scene = this->getCurScene();
			if (scene)
			{
				auto game_layer = dynamic_cast<GameScene*>(scene->getChildByName("game"));
				game_layer->runByState(OVER);
				return;
			}
		}
		break;
	
	}
	this->setCurScene(scene);
	this->nextScene(scene);
}


void GameController::getPoint()
{
	auto scene = this->getCurScene();
	if (scene)
	{
		auto game_layer = dynamic_cast<GameScene*>(scene->getChildByName("game"));
		game_layer->updateScore();
		return;
	}
}

void GameController::nextScene(Scene* scene)
{
	TransitionScene *transition = TransitionFade::create(0.3f, scene);
	// run
	Director::getInstance()->replaceScene(transition);
}


void GameController::playSceneSwitchEffect()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
}