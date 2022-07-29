//
// Created by michal on 7.5.22.
//

#include "FAnthill.h"

FAnthill::FAnthill(const int x, const int y, const int frequency) : Character(x, y), m_birthFrequency(frequency),
                    m_passedTimeBirth(0), m_passedTimeStep(0), m_antCount(1), m_isSelected(false) {

}

FAnthill::FAnthill(const int x, const int y, const int frequency, const int antCount) : Character(x, y),
                    m_birthFrequency(frequency), m_passedTimeBirth(0), m_passedTimeStep(0), m_antCount(antCount), m_isSelected(false) {

}

void FAnthill::progress(const MatrixCoordinates & mouse) {
    // Destroyed anthill
    if (m_antCount == 0) {
        m_object.changeObject(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE, m_angle);
        return;
    }

    if (m_isSelected) // if it is selected
        m_objectSelected.changeObject(m_x, m_y, screenConstants::BLOCK_SIZE, screenConstants::BLOCK_SIZE, m_angle);
    else if (mouse.col == (int) (m_x / screenConstants::BLOCK_SIZE) && mouse.row == (int) (m_y / screenConstants::BLOCK_SIZE)) // if cursor over
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

void FAnthill::moveAnts(const MatrixCoordinates & mouse) {
    auto it = m_ants.begin();
    while (it != m_ants.end())
    {
        if ((*it)->getTarget()->getAntCount() == 0) {
            (*it)->goHome();
            m_target = std::shared_ptr<Character>();
        }
        (*it)->progress(mouse);
        if ((*it)->getTarget()->getX() == (*it)->getX() && (*it)->getTarget()->getY() == (*it)->getY()) {
            if ((*it)->getTarget()->getType() == "eanthill")
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

bool FAnthill::isSelected() const {
    return m_isSelected;
}

bool FAnthill::setSelected(bool selected) {
    m_isSelected = selected;
    return true;
}

std::string FAnthill::getType() const {
    return "fanthill";
}

bool FAnthill::setTarget(const std::shared_ptr<Character> anthill, const std::shared_ptr<Path> path) {
    m_target = anthill;
    m_path = path;
    m_isSelected = false;
    if (m_target.lock() != nullptr)
        std::cout << "Target set to: " << anthill->getType() << " " << anthill->getX() << " " << anthill->getY() << std::endl;
    return true;
}

void FAnthill::initCharacter(SDL_Renderer *renderer) {
    loadRenderer(renderer);
    m_object.initObject("assets/fanthill.bmp", m_renderer);
    m_objectHover.initObject("assets/fanthill_hover.bmp", m_renderer);
    m_objectSelected.initObject("assets/fanthill_selected.bmp", m_renderer);
}

void FAnthill::decreaseAntCount() {
    m_antCount--;
}

void FAnthill::increaseAntCount() {
    m_antCount++;
}

size_t FAnthill::getAntCount() const {
    return m_antCount;
}

std::vector<std::shared_ptr<Character>> & FAnthill::getAnts() {
    return m_ants;
}

std::string FAnthill::printInfo() const {
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
