
#include "BulletinBoard.h"


bool BulletinBoard::init()
{

	if (!Layer::init())
	{
		return false; 
	}

	originPoint = Director::getInstance()->getVisibleOrigin();

	visibleSize = Director::getInstance()->getVisibleSize();

	creditView  = nullptr;
	
	curStar     = 0;

	curScore    = 0;

	return true;

}



void BulletinBoard::showBulletin(GAME_STATE state)
{

	switch (state)
	{
	case GAME_STATE::MENU:
			showStateMenu();
			break;
	case GAME_STATE::READY:
			showStateReady();
			break;
	case GAME_STATE::GAMING:
			readyToGame(CC_CALLBACK_0(BulletinBoard::showStateGaming,this));
			break;
	case GAME_STATE::OVER:
			showStateOver();
			break;
		default:
			break;

	}

}


void BulletinBoard::showStateMenu()
{
	
	std::string file_name;
	//add title and ease In
	file_name = JsonReader::getInstance()->getPathFromJson("font");
	auto titleLabel = Label::createWithBMFont(file_name, "TAPPY PLANE", TextHAlignment::CENTER);
	titleLabel->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height + titleLabel->getContentSize().height);
	this->addChild(titleLabel);
	MoveTo* move = MoveTo::create(0.8f, Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 10 * 8));
	Action* action = EaseExponentialOut::create(move);
	titleLabel->runAction(action);
	
	//add start button
	//button
	file_name = JsonReader::getInstance()->getPathFromJson("button_play");
	auto buttonStart_n = Sprite::createWithSpriteFrameName(file_name);
	auto buttonStart_p = Sprite::createWithSpriteFrameName(file_name);
	buttonStart_n->setPositionY(5);
	auto itemStart = MenuItemSprite::create(buttonStart_n, buttonStart_p, CC_CALLBACK_1(BulletinBoard::startGame, this));
	itemStart->setScale(0.8f);
	//add credits button
	file_name = JsonReader::getInstance()->getPathFromJson("button_credits");
	auto buttonCredits_n = Sprite::createWithSpriteFrameName(file_name);
	auto buttonCredits_p = Sprite::createWithSpriteFrameName(file_name);
	buttonCredits_n->setPositionY(5);
	auto itemCredits = MenuItemSprite::create(buttonCredits_n, buttonCredits_p, CC_CALLBACK_1(BulletinBoard::showCreditsView, this));
	itemCredits->setScale(0.8f);

	auto menu = Menu::create(itemStart, itemCredits, nullptr);
	menu->alignItemsVerticallyWithPadding(10.0f);
	menu->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y - menu->getContentSize().height));
	menu->setOpacity(180);
	this->addChild(menu);
	menu->runAction(EaseExponentialOut::create(MoveTo::create(0.6f, Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 10 * 3))));


}


void BulletinBoard::showStateReady()
{
	//do clean
	this->removeAllChildren();
	//do work
	std::string file_name;
	file_name = JsonReader::getInstance()->getPathFromJson("ready");
	this->readySprite = Sprite::createWithSpriteFrameName(file_name);
	readySprite->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height - readySprite->getContentSize().height);
	this->addChild(readySprite);

	file_name = JsonReader::getInstance()->getPathFromJson("tap_tag_right");
	auto tutorRight = Sprite::createWithSpriteFrameName(file_name);

	file_name = JsonReader::getInstance()->getPathFromJson("tap_tag_left");
	auto tutorLeft = Sprite::createWithSpriteFrameName(file_name);

	//88 is the width of the plane sprite	
	this->tutorSprite = Node::create();
	tutorSprite->setCascadeOpacityEnabled(true);
	tutorSprite->addChild(tutorLeft);
	tutorSprite->addChild(tutorRight);
	tutorRight->setPosition(-100, 0);
	tutorLeft->setPosition(100, 0);
	tutorSprite->setPosition(originPoint.x + visibleSize.width / 3, originPoint.y + visibleSize.height / 2);
	this->addChild(tutorSprite);
	
	//click hand
	file_name = JsonReader::getInstance()->getPathFromJson("tap");
	auto tapFrame_f = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name);
	file_name = JsonReader::getInstance()->getPathFromJson("tap_click");
	auto tapFrame_s = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name);
	Animation* tapAnimation = Animation::create();
	tapAnimation->addSpriteFrame(tapFrame_f);
	tapAnimation->addSpriteFrame(tapFrame_s);
	tapAnimation->setDelayPerUnit(0.4f);

	tapSprite = Sprite::create();
	// 73 is the height of the plane contenSize
	tapSprite->setPosition(originPoint.x + visibleSize.width / 3 + 30, originPoint.y + visibleSize.height / 2 - 73);

	Animate*  blink_ = Animate::create(tapAnimation);
	tapSprite->runAction(RepeatForever::create(blink_));

	this->addChild(tapSprite);

}

