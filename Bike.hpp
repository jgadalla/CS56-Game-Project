#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Unit.hpp"
class Bike : public Unit
{

public:
	Bike(Texture* texture, SDL_Rect* hitbox);
	
private:

};