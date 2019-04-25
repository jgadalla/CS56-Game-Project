#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

class LTexture
{
  public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//Deallocates texture
	void free();

	//Renders texture at given point
	//void render(int x, int y, SDL_Renderer* renderer);
    void render(int x, int y, SDL_Rect* clip , double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();


    SDL_Rect* getTexRect(int x, int y);

  private:
	//The actual hardware texture
	SDL_Texture *mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};