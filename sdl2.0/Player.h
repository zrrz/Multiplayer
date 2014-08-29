#include "GameObject.h"
#include <string>

#pragma once

class Player : public GameObject
{
public:
	Player(void);
	~Player(void);

	virtual bool Update();
	virtual void Move(int direction);

protected:
	string prev_state;
	string orientation;

};

