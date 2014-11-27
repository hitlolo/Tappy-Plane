#ifndef _TP_RANDOM_CACHE_
#define _TP_RANDOM_CACHE_

#include "cocos2d.h"
using namespace std;


class RandomCacher{

private:
	static RandomCacher* _randomCacher;

	random_device randomDevice;

	mt19937*      mt;

	~RandomCacher();

public:

	RandomCacher();

	static RandomCacher* getInstance();
	
	int     getRandomByRange(int, int);

	float   getRandomByRange(float, float);

};

#endif