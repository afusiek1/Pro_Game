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
    textures.resize(TextureID::SIZE, LTexture());

    //Load default texture
    if (!textures[TextureID::DEFAULT].loadFromFile(gRenderer, "Default.png")) {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    Entity::SetDefaultTexture(textures[TextureID::DEFAULT]);

    //Load background texture
    if (!textures[TextureID::BACKGROUND].loadFromFile(gRenderer, "Bckgnd.png")) {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load Crow od Judgement
    if (!textures[TextureID::CROW].loadFromFile(gRenderer, "Crow.png")) {
        printf("Failed to load Crow od Judgement!\n");
        success = false;
    }

    //Open the font
    gFont = TTF_OpenFont("../../../Font/ka1.ttf", (int) (16 * scale_y));
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

    Vec2I UnitSize = unitMap[currentUnit].getSize();

    /////Render blue zone of putting units /////

    //Left boundary
    SDL_Rect fillRect = { screen_width / 16 + (int)(UnitSize.x/2 * scale_x), screen_height / 2 + (int)(UnitSize.y/2 * scale_y) - (int)cameraPosition.y, 1, screen_height * 3 / 8  - (int)(UnitSize.y * scale_y) };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Bottom boundary
    fillRect = { screen_width / 16 + (int)(UnitSize.x / 2 * scale_x), screen_height * 7 / 8 - (int)(UnitSize.y / 2 * scale_y) - (int)cameraPosition.y, screen_width * 5 / 8 - (int)(UnitSize.x * scale_x) , 1 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Right boundary
    fillRect = { screen_width / 16 + (int)(UnitSize.x / 2 * scale_x) + screen_width * 5 / 8 - (int)(UnitSize.x * scale_x) , screen_height / 2 + (int)(UnitSize.y / 2 * scale_y) - (int)cameraPosition.y, 1, screen_height * 3 / 8 - (int)(UnitSize.y * scale_y) };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Top boundary
    fillRect = { screen_width / 16 + (int)(UnitSize.x / 2 * scale_x), screen_height / 2 + (int)(UnitSize.y / 2 * scale_y) - (int)cameraPosition.y, screen_width * 5 / 8 - (int)(UnitSize.x * scale_x) , 1 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);


    /////Render pink map boundaries/////

    //Left boundary
    fillRect = { screen_width / 16 - 6, screen_height / 16, 6, screen_height * 7 / 8 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Bottom boundary
    fillRect = { screen_width / 16 - 6, screen_height * 15 / 16, screen_width * 5 / 8 + 12, 6 };
    SDL_SetRenderDrawColor(gRenderer, 0xDB, 0x4A, 0xE0, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    //Right boundary
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
    textures[TextureID::BACKGROUND].render(gRenderer, { 0, 0 }, {screen_width, screen_height});

    for (int i{};i < unitList.size();++i) {
        if (unitList[i].getPos().y - cameraPosition.y < screen_height * 15 / 16 && unitList[i].getPos().y + unitList[i].getSize().y - cameraPosition.y > screen_height / 16) {
            unitList[i].render(gRenderer, cameraPosition);
        }
    }

    RenderMap();

    for (int i{};i < allButtons.size(); ++i) {
        if (allButtons[i].buttonName == currentUnit) allButtons[i].setAlpha(128);
        allButtons[i].render(gRenderer);
        allButtons[i].setAlpha(255);
    }

    TextRender();

    //Update screen
    SDL_RenderPresent(gRenderer);
}

void Game::TextRender() {

    //In memory text stream
    std::stringstream timeText;

    //Set text to be rendered
    timeText.str("");
    timeText << "t  " << elapsedTime << "ms  fps  " << 1000.0 / (double)elapsedTime;

    //Render text
    if (!frameInfo.loadFromRenderedText(timeText.str().c_str(), textColor, gRenderer, gFont)) {
        printf("Unable to render time related texture!\n");
    }

    //Render text
    frameInfo.render(gRenderer, { std::min(screen_width - frameInfo.getWidth(), screen_width * 7 / 8), (int)(10 * scale_y) });

    //In memory text stream
    std::stringstream unitText;

    //Set text to be rendered
    unitText.str("");
    unitText << "Selected unit  " << currentUnit;

    //Render text
    if (!frameInfo.loadFromRenderedText(unitText.str().c_str(), textColor, gRenderer, gFont)) {
        printf("Unable to render unit related texture!\n");
    }

    //Render text
    frameInfo.render(gRenderer, { std::min(screen_width - frameInfo.getWidth(), screen_width * 7 / 8), screen_height - (int)(30 * scale_y) });
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
            case SDLK_UP: cameraVelocity -= cameraAddSpeed; break;
            case SDLK_DOWN: cameraVelocity += cameraAddSpeed; break;
            }
        }

        else if (e.type == SDL_KEYDOWN && e.key.repeat > 0) {

            //Adjust the velocity
            //switch (e.key.keysym.sym) {
            //case SDLK_UP: cameraPosition.y -= cameraSpeed * elapsedTime; break;
            //case SDLK_DOWN: cameraPosition.y += cameraSpeed * elapsedTime; break;
            //}
        }

        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP: cameraVelocity += cameraAddSpeed; break;
            case SDLK_DOWN: cameraVelocity -= cameraAddSpeed; break;
            }
        }
        //If mouse event happened
        else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {

            //Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            Vec2I UnitSize = unitMap[currentUnit].getSize();

            if ((x > screen_width / 16 + UnitSize.x / 2) && (x < screen_width * 11 / 16 - UnitSize.x / 2) && (y > screen_height / 2 + cameraPosition.y + UnitSize.y / 2) && (y < screen_height * 7 / 8 + cameraPosition.y - UnitSize.y / 2)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    Unit UnitTemp = unitMap[currentUnit];
                    UnitTemp.setPos({ x - UnitSize.x / 2, y - UnitSize.y / 2 });
                    UnitTemp.update({ 0.0, -0.1 });
                    unitList.push_back(UnitTemp);
                }
            }
            else {
                for (int i{}; i < allButtons.size(); ++i) {
                    allButtons[i].handleEvent(&e);
                }
            }
        }
    }
}

