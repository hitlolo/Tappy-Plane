#include "RandomCacher.h"

RandomCacher* RandomCacher::_randomCacher = nullptr;

RandomCacher* RandomCacher::getInstance()
{
	if (!_randomCacher)
	{
		_randomCacher = new RandomCacher();
		return _randomCacher;
	}
	else
		return _randomCacher;

}

RandomCacher::RandomCacher()
{
	mt = new mt19937(randomDevice());
}

RandomCacher::~RandomCacher()
{
	CC_SAFE_DELETE(mt);
	CC_SAFE_DELETE(_randomCacher);
}

int RandomCacher::getRandomByRange(int from, int to)
{
	//std::default_random_engine random_e;
	uniform_int_distribution<int> dist(from, to);
	return dist(*mt);
}

float RandomCacher::getRandomByRange(float from, float to)
{
	//std::default_random_engine random_e;
	uniform_real_distribution<float> dist(from, to);
	return dist(*mt);
}
