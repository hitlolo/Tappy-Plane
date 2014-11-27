#ifndef __TP_JSON_H__
#define __TP_JSON_H__


#include "cocos2d.h"
#include <string>   
#include "json/rapidjson.h"
#include "json/document.h"


USING_NS_CC;
using namespace rapidjson;

class JsonReader{


public:

	static JsonReader* getInstance();

	std::string getPathFromJson(const std::string key);


private:

	JsonReader();

	~JsonReader();
	
	static JsonReader* jsonReader;

	std::string jsonStr;

	rapidjson::Document decoder;

	std::string getJsonData();

};


#endif
