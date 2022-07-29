//
// Created by michal on 7.5.22.
//

#include "Ant.h"

Ant::Ant(const int x, const int y) : Character(x, y), m_distance(0), m_invertedPath(false) {

}

void Ant::progress(const MatrixCoordinates & mouse) {
    if (m_distance + (m_invertedPath ? -1 : 1) >= (*m_path).size()) // To avoid invalid read at final
        return;
    if (m_x < (*m_path)[m_distance + (m_invertedPath ? -1 : 1)].col * 100 && m_y % 100 == 0) {
        m_x += characterConstants::ANT_STEP_SIZE;
        m_angle = 90;
    }
    else if (m_x > (*m_path)[m_distance + (m_invertedPath ? -1 : 1)].col * 100 && m_y % 100 == 0) {
        m_x -= characterConstants::ANT_STEP_SIZE;
        m_angle = 270;
    }
    else if (m_y < (*m_path)[m_distance + (m_invertedPath ? -1 : 1)].row * 100 && m_x % 100 == 0) {
        m_y += characterConstants::ANT_STEP_SIZE;
        m_angle = 180;
    }
    else if (m_y > (*m_path)[m_distance + (m_invertedPath ? -1 : 1)].row * 100 && m_x % 100 == 0) {
        m_y -= characterConstants::ANT_STEP_SIZE;
        m_angle = 0;
    }
    if (m_x == (*m_path)[m_distance + (m_invertedPath ? -1 : 1)].col * 100 && m_y == (*m_path)[m_distance + (m_invertedPath ? -1 : 1)].row * 100)
        m_invertedPath ? m_distance-- : m_distance++;

    m_object.changeObject(m_x, m_y, characterConstants::ANT_WIDTH, characterConstants::ANT_HEIGHT, m_angle);
}

std::string Ant::getType() const {
    return "ant";
}

void Ant::initCharacter(SDL_Renderer * renderer) {
    loadRenderer(renderer);
    m_object.initObject("assets/ant.bmp", m_renderer);
}

std::shared_ptr<Character> Ant::getTarget() const {
    return m_target.lock();
}

bool Ant::setTarget(const std::shared_ptr<Character> anthill, const std::shared_ptr<Path> path) {
    m_target = anthill;
    m_path = path;

    if (m_target.lock()->getX() != (*m_path)[m_path->size() - 1].col * 100 || m_target.lock()->getY() != (*m_path)[m_path->size() - 1].row * 100) {
        m_invertedPath = true;
        m_distance = m_path->size() - 1;
    }
    return true;
}

void Ant::setParent(const std::shared_ptr<Character> parent) {
    m_parent = parent;
}

void Ant::goHome() {
    m_invertedPath = !m_invertedPath;
    m_target = m_parent;
}
