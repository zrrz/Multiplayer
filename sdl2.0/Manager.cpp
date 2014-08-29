#include "Manager.h"
#include "Enemy.h"
#include "Player.h"
#include <SDL_image.h>
#include <stdio.h>
#include <fstream>

SDL_Window* 	Manager::window = NULL;
SDL_Renderer*	Manager::renderer = NULL;

Manager::Manager(void)
{
	window   = NULL;
	renderer = NULL;

	background = NULL;
	keys = 0;
}


Manager::~Manager(void)
{

}

int Manager::Init()
{
	//start sdl
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		return MANAGERERROR::SDL_INITFAIL;

	//start img
	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ( IMG_Init( flags ) != flags )
		return MANAGERERROR::IMG_INITFAIL;

	//start ttf
	if ( TTF_Init() == -1)
		return MANAGERERROR::TTF_INITFAIL;

	window = SDL_CreateWindow("Coding 2",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if ( !window )
		return MANAGERERROR::WINDOW_INITFAIL;

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	LoadLevel("level1.txt");

	network.Init();

	return 0;
}

bool Manager::LoadLevel(std::string levelfile)
{
	std::ifstream in;
	in.open(levelfile);

	if (in.fail())
		exit(99999);

	std::string type, file, name;
	int x,y;

	while ( !in.eof() )
	{
		in >> type;
		if (in.fail())
			continue;

		if (type == "bg")
		{
			in >> file;
			background = LoadTexture(file);
			//objs.insert("bg", new GameObject);
			//objs["bg"]->Init(file);
		}
		else if (type == "Player")
		{
			in >> name >> file >> x >> y;
			objs.insert( name, new Player );
			objs[name]->Init( file );
			objs[name]->pos.x = x;
			objs[name]->pos.y = y;
		}
		else if (type == "Enemy")
		{
			in >> name >> file >> x >> y;
			objs.insert( name, new Enemy );
			objs[name]->Init( file );
			objs[name]->pos.x = x;
			objs[name]->pos.y = y;
		}
		else if (type == "Nextlevel")
		{
			in >> nextlevel;
		}
	}

	in.close();
}



bool Manager::Update()
{
	if ( !KeyUpdate() )
		return false;

	SDL_RenderClear( renderer );
	SDL_RenderCopy( renderer, background, NULL, NULL);

	//if (keys)
	for (int i=0; i<objs.size(); i++)
	{
		objs[i]->Move(keys);
		objs[i]->Update();
		objs[i]->Render();
	}

	SDL_RenderPresent( renderer );
	return true;
}

void Manager::Close()
{
	if ( renderer != NULL )
	{
		SDL_DestroyRenderer( renderer );
		renderer = NULL;
	}
	SDL_DestroyWindow( window );

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Manager::LoadTexture(std::string filename, SDL_Rect* offset)
//SDL_Texture* Manager::LoadTexture(char filename[], SDL_Rect* offset)
{
	if ( renderer == NULL )
		exit( 403 );

	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

	surface = IMG_Load( filename.c_str() );
	//surface = IMG_Load( filename );
	if ( surface == NULL )
		exit( 404 );
	
	if ( offset != NULL )
	{
		offset->w = surface->w;
		offset->h = surface->h;
	}
	
	texture = SDL_CreateTextureFromSurface( renderer, surface );

	SDL_FreeSurface( surface );
	return texture;
}

void Manager::RenderTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* offset)
{
	SDL_RenderCopy( renderer, texture, clip, offset );
}


bool Manager::KeyUpdate()
{
	int x,y;
	SDL_GetMouseState(&x, &y);
	mouse_pos.x = x;
	mouse_pos.y = y;

	SDL_Event e;
	while ( SDL_PollEvent( &e ) )
	{
		switch( e.type )
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			if ( !KeyDown( e.key.keysym.sym ) )
				return false;
			break;

		case SDL_KEYUP:
			if ( !KeyUp( e.key.keysym.sym ) )
				return false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if ( e.button.button == SDL_BUTTON_LEFT )
				keys |= KEYS::MOUSE0;
			if ( e.button.button == SDL_BUTTON_RIGHT )
				keys |= KEYS::MOUSE1;
			break;

		case SDL_MOUSEBUTTONUP:
			if ( e.button.button == SDL_BUTTON_LEFT )
				keys &= (~KEYS::MOUSE0);
			if ( e.button.button == SDL_BUTTON_RIGHT )
				keys &= (~KEYS::MOUSE1);
			break;
		}
	}
	return true;
}

bool Manager::KeyDown(SDL_Keycode key)
{
	switch( key )
	{
	case SDLK_ESCAPE:
		return false;
		break;

	case SDLK_UP:
	case 'w':
		keys |= KEYS::UP;
		break;
	
	case SDLK_DOWN:
	case 's':
		keys |= KEYS::DOWN;
		break;

	case SDLK_LEFT:
	case 'a':
		keys |= KEYS::LEFT;
		break;

	case SDLK_RIGHT:
	case 'd':
		keys |= KEYS::RIGHT;
		break;

	case SDLK_SPACE:
		keys |= KEYS::SPACE;
		break;
	}

	return true;
}

bool Manager::KeyUp(SDL_Keycode key)
{
	switch( key )
	{
	case SDLK_ESCAPE:
		return false;
		break;

	case SDLK_UP:
	case 'w':
		keys &= ~KEYS::UP;
		break;
	
	case SDLK_DOWN:
	case 's':
		keys &= ~KEYS::DOWN;
		break;

	case SDLK_LEFT:
	case 'a':
		keys &= ~KEYS::LEFT;
		break;

	case SDLK_RIGHT:
	case 'd':
		keys &= ~KEYS::RIGHT;
		break;

	case SDLK_SPACE:
		keys &= ~KEYS::SPACE;
		break;

	}

	return true;
}