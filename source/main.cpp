#include "Game.h"

int main(void)
{
    Game game("testfiles/lab_3.txt");
    game.play();
    game.save_file("testfiles/lab_3_t.txt");
    return 0;
}