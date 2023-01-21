#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

//Struct of positions of entities textures
struct Vec2D {
    int x;
    int y;
    Vec2D operator - (const Vec2D& other) const {
        return { this->x - other.x, this->y - other.y };
    }
};

//Texture wrapper class
class LTexture {
public:

    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(SDL_Renderer* rend, std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(SDL_Renderer* rend, Vec2D position) const;
    void render(SDL_Renderer* rend, Vec2D position, Vec2D size) const;
    void render(SDL_Renderer* rend, int x, int y) const;

    //Gets image dimensions
    int getWidth() const;
    int getHeight() const;

    //Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* tFont);

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int tWidth;
    int tHeight;
};

//Enum for all textures
enum TextureID { Default = 0, Background, Crow, size };




#endif //TEXTURES_H