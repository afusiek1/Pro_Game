#include "Entity.h"

Entity::Entity(int xpos, int ypos,const LTexture* reference)
    :draw(reference), position{ xpos, ypos }, velocity {0,0} {

}

Entity::Entity()
    :draw(&DefaultTexture), position{ 0, 0 }, velocity{ 0,0 } {
}

void Entity::update(Vec2D v) {
    velocity.x = std::max(std::min(v.x+velocity.x, REC_VEL), -REC_VEL);
    velocity.y = std::max(std::min(v.y+velocity.y, REC_VEL), -REC_VEL);
}

void Entity::move() {
    //Move the entity left or right
    position.x += velocity.x;

    //If the entity went too far to the left or right
    if ((position.x < LeftBound) || (position.x + draw->getWidth() > RightBound)) {
        //Move back
        position.x -= velocity.x;
    }
    //Move the entity up or down
    position.y += velocity.y;

    //If the entity went too far up or down
    if ((position.y < UpBound) || (position.y + draw->getHeight() > DownBound)) {
        //Move back
        position.y -= velocity.y;
    }
}

int Entity::LeftBound = 20, Entity::RightBound = 1500, Entity::UpBound = 0, Entity::DownBound = 180;
LTexture Entity::DefaultTexture = LTexture();

void Entity::setBoundaries(int LB, int RB, int UB, int DB) {
    LeftBound = LB;
    RightBound = RB;
    UpBound = UB;
    DownBound = DB;
}

void Entity::SetDefaultTexture(const LTexture& Default) {
    DefaultTexture = Default;
}

void Entity::render(SDL_Renderer* eRenderer) {

    //Render CROW OF JUDGMENT

    draw->render(eRenderer, position);

}

