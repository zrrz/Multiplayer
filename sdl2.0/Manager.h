#include <SDL.h>
#include <SDL_ttf.h>
#include "helper.h"
//#include <string>
#include "GameObject.h"
#include "Network.h"

#pragma once

namespace MANAGERERROR
{
	enum { SDL_INITFAIL=-10, IMG_INITFAIL, TTF_INITFAIL, WINDOW_INITFAIL };
}


class Manager
{
public:
	Manager(void);
	~Manager(void);

	int Init();

	bool LoadLevel(std::string levelfile);
	void UnloadLevel();

	bool Update();
	void Close();

	static SDL_Texture* LoadTexture(std::string filename, SDL_Rect* offset=NULL);
	static void			RenderTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* offset);
	
	static SDL_Window*		window;
	static SDL_Renderer*	renderer;

private:
	bool KeyUpdate();
	bool KeyDown(SDL_Keycode key);
	bool KeyUp(SDL_Keycode key);

	int		 keys;
	Vector2 mouse_pos;
	
	std::string nextlevel;
	//GameObject* objs[100];
	list<GameObject*>	objs;

	SDL_Texture* background;

	Network network;
	
};