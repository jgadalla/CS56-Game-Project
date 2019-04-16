#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

class Screen{

public:
	Screen(Renderer* gRenderer);
	Screen(Renderer* gRenderer, Screen* gScreen);
	void getScreen();
	void getRenderer();

private:
	Renderer* gRenderer_;
	Screen* gScreen_;


}