// ==========================================================================
//
// Software written by Boguslaw Cyganek (C) to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================


#ifndef APP_H
#define APP_H


#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>
#include <string>
#include <cmath>

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


public:
	Game(int screen_width, int screen_height);
	int screen_width = 1920;
	int screen_height = 1080;
	void run();
};



#endif //APP_H
