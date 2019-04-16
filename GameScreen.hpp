#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Screen.hpp"

class GameScreen : public Screen
{
public:
	GameScreen(Renderer* gRenderer);
private:

};