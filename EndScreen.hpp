#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Screen.hpp"

class EndScreen : public Screen{
public:
	EndScreen(Renderer* gRenderer);
private:

};