void Game::update() {

    Uint32 time = SDL_GetTicks();
    elapsedTime = (double) (time - lastTime);
    lastTime = time;

    cameraPosition.y = std::min(cameraPosition.y + cameraVelocity * elapsedTime, 0.0);
    cameraPosition.y = std::max(cameraPosition.y, (double) - screen_height);

    for (int i{};i < unitList.size();++i) {
        unitList[i].move(elapsedTime);
    }

    vector<int> pressedButtons;

    for (int j{}; j < allButtons.size(); ++j) {
        if (allButtons[j].isPressed()) {
            pressedButtons.push_back(j);
        }
    }
    for (int i{}; i < pressedButtons.size(); ++i) {
        std::string name = allButtons[pressedButtons[i]].buttonName;
        if (name == "Rifleman") currentUnit = "Rifleman";
        else if (name == "Machine Gunner") currentUnit = "Machine Gunner";
        else if (name == "Sniper") currentUnit = "Sniper";
        else if (name == "Bazooker") currentUnit = "Bazooker";
        else if (name == "Car with machine gun") currentUnit = "Car with machine gun";
        else if (name == "Armored Car with turret") currentUnit = "Armored Car with turret";
        else if (name == "RPG Car") currentUnit = "RPG Car";
        else if (name == "Minigun Car") currentUnit = "Minigun Car";
        else if (name == "Tank") currentUnit = "Tank";
        else if (name == "Big Tank") currentUnit = "Big Tank";
        else if (name == "Artillery") currentUnit = "Artillery";
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
    unitMap["None Selected"] = Unit(1000.0, 500, 1000, 1000, 0.4, 10, 10, true, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::CROW], { (int)(0 * scale_x), (int)(0 * scale_y) });

    //Bases
    unitMap["Blue Base"] = Unit(5000.0, 0, 0, 0, 1, 0, 5, false, "Base", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Red Base"] = Unit(5000.0, 0, 0, 0, 1, 0, 5, false, "Base", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(64 * scale_x), (int)(64 * scale_y) });

    //Infantry units
    unitMap["Rifleman"] = Unit(15.0, 50, 70, 2.5, 1.2, 4, 0, false, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(32 * scale_x), (int)(32 * scale_y) });
    unitMap["Machine Gunner"] = Unit(30.0, 40, 60, 2, 0.4, 3, 0, false, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(32 * scale_x), (int)(32 * scale_y) });
    unitMap["Sniper"] = Unit(10.0, 120, 150, 12, 3, 4, 0, false, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(32 * scale_x), (int)(32 * scale_y) });
    unitMap["Bazooker"] = Unit(35.0, 60, 75, 50, 5, 3, 0, true, "Infantry", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(32 * scale_x), (int)(32 * scale_y) });

    //Car units
    unitMap["Car with machine gun"] = Unit(55.0, 45, 65, 2, 0.35, 8, 1, false, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Armored Car with turret"] = Unit(110.0, 65, 80, 10, 1.4, 6, 2, false, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["RPG Car"] = Unit(70.0, 70, 90, 50, 5, 8, 1, true, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(64 * scale_x), (int)(64 * scale_y) });
    unitMap["Minigun Car"] = Unit(140.0, 30, 60, 4, 0.2, 10, 1, false, "Car", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(64 * scale_x), (int)(64 * scale_y) });

    //Tank units
    unitMap["Tank"] = Unit(240.0, 60, 80, 25, 2, 2, 3, false, "Tank", { screen_width / 3, screen_height / 3 }, &textures[TextureID::DEFAULT], { (int)(96 * scale_x), (int)(96 * scale_y) });
    unitMap["Big Tank"] = Unit(450.0, 70, 90, 40, 3, 2, 4, false, "Tank", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(96 * scale_x), (int)(96 * scale_y) });
    unitMap["Artillery"] = Unit(160.0, 150, 200, 120, 8, 1, 3, true, "Tank", { screen_width / 2, screen_height / 2 }, &textures[TextureID::DEFAULT], { (int)(96 * scale_x), (int)(96 * scale_y) });
}

