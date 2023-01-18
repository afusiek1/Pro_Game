#include "Textures.h"

LTexture::LTexture() {

	//Initialize
	mTexture = NULL;
	tWidth = 0;
	tHeight = 0;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile(SDL_Renderer* rend, std::string path) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( rend, loadedSurface);
		if (newTexture == NULL)	{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			//Get image dimensions
			tWidth = loadedSurface->w;
			tHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free() {
	//Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}

void LTexture::render(SDL_Renderer* rend, Vec2D position) const {

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { position.x, position.y, tWidth, tHeight };
	SDL_RenderCopy(rend, mTexture, NULL, &renderQuad);
}

void LTexture::render(SDL_Renderer* rend, int x, int y) const {

	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, tWidth, tHeight };
	SDL_RenderCopy(rend, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth() const {
	return tWidth;
}

int LTexture::getHeight() const {
	return tHeight;
}