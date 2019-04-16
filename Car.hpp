#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Unit.hpp"

class Car : public Unit
{
public:
	Car(Texture* texture, SDL_Rect* hitbox, sound s);
	virtual makeSound() = 0;
private:
	sound s_;

};