#include "Player.h"


Player::Player(void) : GameObject()
{
	state = "idle_d";
	orientation = 'd';

}


Player::~Player(void)
{
}

bool Player::Update()
{
	return GameObject::Update();
} 


void Player::Move(int action)
{
	Vector2 dir(0,0);
	state = "idle_";

	if (action & KEYS::UP)
	{
		orientation = 'u';
		state = "walk_";
		dir.y -= 1;
	}
	if (action & KEYS::DOWN)
	{
		orientation = 'd';
		state = "walk_";
		dir.y += 1;
	}
	if (action & KEYS::LEFT)
	{
		orientation = 'l';
		state = "walk_";
		dir.x -= 1;
	}
	if (action & KEYS::RIGHT)
	{
		orientation = 'r';
		state = "walk_";
		dir.x += 1;
	}
	if (action & KEYS::SPACE)
	{
		state = "chop_";
	}

	state += orientation;

	if (state != prev_state)
	{
		prev_state = state;
		frame = 0;
	}

	pos.x += dir.x;
	pos.y += dir.y;


}