void BulletinBoard::readyToGame(const std::function<void(void)> &callback)
{
	tutorSprite->stopAllActions();
	tapSprite->stopAllActions();
	auto scale = ScaleBy::create(0.2f, 1.8f);
	auto fade  = FadeOut::create(0.3f);
	auto fadeout = Spawn::createWithTwoActions(scale, fade);
	this->readySprite->runAction(fadeout);
	this->tutorSprite->runAction(FadeOut::create(0.3f));
	this->tapSprite->runAction(FadeOut::create(0.3f));
	//go show Gaming state infomation
	callback();
}

void BulletinBoard::showStateGaming()
{
	std::string file_name = JsonReader::getInstance()->getPathFromJson("font"); 
	this->scoreLabel = Label::createWithBMFont(file_name,"0");
	scoreLabel->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 10 * 8);
	this->addChild(scoreLabel);


	file_name = JsonReader::getInstance()->getPathFromJson("star_gold");
	this->starSprite = Sprite::createWithSpriteFrameName(file_name);
	file_name = JsonReader::getInstance()->getPathFromJson("font_ttf");
	this->starLabel = Label::createWithTTF("0", file_name, 50, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	starLabel->enableOutline(Color4B(245, 178, 33, 155), 2);
	this->starNode = Node::create(); 
	this->starSprite->setAnchorPoint(Point(0, 1));
	this->starLabel->setAnchorPoint(Point(0, 0.5));
	starNode->setAnchorPoint(Point(0, 1));
	starLabel->setPosition(starSprite->getContentSize().width + 10, -starSprite->getContentSize().height/2 );

	starNode->addChild(starSprite);
	starNode->addChild(starLabel);
	starNode->setPosition(10,originPoint.y + visibleSize.height - 10);
	this->addChild(starNode);

}

void  BulletinBoard::updateStarAcount()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PickedCoinEcho.wav");
	this->setCurStar(this->getCurStar() + 1);
	auto str = String::createWithFormat("%d", getCurStar());
	starLabel->setString(str->getCString());
}

void BulletinBoard::updateScore()
{	

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
	this->setCurScore(this->getCurScore() + 1);
	auto str = String::createWithFormat("%d", getCurScore());
	scoreLabel->setString(str->getCString());

}

void BulletinBoard::showStateOver()
{
	this->removeChild(scoreLabel);
	this->removeChild(starNode);

	Node *rootNode = CSLoader::createNode("overMenu.csb");//传入Studio2.x的资源路径
	rootNode->setPosition(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2));
	rootNode->runAction(MoveTo::create(0.4f, Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2)));
	this->addChild(rootNode);
