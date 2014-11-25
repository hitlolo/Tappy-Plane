#include "CoinLayer.h"


bool CoinLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	addMapLayer();
	return true;


}

CoinLayer::CoinLayer()
{
	
	int map[10] = {0,0,0,0,0,0,1,2,3,4};
	for (int i = 0; i < 10; i++)
		this->mapIndex.push_back(map[i]);

}

CoinLayer::~CoinLayer()
{
	mapVector.clear();
	mapIndex.clear();
}

void CoinLayer::addMapLayer()
{
	random_shuffle(mapIndex.begin(),mapIndex.end());
	int index = RandomCacher::getInstance()->getRandomByRange(0, 4);
	int type = mapIndex.at(index);
	createMapByType(type);
}


void CoinLayer::getObjectsAndSet(TMXTiledMap* map)
{
	auto stars = map->getObjectGroup("stars");
	
	ValueVector objectsVector = stars->getObjects();

	for (auto starObject : objectsVector)
	{
		Sprite* star = nullptr;
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
			this->setStarPhysics(star);
			map->addChild(star);
			starVector.pushBack(star);
		}

	}
}

Sprite* CoinLayer::createStarAndSet(float x, float y, float rotation)
{
	std::string file_name = JsonReader::getInstance()->getPathFromJson("star_gold");
	auto star = Sprite::createWithSpriteFrameName(file_name);
	star->setPosition(x, y);
	star->setRotation(rotation);
	

	return star;
}

void CoinLayer::setStarPhysics(Sprite* coin)
{

	PhysicsBody *body = PhysicsBody::create();
	ShapeCacher::getInstance()->addShapesWithFile("starShape.plist", body);
	body->setCategoryBitmask(COLLIDER_TYPE_COIN);
	body->setCollisionBitmask(COLLIDER_TYPE_PLANE);
	body->setContactTestBitmask(COLLIDER_TYPE_PLANE);

	body->setDynamic(false);
	body->setLinearDamping(1.0f);
	body->setGravityEnable(false);
	coin->setPhysicsBody(body);
}

void CoinLayer::setObjectsAction()
{

}

void CoinLayer::createMapByType(int type)
{
	std::string map_name = String::createWithFormat("map%d.tmx",type)->getCString();
	TMXTiledMap* map     = TMXTiledMap::create(map_name);

	getObjectsAndSet(map);

	this->addChild(map);
}


