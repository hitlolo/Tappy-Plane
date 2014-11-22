

#include "JsonReader.h"


JsonReader* JsonReader::jsonReader = nullptr;


JsonReader*  JsonReader::getInstance()
{


	if (jsonReader == nullptr)
	{

		jsonReader = new JsonReader();
		if (!jsonReader)
		{
			CC_SAFE_DELETE(jsonReader);
			CCLOG("JSON READER INIT FAIL£¡");  
		}
		return jsonReader;
	}
	else
		return jsonReader;
}

JsonReader::~JsonReader(){

	CC_SAFE_DELETE(jsonReader);

}


JsonReader::JsonReader()
{

	jsonStr =this->getJsonData();
	decoder.Parse<kParseDefaultFlags>(jsonStr.c_str());
}


std::string JsonReader::getJsonData()
{

	std::string filename = "image.json";
	std::string filepath = FileUtils::getInstance()->fullPathForFilename(filename);
	ssize_t  size;
	unsigned char *pData = NULL;
	pData = FileUtils::getInstance()->getFileData(filepath.c_str(), "r", &size);
	std::string str((const char*)pData, size);

	CC_SAFE_DELETE_ARRAY(pData);

	return str;

}


std::string JsonReader::getPathFromJson(const std::string key)
{

	if (!decoder.IsNull())  
	{
		if (decoder.HasParseError())
		{
			CCLOG("GetParseError %s\n", decoder.GetParseError());
		}
		
		if (decoder.IsObject())
		{
			//CCLOG("!decoder.IsObject().");
			const rapidjson::Value &value = decoder[key.c_str()];

			std::string str = value.GetString();
			return str;
		}
		else
			return "";		
	}
	else
		return "";

}
