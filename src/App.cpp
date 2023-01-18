#include "App.h"



bool Game::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("Base defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {

            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool Game::loadMedia() {
    //Loading success flag
    bool success = true;

    //Initializing vector of textures
    textures.resize(TextureID::size, LTexture());

    //Load default texture
    if (!textures[TextureID::Background].loadFromFile(gRenderer, "Default.png")) {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    Entity::SetDefaultTexture(textures[TextureID::Default]);

    //Load background texture
    if (!textures[TextureID::Background].loadFromFile(gRenderer, "Bckgnd.png")) {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load Crow od Judgement
    if (!textures[TextureID::Crow].loadFromFile(gRenderer, "Crow.png")) {
        printf("Failed to load Crow od Judgement!\n");
        success = false;
    }

    return success;
}

void Game::close() {

    //Free images
    for (int i{}; i < textures.size(); ++i) {
        textures[i].free();
    }

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void Game::render() {

    //Clear screen
    SDL_RenderClear(gRenderer);

    //Render texture to screen
    textures[TextureID::Background].render(gRenderer, 0, 0 );

    Test.render(gRenderer);

    //Render map boundaries
    SDL_Rect fillRect = { (screen_width / 16) - 6, 0, 6, screen_height * 5 / 6 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
    fillRect = { (screen_width / 16) - 6, screen_height * 5 / 6, screen_width * 10 / 16 + 12, 6 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
    fillRect = { (screen_width * 11 / 16), 0, 6, screen_height * 5 / 6 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Update screen
    SDL_RenderPresent(gRenderer);
}

void Game::handleEvents() {

    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        //If a key was pressed
        else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP: Test.update({ 0, -2 }); break;
            case SDLK_DOWN: Test.update({ 0, 2 }); break;
            case SDLK_LEFT: Test.update({ -2, 0 }); break;
            case SDLK_RIGHT: Test.update({ 2, 0 }); break;
            }
        }
        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP: Test.update({ 0, 2 }); break;
            case SDLK_DOWN: Test.update({ 0, -2 }); break;
            case SDLK_LEFT: Test.update({ 2, 0 }); break;
            case SDLK_RIGHT: Test.update({ -2, 0 }); break;
            }
        }
    }
}

void Game::update() {
    Test.move();
}

void Game::run() {
    //While application is running
    while (!quit) {
        
        handleEvents();

        update();

        render();

    }

    //Free resources and close SDL
    close();
}

Game::Game(int screen_width, int screen_height)
:screen_width(screen_width),screen_height(screen_height) {


    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            Entity::setBoundaries(screen_width / 16, screen_width * 11 / 16, 0, screen_height * 5 / 6);
            Test = Entity(screen_width / 2, screen_height /2, &textures[TextureID::Crow]);
        }
    }

}



