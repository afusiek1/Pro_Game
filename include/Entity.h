#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <string>
#include <cmath>
#include "Textures.h"
#include <vector>

using std::cin, std::vector;

//The entity that will move around on the screen
class Entity {
public:
    //The dimensions of the entity
    const LTexture* draw;

    //Maximum velocity of the entity
    static const int REC_VEL = 10;

    //Initializes the variables
    Entity(int xpos, int ypos, const LTexture* reference);
    Entity();

    //Moves the entity
    void move();

    //Shows the entity on the screen
    void render(SDL_Renderer* eRenderer);

    //Updates parameters for entity
    void update(Vec2D velocity);

    //Map boundaries
    static void setBoundaries(int LeftBound, int RightBound, int UpBound, int DownBound);
    static int LeftBound;
    static int RightBound;
    static int UpBound;
    static int DownBound;

    //Set default texture
    static void SetDefaultTexture(const LTexture& Default);

private:

    static LTexture DefaultTexture;

    Vec2D position;

    //The velocity of the entity
    Vec2D velocity;
};




#endif //ENTITY_H