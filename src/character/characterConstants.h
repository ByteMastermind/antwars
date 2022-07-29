//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_CHARACTERCONSTANTS_H
#define BENESM41_CHARACTERCONSTANTS_H

#include <cstddef>

/**
 * All constants connected with each character
 */
namespace characterConstants {
    const size_t ANT_WIDTH = 100;                       /*!< Ant width, the same as width of ant.bmp */
    const size_t ANT_HEIGHT = 100;                      /*!< Ant height, the same as height of ant.bmp */
    const int ANT_STEP_SIZE = 5;                        /*!< How many pixels the ant moves each iteration, ANT_STEP_SIZE % screenConstants::BLOCK_SIZE must be 0 */
    const size_t CHANGE_TARGET_FREQ = 100;              /*!< How often AI anthills chooses enemy. Higher number means smaller frequency */
    const size_t BIRTH_FREQ = 900;                      /*!< How often is a new ant born in each of the anthills. Higher number means smaller frequency */
    const size_t SET_OFF_FREQ = 50;                     /*!< How often an ant set of from an anthill to the war. Higher number means smaller frequency */
}

#endif //BENESM41_CHARACTERCONSTANTS_H
