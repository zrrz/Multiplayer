#include "GameObject.h"

#pragma once
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();

	virtual bool Update();

	virtual void Move(int action);
protected:
	int direction;
};

