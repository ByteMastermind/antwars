//
// Created by michal on 20.5.22.
//

#include "EAnthill.h"

EAnthill::EAnthill(const int x, const int y, const int frequency) : Character(x, y), m_birthFrequency(frequency),
                    m_passedTimeBirth(0), m_passedTimeStep(0), m_antCount(1) {

}

EAnthill::EAnthill(const int x, const int y, const int frequency, const int antCount) : Character(x, y),
                    m_birthFrequency(frequency), m_passedTimeBirth(0), m_passedTimeStep(0), m_antCount(antCount) {

}

void EAnthill::progress(const MatrixCoordinates & mouse) {
    // Destroyed anthill
    if (m_antCount == 0) {
        m_object.changeObject(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE, m_angle);
        return;
    }

    if (mouse.col == (int) (m_x / screenConstants::BLOCK_SIZE) && mouse.row == (int) (m_y / screenConstants::BLOCK_SIZE)) // if cursor is over
        m_objectHover.changeObject(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE, m_angle);
    else    // normal state
        m_object.changeObject(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE, m_angle);

    if (m_passedTimeBirth++ > (unsigned)(characterConstants::BIRTH_FREQ / m_birthFrequency)) {
        m_passedTimeBirth = 0;
        m_antCount++;
    }

    if (++m_passedTimeStep % characterConstants::SET_OFF_FREQ == 0 && m_target.lock() != nullptr &&
        m_target.lock()->getAntCount() != 0 && m_antCount - 1 > 0 && m_antCount - 1 < 9999) {

        Ant a(m_x, m_y);
        a.setTarget(m_target.lock(), m_path);
        a.setParent(shared_from_this());
        m_ants.push_back(std::make_shared<Ant>(a));
        m_ants[m_ants.size() - 1]->initCharacter(m_renderer);
        m_antCount--;
    }

    moveAnts(mouse);

    m_text.initText(std::to_string(m_antCount), m_renderer);
    m_text.renderText(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE);
}

void EAnthill::moveAnts(const MatrixCoordinates &mouse) {
    auto it = m_ants.begin();
    while (it != m_ants.end())
    {
        if ((*it)->getTarget()->getAntCount() == 0) {
            (*it)->goHome();
            m_target = std::shared_ptr<Character>();
        }
        (*it)->progress(mouse);
        if ((*it)->getTarget()->getX() == (*it)->getX() && (*it)->getTarget()->getY() == (*it)->getY()) {
            if ((*it)->getTarget()->getType() == "fanthill")
                (*it)->getTarget()->decreaseAntCount();
            else
                (*it)->getTarget()->increaseAntCount();
            it = m_ants.erase(it);
            std::cout << "Ant dead" << std::endl;
        }
        else
            ++it;
    }
}

std::string EAnthill::getType() const {
    return "eanthill";
}

void EAnthill::initCharacter(SDL_Renderer *renderer) {
    loadRenderer(renderer);
    m_object.initObject("assets/eanthill.bmp", m_renderer);
    m_objectHover.initObject("assets/eanthill_hover.bmp", m_renderer);
}

void EAnthill::decreaseAntCount() {
    m_antCount--;
}

void EAnthill::increaseAntCount() {
    m_antCount++;
}

size_t EAnthill::getAntCount() const {
    return m_antCount;
}

bool EAnthill::setTarget(std::shared_ptr<Character> anthill, std::shared_ptr<Path> path) {
    m_target = anthill;
    m_path = path;
    if (m_target.lock() != nullptr)
        std::cout << "Target set to: " << anthill->getType() << " " << anthill->getX() << " " << anthill->getY() << std::endl;
    return true;
}

std::vector<std::shared_ptr<Character>> & EAnthill::getAnts() {
    return m_ants;
}

std::string EAnthill::printInfo() const {
    std::string output;

    output.append(std::to_string(m_y / screenConstants::BLOCK_SIZE));
    output.append(" ");
    output.append(std::to_string(m_x / screenConstants::BLOCK_SIZE));
    output.append(" ");
    output.append(std::to_string(m_birthFrequency));
    output.append(" ");
    output.append(std::to_string(m_antCount));
    output.append("\n");

    return output;
}
