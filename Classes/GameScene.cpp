
#include "GameScene.h"



Scene* GameScene::createScene()
{
	//init physics world
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(GRAVITY);
#if 0
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 1.0f);
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);

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
	case GAME_STATE::LOGO:

			break;
	case GAME_STATE::MENU:

		break;
	case GAME_STATE::READY:
		readyGame();
		break;
	case GAME_STATE::GAMING:
		startGame();
		break;
	case GAME_STATE::OVER:
		overGame();
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
			this->stratoLayer->getPlaneSprite()->flyUp();
			break;
		case GAME_STATE::OVER:
			return;
			break;

	}

}


void GameScene::updateScore()
{
	this->bulletinDelegator->updateScore(); 

}


void GameScene::addPhysicsContactListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContact, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool  GameScene::onContact(PhysicsContact& contact){

	if (GameController::getInstance()->getCurState() == GAME_STATE::GAMING)
	{
		if ((COLLIDER_TYPE)contact.getType() == (COLLIDER_TYPE_LAND | COLLIDER_TYPE_ROCK))
		{
			GameController::getInstance()->goState(GAME_STATE::OVER);

		}
	
	}
	
	return true;
}


void GameScene::readyGame()
{
	this->stratoLayer->runByState(READY);
	this->bulletinDelegator->showBulletin(READY);

}

void GameScene::startGame()
{

	this->stratoLayer->runByState(GAMING);
	this->backLayer->runByState(GAMING);
	this->bulletinDelegator->showBulletin(GAMING);
	this->addPhysicsContactListener();
}

void GameScene::overGame()
{
	
	this->stratoLayer->runByState(OVER);
	this->backLayer->runByState(OVER);
	this->bulletinDelegator->showBulletin(OVER);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
}
