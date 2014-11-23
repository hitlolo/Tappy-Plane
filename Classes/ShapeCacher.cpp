#include "ShapeCacher.h"

ShapeCacher* ShapeCacher::_ShapeCacher = nullptr;

ShapeCacher* ShapeCacher::getInstance(void)
{
	if (!_ShapeCacher)
	{
		_ShapeCacher = new ShapeCacher();

		return _ShapeCacher;
	}
	else
		return _ShapeCacher;

}

ShapeCacher::~ShapeCacher()
{
	CC_SAFE_DELETE(_ShapeCacher);
}

void ShapeCacher::addShapesWithFile(const std::string &plist, PhysicsBody *body)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

	addShapesWithDictionary(dict, body);

}



void ShapeCacher::addShapesWithDictionary(ValueMap &dictionary, PhysicsBody *body)
{
	int format = 0;

	// get the format
	if (dictionary.find("metadata") != dictionary.end())
	{
		ValueMap& metadataDict = dictionary["metadata"].asValueMap();
		format = metadataDict["format"].asInt();
	}

	// check the format
	CCASSERT(format == 1, "format is not supported for #addShapesWithDictionary#:");

	ValueMap& bodyDict = dictionary["bodies"].asValueMap();

	for (auto iter = bodyDict.begin(); iter != bodyDict.end(); ++iter)
	{
		ValueMap& dataDict = iter->second.asValueMap();

		//set anchorpoint
		Point anchorPoint = PointFromString(dataDict["anchorpoint"].asString());
	

		ValueVector& fixtureVector = dataDict["fixtures"].asValueVector();

		for (auto iter = fixtureVector.begin(); iter != fixtureVector.end(); ++iter)
		{
			ValueMap& fixtureDict =(ValueMap&)(*iter).asValueMap();

			//body->setCategoryBitmask(fixtureDict["filter_categoryBits"].asInt);
			//body->setCollisionBitmask(fixtureDict["filter_maskBits"].asInt);
			//body->setGroup(fixtureDict["filter_groupIndex"].asInt);

			//float friction    = fixtureDict["friction"].asFloat;
			//float density     = fixtureDict["density"].asFloat;
			//float restitution = fixtureDict["restitution"].asFloat;
			//int   isSensor    = fixtureDict["isSensor"].asInt;
			//std::string userdata = fixtureDict["userdataCbValue"].asString;

			//std::string fixtureType = fixtureDict["fixture_type"].asString();

			/*if (fixtureType == "POLYGON") 
			{*/

			ValueVector& polygonsVector = (fixtureDict["polygons"].asValueVector());

			for (auto iter = polygonsVector.begin(); iter != polygonsVector.end(); ++iter) 
			{
	
				int vertexNum = (*iter).asValueVector().size();;

				//Vector<std::string > polygonArray = *iter;
				ValueVector polygonArray = (*iter).asValueVector();

				Point *polyVertex = new Point[vertexNum];

				int i = 0;

				for (auto piter = polygonArray.begin(); piter != polygonArray.end(), i < vertexNum; ++piter ,i++)
				{
					Point vertex = PointFromString((*piter).asString());
					polyVertex[i] = vertex;
				}

				body->addShape(PhysicsShapePolygon::create(polyVertex, vertexNum));
			}

		}
		//	else if (fixtureType == "CIRCLE") 
		//	{

		//		continue;
		//		//ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");

		//		//b2CircleShape *circleShape = new b2CircleShape();

		//		//circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
		//		//CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
		//		//circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
		//		//fix->fixture.shape = circleShape;

		//		//// create a list
		//		//*nextFixtureDef = fix;
		//		//nextFixtureDef = &(fix->next);

		//	}
		//	else 
		//	{
		//		CCAssert(0, "Unknown fixtureType");
		//	}
		//}
	
	}
}