#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>
#include <string>
#include <cmath>

//The entity that will move around on the screen
class Entity {
public:
    //The dimensions of the entity
    SDL_Rect draw;

    //Maximum velocity of the entity
    static const int REC_VEL = 10;

    //Initializes the variables
    Entity(int xpos, int ypos, int width, int height);
    Entity() {}

    //Moves the entity
    void move();

    //Shows the entity on the screen
    void render(SDL_Renderer* eRenderer);

    //Updates parameters for entity
    void update(int xVel, int yVel);

    //Map boundaries
    static void setBoundaries(int LeftBound, int RightBound);
    static int LeftBound;
    static int RightBound;

private:

    //The velocity of the entity
    int mVelX, mVelY;
};



#endif //ENTITY_H