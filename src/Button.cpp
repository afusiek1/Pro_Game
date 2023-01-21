#include "Button.h"

void LButton::handleEvent(SDL_Event* e) {

	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		if (x < mPosition.x || x > mPosition.x + butSize.x || y < mPosition.y || y > mPosition.y + butSize.y) {
			mCurrentSprite = MouseElsewhere;
		}

		//Mouse is inside button
		else {
			//Set mouse over sprite
			switch (e->type) {
			case SDL_MOUSEMOTION:
				mCurrentSprite = MouseHoveringOver;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = MouseButtonClicking;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = MouseButtonNotClicked;
				break;
			}
		}
	}
}

void LButton::setButtonSize(Vec2I setButSize) {
	butSize = setButSize;
}

void LButton::render(SDL_Renderer* gRenderer) {
	//Show current button sprite
	buttonTexture->render(gRenderer, { mPosition.x, mPosition.y }, butSize);
}

void LButton::setPosition(Vec2I position) {
	mPosition = { position.x, position.y };
}

LButton::LButton() {
	mPosition = { 0, 0 };
	mCurrentSprite = LButtonSprite::MouseElsewhere;
	butSize = { 64, 64 };

}