void Game::initializeButtons() {

    allButtons = vector<LButton>(11);
    
    /////Set buttons/////

    //row 1
    allButtons[0].setPosition({ (int) (screen_width * 3 / 4 + 96 * scale_x), screen_height / 16 });
    allButtons[0].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[0].buttonTexture = &textures[TextureID::DEFAULT];
    allButtons[0].buttonName = "Rifleman";

    allButtons[1].setPosition({ (int) (screen_width * 3 / 4 + 224 * scale_x) , screen_height / 16 });
    allButtons[1].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[1].buttonTexture = &textures[TextureID::CROW];
    allButtons[1].buttonName = "Machine Gunner";

    allButtons[2].setPosition({ (int) (screen_width * 3 / 4 + 352 * scale_x), screen_height / 16 });
    allButtons[2].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[2].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[2].buttonName = "Sniper";

    //row 2
    allButtons[3].setPosition({ (int)(screen_width * 3 / 4 + 96 * scale_x), screen_height * 3 / 16 });
    allButtons[3].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[3].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[3].buttonName = "Bazooker";

    allButtons[4].setPosition({ (int)(screen_width * 3 / 4 + 224 * scale_x), screen_height * 3 / 16 });
    allButtons[4].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[4].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[4].buttonName = "Car with machine gun";

    allButtons[5].setPosition({ (int)(screen_width * 3 / 4 + 352 * scale_x), screen_height * 3 / 16 });
    allButtons[5].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[5].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[5].buttonName = "Armored Car with turret";

    //row 3
    allButtons[6].setPosition({ (int)(screen_width * 3 / 4 + 96 * scale_x), screen_height * 5 / 16 });
    allButtons[6].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[6].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[6].buttonName = "RPG Car";

    allButtons[7].setPosition({ (int)(screen_width * 3 / 4 + 224 * scale_x), screen_height * 5 / 16 });
    allButtons[7].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[7].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[7].buttonName = "Minigun Car";

    allButtons[8].setPosition({ (int)(screen_width * 3 / 4 + 352 * scale_x), screen_height * 5 / 16 });
    allButtons[8].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[8].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[8].buttonName = "Tank";

    //row 4
    allButtons[9].setPosition({ (int)(screen_width * 3 / 4 + 96 * scale_x), screen_height * 7 / 16 });
    allButtons[9].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[9].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[9].buttonName = "Big Tank";

    allButtons[10].setPosition({ (int)(screen_width * 3 / 4 + 224 * scale_x), screen_height * 7 / 16 });
    allButtons[10].setButtonSize({ (int)(64 * scale_x), (int)(64 * scale_y) });
    allButtons[10].buttonTexture = &textures[TextureID::BACKGROUND];
    allButtons[10].buttonName = "Artillery";
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
            Entity::setBoundaries(screen_width / 16, screen_width * 11 / 16, - screen_height * 15 / 16, screen_height * 15 / 16);

            initializeUnits();
            initializeButtons();
        }
    }
}