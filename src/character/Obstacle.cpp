//
// Created by michal on 20.5.22.
//

#include "Obstacle.h"

Obstacle::Obstacle(const int x, const int y) : Character(x, y) {

}

void Obstacle::progress(const MatrixCoordinates & mouse) {
    m_object.changeObject(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE, m_angle);
}

std::string Obstacle::getType() const {
    return "obstacle";
}

void Obstacle::initCharacter(SDL_Renderer * renderer) {
    loadRenderer(renderer);
    m_object.initObject("assets/obstacle.bmp", m_renderer);
}

std::string Obstacle::printInfo() const {
    std::string output;

    output.append(std::to_string(m_y / screenConstants::BLOCK_SIZE));
    output.append(" ");
    output.append(std::to_string(m_x / screenConstants::BLOCK_SIZE));
    output.append("\n");

    return output;
}
