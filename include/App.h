#ifndef APP_H
#define APP_H

#include "Unit.h"
#include <SDL_timer.h>
#include <map>


class Game {
private:
	bool init();
	bool loadMedia();
	void close();
	void render();
	void initializeUnits();

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Current displayed texture
	vector<LTexture> textures;

	//Takes user input
	void handleEvents();

	//Updates everything
	void update();

public:
	Game(int screen_width, int screen_height);
	int screen_width = 1920;
	int screen_height = 1080;
	void run();
	double scale_x = 1.f;
	double scale_y = 1.f;
	std::map<std::string, Unit> unitMap;
	vector<Unit> unitList;

};


#endif //APP_H