//
	std::string file_name = JsonReader::getInstance()->getPathFromJson("over");
	auto overSprite = Sprite::createWithSpriteFrameName(file_name);
	overSprite->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height + overSprite->getContentSize().height);
	overSprite->runAction(MoveTo::create(0.4f, Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 10 * 8)));
	this->addChild(overSprite);

	auto restartButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("restartButton"));
	if (restartButton)
	{
		restartButton->addClickEventListener(CC_CALLBACK_1(BulletinBoard::startGame,this));
	}

	//set font name again due to the cocos studio 2.0 bugs (Text load ttf error)
	file_name = JsonReader::getInstance()->getPathFromJson("font_ttf");
	this->starNumLabel = dynamic_cast<ui::Text*> (rootNode->getChildByName("starNumText"));
	starNumLabel->setFontName(file_name);
	auto scoreLabel = dynamic_cast<ui::Text*> (rootNode->getChildByName("scoreText"));
	scoreLabel->setFontName(file_name);
	this->scoreNumLabel = dynamic_cast<ui::Text*> (rootNode->getChildByName("scoreNumText"));
	scoreNumLabel->setFontName(file_name);
	auto bestLabel = dynamic_cast<ui::Text*> (rootNode->getChildByName("bestText"));
	bestLabel->setFontName(file_name);
	auto bestNumLabel = dynamic_cast<ui::Text*> (rootNode->getChildByName("bestNumText"));
	bestNumLabel->setFontName(file_name);

	//user data record
	int bestScore = 0;
	bestScore = UserDefault::getInstance()->getIntegerForKey("best_score");
	if (curScore > bestScore)
	{
		bestScore = curScore;
		UserDefault::getInstance()->setIntegerForKey("best_score", bestScore);

	}
	bestNumLabel->setText(String::createWithFormat("%d", bestScore)->getCString());

	if (curScore > 0)
	{
		this->schedule(CC_SCHEDULE_SELECTOR(BulletinBoard::addScoreAnimation), 0.2f);
	}
	if (curStar > 0)
	{
		this->schedule(CC_SCHEDULE_SELECTOR(BulletinBoard::addStarAnimation), 0.2f);
	}
	
}



void  BulletinBoard::startGame(Ref* sender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_click.ogg");
	GameController::getInstance()->goState(GAME_STATE::READY);;
	
#if 0
	CCLOG("START GAME!");
#endif
}

void  BulletinBoard::showCreditsView(Ref* sender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_click.ogg");
	if (!creditView)
	{
		this->addCreditSprite();
	}
	else 
	{
		creditView->setVisible(!creditView->isVisible());
	}
		
#if 0
	CCLOG("CREDITS VIEW!");
#endif

}

void BulletinBoard::addCreditSprite()
{
	std::string file = JsonReader::getInstance()->getPathFromJson("uibackground");
	creditView = Sprite::createWithSpriteFrameName(file);
	creditView->setPosition(originPoint.x + visibleSize.width - creditView->getContentSize().width / 2 - 30, originPoint.y + creditView->getContentSize().height / 2 + 20);
	creditView->setOpacity(195);
	this->addChild(creditView);

	//:createWithTTF(
	//const std::string& text, 
	//const std::string& fontFile, 
	//float fontSize, 
	//const Size& dimensions /* = Size::ZERO */,
	//TextHAlignment hAlignment /* = TextHAlignment::LEFT */, 
	//TextVAlignment vAlignment /* = TextVAlignment::TOP */)

	//label
	std::string thanks_str = "\nC R E D I T S\n\n---------\ncoding:\nhitlolo\n\nSpecial thanks:\nwww.kenney.nl\n---------";
	std::string font_name = JsonReader::getInstance()->getPathFromJson("font_ttf");
	Label* thanks = Label::createWithTTF(thanks_str, font_name, 18);
	thanks->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	thanks->setPosition(originPoint.x + creditView->getContentSize().width / 2, originPoint.y + creditView->getContentSize().height - 100);
	creditView->addChild(thanks);

}


void BulletinBoard::addScoreAnimation(float time)
{
	int i;
	sscanf(this->scoreNumLabel->getStringValue().c_str(), "%d", &i);
	if (i < this->getCurScore())
	{
		i++;
		scoreNumLabel->setText(String::createWithFormat("%d", i)->getCString());
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PickedCoinEcho.wav");
	}
	else if (i == this->getCurScore())
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(BulletinBoard::addScoreAnimation));
	}
}

void BulletinBoard::addStarAnimation(float time)
{
	int i;
	sscanf(this->starNumLabel->getStringValue().c_str(), "%d", &i);
	if (i < this->getCurStar())
	{
		i++;
		starNumLabel->setText(String::createWithFormat("%d", i)->getCString());
	}
	else if (i == this->getCurStar())
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(BulletinBoard::addStarAnimation));
	}
}


BulletinBoard::~BulletinBoard()
{
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}
