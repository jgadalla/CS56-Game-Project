#include "LTexture.hpp"

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	angle = 0.0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture *newTexture = NULL;

	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

SDL_Rect* LTexture::getTexRect(int x, int y)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = mWidth;
	rect->h = mHeight;
	return rect;
}

void LTexture::render(int x, int y, SDL_Rect *clip, SDL_Point *center, SDL_RendererFlip flip, SDL_Renderer *gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::render(int x, int y, SDL_Renderer *gRenderer, int dir)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	switch(dir){
		case 0:
			SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, 180.0, NULL, SDL_FLIP_NONE);
			break;
		case 1:
			SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, -90.0, NULL, SDL_FLIP_NONE);
			break;
		case 2:
			SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, 90.0, NULL, SDL_FLIP_NONE);
			break;
		case 3:
			SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
			break;
	}
	
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

void LTexture::setAngle(int degrees){
	angle = degrees;
}
