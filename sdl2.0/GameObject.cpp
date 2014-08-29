#include <SDL_image.h>
#include "GameObject.h"
#include "Manager.h"
#include <fstream>
#include <iostream>

GameObject::GameObject(void)
{
	pos.x = pos.y = pos.w = pos.h = 0;
	img = NULL;
	clip.x = clip.y = 0;
	clip.w = clip.h = 24;
	frame = 0;
	state = "";
	//num_frames = 6;

	active = true;
}


GameObject::~GameObject(void)
{
}

//void GameObject::Init(std::string imgfile, SDL_Rect* dest)
void GameObject::Init(string txtfile, SDL_Rect* dest)
{
	std::ifstream in;
	in.open(txtfile);
	if ( in.fail() )
		exit(808);


	string dummy, imgfile, anime_name;
	SDL_Rect offset;
	int numframes;

	if ( in.peek() == '#')
	{
		getline(in, dummy);
	}
	in >> imgfile;

	while ( !in.eof() )
	{
		in >> anime_name 
		   >> offset.x >> offset.y >> offset.w >> offset.h
		   >> numframes;

		if (in.fail())
			continue;

		pos.w = clip.w = offset.w;
		pos.h = clip.h = offset.h;
		
		anime[anime_name].offset    = offset;
		anime[anime_name].numframes = numframes;
	}

	//surf = IMG_Load( imgfile.c_str() );
	img = Manager::LoadTexture( imgfile, &pos );
	if ( dest != NULL )
		pos = *dest;

	pos.w = clip.w;
	pos.h = clip.h;

	prev = SDL_GetTicks();
	timer = 0;
}

//true if eats up a key, false otherwise
bool GameObject::Update()
{
	Uint32 now = SDL_GetTicks();
	Uint32 dt = now - prev;
	prev = now;

	if (!active)
		return false;

	clip = anime[state].offset;
	clip.x += clip.w * frame;
	timer += dt;

	if ( timer > 1000/FPS ) // 66ms ~ 1/15 sec
	{
		frame++;
		frame %= anime[state].numframes;
		timer = 0;
	}

	//std::cout << state << " " << frame << std::endl;

	//Manager::RenderTexture( img, NULL, &pos );
	
	return false;
}

void GameObject::Render()
{
	if (active)
		Manager::RenderTexture( img, &clip, &pos );
}

void GameObject::Move(int direction)
{

}
