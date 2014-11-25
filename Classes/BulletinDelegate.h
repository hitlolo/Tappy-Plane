#pragma once

#include "Data.h"

class BulletinDelegate{

public:
	
	virtual void showBulletin(GAME_STATE) = 0;

	virtual void updateStarAcount(int) = 0;

	virtual void updateScore() = 0;

protected:

	virtual void showStateMenu() = 0;

	virtual void showStateReady() = 0;

	virtual void showStateGaming() = 0;

	virtual void showStateOver() = 0;

};