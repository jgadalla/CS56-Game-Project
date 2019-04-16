#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Car.hpp"

class Semi : public Car
{
public:
	Semi(Texture* texture, SDL_Rect* hitbox, sound s);
private:

};