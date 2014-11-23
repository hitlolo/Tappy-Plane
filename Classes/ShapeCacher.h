
#ifndef _TP_SHAPE_CACHE_
#define _TP_SHAPE_CACHE_

#include "cocos2d.h"

USING_NS_CC;

class ShapeCacher {

public:
	// Static interface
	static ShapeCacher* getInstance(void);

public:

	void addShapesWithFile(const std::string &plist, PhysicsBody *body);

private:

	static ShapeCacher* _ShapeCacher;

	void addShapesWithDictionary(ValueMap&, PhysicsBody*);

	~ShapeCacher();

};


#endif