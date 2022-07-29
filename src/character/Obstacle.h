//
// Created by michal on 20.5.22.
//

#ifndef BENESM41_OBSTACLE_H
#define BENESM41_OBSTACLE_H

#include "Character.h"

/**
 * Class of an obstacle in the map
 */
class Obstacle : public Character {
public:
    /**
     * Constructor of the obstacle
     * @param x is the X coordinate
     * @param y is the Y coordinate
     */
    Obstacle(int x, int y);
    void initCharacter(SDL_Renderer * renderer) override;
    void progress(const MatrixCoordinates & mouse) override;
    [[nodiscard]] std::string getType() const override;
    [[nodiscard]] std::string printInfo() const override;
};


#endif //BENESM41_OBSTACLE_H
