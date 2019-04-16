#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Car.hpp"

class Sedan : public Car
{
public:
	Sedan(Texture* texture, SDL_Rect* hitbox, sound s);
private:

};