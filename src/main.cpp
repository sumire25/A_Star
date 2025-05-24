#include "Game.hpp"
#include "conventions.hpp"

int main() {
    Game game(WIN_WIDTH/CELL_SIZE, WIN_HEIGHT/CELL_SIZE);
    game.run();

    return 0;
}
