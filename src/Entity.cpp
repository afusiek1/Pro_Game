#include "Entity.h"

Entity::Entity(int xpos, int ypos, int width, int height)
	:draw{ xpos, ypos, width, height }, mVelX{}, mVelY{} {

}

void Entity::update(int xVel, int yVel) {
    mVelX = std::max(std::min(xVel+mVelX, REC_VEL), -REC_VEL);
    mVelY = std::max(std::min(yVel+mVelY, REC_VEL), -REC_VEL);
}

void Entity::move() {
    //Move the entity left or right
    draw.x += mVelX;

    //If the entity went too far to the left or right
    if ((draw.x < LeftBound) || (draw.x + draw.w > RightBound))
    {
        //Move back
        draw.x -= mVelX;
    }
    //Move the entity up or down
    draw.y += mVelY;

    //If the entity went too far up or down
    if ((draw.y < 0) || (draw.y + draw.h > 1080))
    {
        //Move back
        draw.y -= mVelY;
    }
}

int Entity::LeftBound = 20, Entity::RightBound = 1500;

void Entity::setBoundaries(int LB, int RB) {
    LeftBound = LB;
    RightBound = RB;
}

void Entity::render(SDL_Renderer* eRenderer) {

    //Render red rectangle
    SDL_SetRenderDrawColor(eRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(eRenderer, &draw);


}