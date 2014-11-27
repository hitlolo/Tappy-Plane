#include "StarLayer.h"


bool StarLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	
	return true;


}

StarLayer::StarLayer()
{
	curMap = nullptr;

	originPoint = Director::getInstance()->getVisibleOrigin();

	visibleSize = Director::getInstance()->getVisibleSize();

	int map[20] = {
					-1,-1,-1,-1,-1,-1,-1,-1,0,1,
					 2,3,4,5,6,7,8,9,10,11
				  };
	for (int i = 0; i < 20; i++)
	{
		this->mapLevelVector.push_back(map[i]);
	}
	mapIndex = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct  timeval  psv;
	gettimeofday(&psv, NULL);    // 获取本地时间
	//根据时间产生随机种子	
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;	
	srand(tsrans);
#endif


#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	//struct tm *tm;
	time_t timep;
	//time(&timep);
	//tm = localtime(&timep);
	srand((unsigned int)time(&timep));
#endif

	random_shuffle(mapLevelVector.begin(), mapLevelVector.end());

	
}

StarLayer::~StarLayer()
{
	mapVector.clear();
	mapLevelVector.clear();
}

void StarLayer::addMapLayer(float time)
{
	
	int type = mapLevelVector.at(mapIndex++);
	if (mapIndex == mapLevelVector.size())
	{
		random_shuffle(mapLevelVector.begin(), mapLevelVector.end());
		mapIndex = 0;
	}
	createMapByType(type);
}


void StarLayer::getObjectsAndSet(TMXTiledMap* map)
{
	auto stars = map->getObjectGroup("stars");
	
	ValueVector objectsVector = stars->getObjects();

	for (auto starObject : objectsVector)
	{
		StarSprite* star = nullptr;
		auto starDef = starObject.asValueMap();
		float positionX = starDef["x"].asInt();
		float positionY = starDef["y"].asInt();
		if (starDef["rotation"].asInt())
		{
			float rotation = starDef["rotation"].asInt();
			star = this->createStarAndSet(positionX, positionY, rotation);
		}
		else
		{
			star = this->createStarAndSet(positionX, positionY);
		}
		if (!(star == nullptr))
		{
			map->addChild(star);
		
		}

	}
}

StarSprite* StarLayer::createStarAndSet(float x, float y, float rotation)
{
	auto star = StarSprite::create();
	star->setPosition(x, y);
	star->setRotation(rotation);
	return star;
}

void StarLayer::createMapByType(int type)
{
	if (type == -1)
	{
		return;
	}
	else
	{
		std::string map_name = String::createWithFormat("map%d.tmx", type)->getCString();
		auto curMap = TMXTiledMap::create(map_name);

		getObjectsAndSet(curMap);
		curMap->setPosition(originPoint.x + visibleSize.width, 0);
		this->addChild(curMap);
		this->mapVector.pushBack(curMap);
		
	}
	
}


void StarLayer::startGame()
{
	this->schedule(CC_SCHEDULE_SELECTOR(StarLayer::addMapLayer), 10.0f);
	this->scheduleUpdate();
}

void StarLayer::overGame()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(StarLayer::addMapLayer));
	this->unscheduleUpdate();
}

void StarLayer::update(float time)
{
	if (mapVector.empty())
	{
		return;
	}
		
	else
	{
		Vector<TMXTiledMap*> mapEraser;
		Vector<Node*> starEraser;
		auto curMap = mapVector.front();
		auto starsVector = curMap->getChildren();
		for (auto star : starsVector)
		{
			star->setPositionX(star->getPositionX() - 1.0f);
			if (star->getPositionX() < -(visibleSize.width+50))
			{
				//starEraser.pushBack(star);
				star->removeFromParentAndCleanup(true);
			}
		}
		if (starsVector.empty())
		{
			mapEraser.pushBack(curMap);
		}
		/*float position_x = curMap->getPositionX();
		curMap->setPositionX(position_x - 1.0f);
		if (position_x < -((curMap->getMapSize().width * curMap->getTileSize().width)))
		{
			mapEraser.pushBack(curMap);
			
		}*/

		for (auto map: mapEraser)
		{
			mapVector.eraseObject(map);
			this->removeChild(curMap);
		}
	}

}