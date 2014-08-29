#include "Enemy.h"


Enemy::Enemy(void) : GameObject()
{
	state = "idle";
	velocity = Vector2(1,0);
	direction = KEYS::RIGHT;
}


Enemy::~Enemy(void)
{
}


bool Enemy::Update()
{
	GameObject::Update();
	return true;
}

void Enemy::Move(int action)
{
	if (direction == KEYS::UP)
	{
		pos.y -= velocity.y;
		if (pos.y <= 0)
			direction = KEYS::DOWN;
	}
	if (direction == KEYS::DOWN)
	{
		pos.y += velocity.y;
		if (pos.y + pos.h > SCREEN_HEIGHT)
			direction = KEYS::DOWN;
	}
	if (direction == KEYS::LEFT)
		pos.x -= velocity.x;
	if (direction == KEYS::RIGHT)
		pos.x += velocity.x;

}