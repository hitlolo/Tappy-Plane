
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
#if 1
		CCLOG("show bulletin bug!");
#endif
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

	Animate*        blink_ = Animate::create(tapAnimation);
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
	auto starNode = Node::create(); 
	this->starSprite->setAnchorPoint(Point(0, 1));
	this->starLabel->setAnchorPoint(Point(0, 0.5));
	starNode->setAnchorPoint(Point(0, 1));
	starLabel->setPosition(starSprite->getContentSize().width + 10, -starSprite->getContentSize().height/2 );

	starNode->addChild(starSprite);
	starNode->addChild(starLabel);
	starNode->setPosition(10,originPoint.y + visibleSize.height - 10);
	this->addChild(starNode);

}

void  BulletinBoard::updateStarAcount(int star)
{

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


}



void  BulletinBoard::startGame(Ref* sender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop1.ogg");
	GameController::getInstance()->goState(GAME_STATE::READY);;
	
#if 0
	CCLOG("START GAME!");
#endif
}

void  BulletinBoard::showCreditsView(Ref* sender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop1.ogg");
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