#include <SDL.h>
#include <string>
#include "helper.h"
#include "Animation.h"
#include "list.h"
#pragma once

using namespace std;

class Manager;

//GameObject class
class GameObject
{
	friend Manager;
public:
	GameObject(void);
	~GameObject(void);

	//void Init(std::string imgfile, SDL_Rect* dest=NULL);
	virtual void Init(std::string txtfile, SDL_Rect* dest=NULL);
	virtual bool Update();

	virtual void Render();
	virtual void Move(int action);

	//virtual bool Collide(GameObject* other);
	//virtual void HandleCollision(GameObject* other);

	bool active;

protected:
	SDL_Surface* surf;
	SDL_Texture* img;
	SDL_Rect	 pos;

	Vector2 position;
	Vector2 velocity;

	//animation stuff
	SDL_Rect	 clip;
	int			 frame;
	
	string state;
	list<Animation> anime;

	//timer
	Uint32		prev;
	Uint32		timer;

};

