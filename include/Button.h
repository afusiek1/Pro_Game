#ifndef BUTTON_H
#define BUTTON_H

#include "Textures.h"

enum LButtonSprite {
	MouseElsewhere = 0,
	MouseHoveringOver = 1,
	MouseButtonClicking = 2,
	MouseButtonNotClicked = 3,
	AllTextures = 4
};

//The mouse button
class LButton{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(Vec2I position);

	//Sets button size
	void setButtonSize(Vec2I setButSize);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(SDL_Renderer* gRenderer);

	//Button textures
	LTexture* buttonTexture = NULL;

	//Change texture's alpha value
	void setAlpha(Uint8 alpha) { buttonTexture->setAlpha(alpha); }

	//Is the button pressed
	bool isPressed() const { return mCurrentSprite == MouseButtonClicking; } 

	std::string buttonName = "";

private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	//Button size
	Vec2I butSize;
};

#endif //BUTTON_H