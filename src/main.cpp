#include "game.h"

int main(void)
{
    Game game("testfiles/copy_test.txt");
    game.play();
    game.save_file("testfiles/copy_test.txt");
    return 0;
}