#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif


class Unit
{
public:
	Unit(Texture* texture, SDL_Rect* hitbox);
	void getSpeed();
	virtual draw() = 0;
	void getTexture();
	void getRect();
private:
	Texture* texture_;
	SDL_Rect* hitbox_;
	int speed;

};