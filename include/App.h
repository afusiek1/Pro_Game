#ifndef APP_H
#define APP_H

#include "Unit.h"
#include "Button.h"
#include <SDL_timer.h>
#include <map>


class Game {
private:
	bool init();
	bool loadMedia();
	void close();
	void render();
	void initializeUnits();
	void initializeButtons();

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

	//Renders text
	void TextRender();

	//Render map boundaries
	void RenderMap();

	//Camera speed
	const double cameraAddSpeed = 1;

	//Camera velociy
	double cameraVelocity{};

	//Frame information
	LTexture frameInfo;

	//Set text color as black
	SDL_Color textColor = { 255, 255, 255, 255 };

	//Globally used font
	TTF_Font* gFont = NULL;

	//Current time start time
	Uint32 lastTime = 0;
	double elapsedTime = 0;

	//Vector of all buttons
	vector<LButton> allButtons;

	//Selected unit
	std::string currentUnit = "None selected";

public:
	Game(int screen_width, int screen_height);

	int screen_width = 1920;
	int screen_height = 1080;
	void run();
	double scale_x = 1.f;
	double scale_y = 1.f;

	Vec2D cameraPosition = { 0,0 };

	std::map<std::string, Unit> unitMap;
	vector<Unit> unitList;

};


#endif //APP_H
