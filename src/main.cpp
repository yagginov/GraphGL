#include "game.h"

int main(void)
{
    Game game;
    game.play();
    game.save_file("testfiles/copy_test.txt");
    return 0;
}