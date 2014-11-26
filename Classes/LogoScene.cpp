

#include "LogoScene.h"


Scene* LogoScene::createScene()
{
	
	auto scene = Scene::create();

	auto layer = LogoScene::create();

	scene->addChild(layer);

	return scene;


}

bool LogoScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	addLogo();

	return true;
}

void LogoScene::addLogo()
{
	
	Size visibleSize      = Director::getInstance()->getVisibleSize();
	Point originPoint     = Director::getInstance()->getVisibleOrigin();

	auto logo = Sprite::create(JsonReader::getInstance()->getPathFromJson("logo"));
	logo->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	logo->setName("logo");
	logo->setOpacity(10);
	this->addChild(logo);
	logo->runAction(Sequence::create(FadeTo::create(2.0f, 255), CallFunc::create(CC_CALLBACK_0(LogoScene::loadRes,this)),nullptr));
}

void  LogoScene::loadRes()
{

	//Sprite* Sprite::create(const std::string& filename)
	//void TextureCache::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback)
	Director::getInstance()->getTextureCache()->addImageAsync("tappyplane.png", CC_CALLBACK_1(LogoScene::loadImageOver, this));

}


void LogoScene::loadImageOver(Texture2D* texture)
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tappyplane.plist", texture);

	this->loadMusic();

	this->startGame();
}

void LogoScene::loadMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("MonkeyIslandBand.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pop1.ogg");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("3_Coins.ogg");
}

void LogoScene::startGame()
{

	// CallFunc::create(std::bind(&BulletinBoard::fadeinPanel, this));
	CallFunc* nextScene = CallFunc::create(std::bind(&LogoScene::nextScene, this));
	this->getChildByName("logo")->runAction(Sequence::create(FadeOut::create(2.0f), nextScene, nullptr));
}


void LogoScene::nextScene()
{

	
	GameController::getInstance()->goState(GAME_STATE::MENU);

}

void LogoScene::onExit()
{

	Layer::onExit();
	this->stopAllActions();

}