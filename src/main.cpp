#include "App.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, char* args[]){


    cout << "Choose screen width (default 1920): ";
    int SCREEN_WIDTH{};
    cin >> SCREEN_WIDTH;
    cout << "Choose screen height (default 1080): ";
    int SCREEN_HEIGHT{};
    cin >> SCREEN_HEIGHT;

    Game A(SCREEN_WIDTH, SCREEN_HEIGHT);
    A.run();

    return 0;
}