#include "App.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, char* args[]){

    Game A(SCREEN_WIDTH, SCREEN_HEIGHT);
    A.run();
    int a{};
    cin >> a;
    return 0;
}



