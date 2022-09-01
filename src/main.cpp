/*! \mainpage Game description
 *
 * \section intro_sec Introduction
 *
 * A game simulating a war between anthills. Your job is to destroy all of the enemy anthills. If the enemy destroys you, you lose.
 *
 * \section install_sec Installation
 *
 *  run "make" inside the antwars folder
 *
 * \section run How to run
 *
 * \subsection usage Usage
 *
 * ./antwars [-s] game_file
 *
 * game_file is the file of the game location
 * "-s" mode will load a game save file
 * without this parameter, a map file should be loaded
 *
 * Providing wrong path to the file or giving a file with a wrong format will cause the error and the game won't be loaded
 *
 * \section controls Controls
 *
 * You can control only your anthills (the bright ones). By clicking on a friendly anthill you select it and then you can click
 * on another anthill to select the target, or click again on the selected anthill to cancel it. You can change the target of the anthill
 * the same way. You can send your ants not only to the enemy anthill, but even to your friendly anthill.
 *
 * To create a savefile and exit, just press 's'. It will be created in the examples folder
 *
 * \section Rules
 *
 * Each anthill has it's parameter, how often a new ant is born inside of it (it's defined in the map file or the save file).
 * When there is no ant in the anthill, the anthill will be destroyed and will no longer produce new ants and all the ants on the way
 * that came from this anthill will die.
 *
 * When ant arrives in the enemy anthill, it will decrement the number inside by 1, if it arrives in to the friendly anthill, it will increment
 * the number inside by 1.
 *
 * If two ants from different teams meet at one position in the map, both of them will die.
 *
 * If the ant destroys the enemy anthill, but there are more ants with this anthill as the target, they will return back where they came from.
 *
 * \section Map File
 * You can create your own map files, they must be in this format:
 *
 * d
 *
 * fa
 *
 * m n v
 *
 * ...
 *
 * m n v
 *
 * ea
 *
 * m n v
 *
 * ...
 *
 * m n v
 *
 * o
 *
 * m n
 *
 * ...
 *
 * m n
 *
 * Under 'fa' are described all friendly anthills (must be at least one), under 'ea' all enemy anthill (again at least one) and under
 * o all obstacles (can be without it)
 *
 * m = the line (coordination) from 0 to 9
 * n = the column (coordination) from 0 to 9
 * v = birth frequency of the anthill (how often a new ant is produced) minimal is 0
 * d = AI difficulty from 50 to 200 (50 is the hardest, 200 the easiest)
 */


#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "Engine.h"

int main(int argc, char * argv[]) {
    if (argc != 2 && argc != 3) {
        std::cout << "Invalid number of arguments" << std::endl;
        std::cout << "Usage: ./antwars [-s] gamefile" << std::endl;
        return 1;
    }
    if (argc == 3) {
        std::string flag(argv[1]);
        if (flag != "-s") {
            std::cout << "Invalid number of arguments" << std::endl;
            std::cout << "Usage: ./antwars [-s] gamefile" << std::endl;
            return 1;
        }
    }

    // Initializing
    try {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw std::runtime_error(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
    }
    catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    atexit(SDL_Quit);
    try {
        Engine engine;
        if (argc == 2)
            engine.loadMap(std::string(argv[1]));
        else
            engine.loadGameSave(std::string(argv[2]));
        engine.initCharacters();
        engine.run();
    }
    catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    SDL_Quit();
    return 0;
}