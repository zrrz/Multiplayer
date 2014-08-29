#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



//keys
namespace KEYS
{
	enum { 
		MOUSE0=1<<1,	MOUSE1=1<<2,	UP=1<<3,	DOWN=1<<4, 
		LEFT=1<<5,		RIGHT=1<<6,		SPACE=1<<7
	};
	const int NUMKEYS = 7;
}

//pixel coordinates
struct Vector2
{
	Vector2() {}
	Vector2(float xx, float yy) : x(xx), y(yy){}
	float x;
	float y;
};

static Vector2 operator+(const Vector2 &a, const Vector2 &b)
{
	Vector2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

static Vector2 operator-(const Vector2 &a, const Vector2 &b)
{
	Vector2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

const int FPS = 15;
