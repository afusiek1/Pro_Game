#ifndef APP_H
#define APP_H


#include "Entity.h"

using std::cin;

class Game {
private:
	bool init();
	bool loadMedia();
	void close();
	void render();

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path);

	//Current displayed texture
	SDL_Texture* gTexture = NULL;

	//Takes user input
	void handleEvents();

	//Updates everything
	void update();

public:
	Game(int screen_width, int screen_height);
	int screen_width = 1920;
	int screen_height = 1080;
	void run();
	Entity Test;
};


#endif //APP_H
