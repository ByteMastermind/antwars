//
// Created by michal on 7.5.22.
//

#include "Character.h"

Character::Character(const int x, const int y) : m_x(x), m_y(y), m_renderer(nullptr) {

}

int Character::getX() const {
    return m_x;
}

int Character::getY() const {
    return m_y;
}

[[maybe_unused]] double Character::getAngle() const {
    return m_angle;
}

bool Character::setSelected(bool selected) {
    return false;
}

bool Character::setTarget(const std::shared_ptr<Character> anthill, const std::shared_ptr<Path> path) {
    return false;
}

bool Character::isSelected() const {
    return false;
}

void Character::loadRenderer(SDL_Renderer * renderer) {
    m_renderer = renderer;
}

std::shared_ptr<Character> Character::getTarget() const {
    return std::shared_ptr<Character>();
}

void Character::increaseAntCount() {

}

void Character::decreaseAntCount() {

}

size_t Character::getAntCount() const {
    return 0;
}

void Character::goHome() {

}

std::vector<std::shared_ptr<Character>> & Character::getAnts() {
    return m_ants;
}

std::string Character::printInfo() const {
    return std::string();
}
