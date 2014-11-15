

#include "LogoScene.h"


Scene* LogoScene::createScene(){
	
	auto scene = Scene::create();

	auto layer = LogoScene::create();

	scene->addChild(layer);

	return scene;


}

bool LogoScene::init(){

	if (!Layer::init()){
		return false;
	}

	loadRes();
	return true;
}

void  LogoScene::loadRes(){

	//Sprite* Sprite::create(const std::string& filename)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin     = Director::getInstance()->getVisibleOrigin();

	std::string name = JsonReader::getInstance()->getPathFromJson("logo");



	auto logo = Sprite::create(name);
	logo->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(logo);

	//auto laa = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 24);

	//								// position the label on the center of the screen
	//laa->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5));

	//								// add the label as a child to this layer
	//this->addChild(laa);
}


