#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Unit.hpp"

class PowerUp : public Unit
{
public:
	StartScreen(Renderer* gRenderer);
private:

};