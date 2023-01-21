#include "App.h"
#include <sstream>



bool Game::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{

        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
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
                if (!(IMG_Init(imgFlags) & imgFlags)) {
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
    if (!textures[TextureID::Default].loadFromFile(gRenderer, "Default.png")) {
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

    //Open the font
    gFont = TTF_OpenFont("../../../Font/ka1.ttf", 16);
    if (gFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
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

    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void Game::RenderMap() {

    /////Render pink map boundaries/////

//Left boundary
    SDL_Rect fillRect = { screen_width / 16 - 6, screen_height / 16, 6, screen_height * 7 / 8 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Bottom boundary
    fillRect = { screen_width / 16 - 6, screen_height * 15 / 16, screen_width * 5 / 8 + 12, 6 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //right boundary
    fillRect = { screen_width * 11 / 16, screen_height / 16, 6, screen_height * 15 / 16 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Shop boundary
    fillRect = { screen_width * 3 / 4, 0, 10, screen_height };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Top boundary
    fillRect = { screen_width * 1 / 16, screen_height / 16, screen_width * 5 / 8 , 6 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    /////Render black void between map and shop/////

    //Blackness on the left
    fillRect = { 0, 0, screen_width / 16 - 6, screen_height };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Blackness on the bottom
    fillRect = { screen_width / 16 - 6 ,  screen_height * 15 / 16 + 6, screen_width * 11 / 16 + 6, screen_height / 16 - 6 };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Blackness between right boundary and shop 
    fillRect = { screen_width * 11 / 16 + 6, 0, screen_width / 16 - 6, screen_height * 15 / 16 + 6 };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Blackness on top
    fillRect = { screen_width / 16 - 6 , 0, screen_width * 5 / 8 + 12, screen_height / 16 };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
}

void Game::render() {

    //Clear screen
    SDL_RenderClear(gRenderer);

    //Render texture to screen
    textures[TextureID::Background].render(gRenderer, { 0, 0 }, {screen_width, screen_height});

    for (int i{};i < unitList.size();++i) {
        if (unitList[i].getPos().y - cameraPosition.y < screen_height * 15 / 16 && unitList[i].getPos().y + unitList[i].getSize().y - cameraPosition.y > screen_height / 16) {
            unitList[i].render(gRenderer, cameraPosition);
        }
    }

    RenderMap();

    //In memory text stream
    std::stringstream timeText;

    //Set text to be rendered
    timeText.str("");
    timeText << "t: " << elapsedTime << "ms  fps: " << 1000.0/(double)elapsedTime;

    //Render text
    if (!frameInfo.loadFromRenderedText(timeText.str().c_str(), textColor, gRenderer, gFont))
    {
        printf("Unable to render time related texture!\n");
    }

    //Render text
    frameInfo.render(gRenderer, { std::min(screen_width - frameInfo.getWidth(), screen_width * 7 / 8), 10 });

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
            case SDLK_UP: cameraPosition.y -= 30; break;
            case SDLK_DOWN: cameraPosition.y += 10; break;
            }
        }

        else if (e.type == SDL_KEYDOWN && e.key.repeat > 0) {

            //Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP: cameraPosition.y -= 30; break;
            case SDLK_DOWN: cameraPosition.y += 10; break;
            }
        }

        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            //Adjust the velocity
            //switch (e.key.keysym.sym) {
            //case SDLK_UP: unitList[i].update({ 0, 2 }); break;
            //case SDLK_DOWN: unitList[i].update({ 0, -2 }); break;
            //}
        }
    }
    cameraPosition.y = std::min(cameraPosition.y, 0);
    cameraPosition.y = std::max(cameraPosition.y, -screen_height);
}

void Game::update() {

    Uint32 time = SDL_GetTicks();
    elapsedTime = time - lastTime;
    lastTime = time;

    for (int i{};i < unitList.size();++i) {
        unitList[i].move();
    }
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

void Game::initializeUnits() {

    //Debug player unit
    unitMap["Player"] = Unit(1000.0, 500, 1000, 1000, 0.4, 10, 10, true, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Crow], { (int)(64 * scale_x), (int)(64 * scale_y) });

    //Bases
    unitMap["Blue Base"] = Unit(5000.0, 0, 0, 0, 1, 0, 5, false, "Base", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Red Base"] = Unit(5000.0, 0, 0, 0, 1, 0, 5, false, "Base", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });

    //Infantry units
    unitMap["Rifleman"] = Unit(15.0, 50, 70, 2.5, 1.2, 4, 0, false, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Machine Gunner"] = Unit(30.0, 40, 60, 2, 0.4, 3, 0, false, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Sniper"] = Unit(10.0, 120, 150, 12, 3, 4, 0, false, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Bazooker"] = Unit(35.0, 60, 75, 50, 5, 3, 0, true, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });

    //Car units
    unitMap["Car with machine gun"] = Unit(55.0, 45, 65, 2, 0.35, 8, 1, false, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Armored Car with turret"] = Unit(110.0, 65, 80, 10, 1.4, 6, 2, false, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["RPG Car"] = Unit(70.0, 70, 90, 50, 5, 8, 1, true, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Minigun Car"] = Unit(140.0, 30, 60, 4, 0.2, 10, 1, false, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });

    //Tank units
    unitMap["Tank"] = Unit(240.0, 60, 80, 25, 2, 2, 3, false, "Tank", { screen_width / 3, screen_height / 3 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Big Tank"] = Unit(450.0, 70, 90, 40, 3, 2, 4, false, "Tank", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Artillery"] = Unit(160.0, 150, 200, 120, 8, 1, 3, true, "Tank", { screen_width / 2, screen_height / 2 }, &textures[TextureID::Default], { (int)(64 * scale_x), (int)(64 * scale_y) });

    unitList.push_back(unitMap["Tank"]);
    unitList.push_back(unitMap["Player"]);
    unitList.push_back(unitMap["Player"]);
    unitList[2].setPos({ 200,200 });

}

Game::Game(int screen_width, int screen_height)
:screen_width(screen_width),screen_height(screen_height) {

    scale_x = (double) screen_width / 1920.f;
    scale_y = (double) screen_height / 1080.f;

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

            initializeUnits();

            //unitMap["Player"] = Entity({screen_width / 2, screen_height / 2}, &textures[TextureID::Crow], { (int)(32 * scale_x), (int)(32 * scale_y) });
        }
    }

}



