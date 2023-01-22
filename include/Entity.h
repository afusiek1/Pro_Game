#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <cmath>
#include "Textures.h"
#include <vector>

using std::cin, std::cout, std::vector;

//The entity that will move around on the screen
class Entity {
public:
    //The dimensions of the entity
    const LTexture* draw;

    //Maximum velocity of the entity
    double maximumSpeed = 40;

    //Initializes the variables
    Entity(Vec2D pos, const LTexture* pointer, Vec2I size2);
    Entity();

    //Moves the entity
    void move(double elapsedTime);

    //Shows the entity on the screen
    void render(SDL_Renderer* eRenderer, Vec2D cameraPosition);

    //Updates parameters for entity
    void update(Vec2D velocity);

    //Sets entity's position
    void setPos(Vec2D pos) { position = pos; }

    //Gets entity's position
    Vec2D getPos() const { return position; }

    //Gets entity's size
    Vec2I getSize() const { return size; }

    //Map boundaries
    static void setBoundaries(int LeftBound, int RightBound, int UpBound, int DownBound);
    static int LeftBound;
    static int RightBound;
    static int UpBound;
    static int DownBound;

    //Set default texture
    static void SetDefaultTexture(const LTexture& Default);

protected:

    static LTexture DefaultTexture;

    Vec2D position;

    //The velocity of the entity
    Vec2D velocity;

    //Dimensions of entity
    Vec2I size;
};




#endif //ENTITY_H