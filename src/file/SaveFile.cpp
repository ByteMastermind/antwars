//
// Created by michal on 7.5.22.
//

#include "SaveFile.h"

SaveFile::SaveFile(const std::string & filePath) : File(filePath), atLeastOneFAnthill(false), atLeastOneEAnthill(false) {

}

void SaveFile::processFile() {
    if (!fileExist(m_filePath))
        throw std::invalid_argument("Given map file does not exist.");

    std::ifstream f(m_filePath);
    if (!f) // File could not be opened
        throw std::runtime_error("Map file could not be opened.");

    std::string line;
    enum PART {AI, NONE, FRIENDLY, ENEMY, OBSTACLE};
    PART part = AI;
    bool haveEntry = false;
    while(std::getline(f, line)) {
        if (line.empty())
            continue;
        if (part == AI) {
            readAIDifficulty(line);
            part = NONE;
        }
        else if (part == NONE) {
            if (line != "fa")
                throw std::invalid_argument("Invalid game save file.");
            part = FRIENDLY;
        }
        else if (part == FRIENDLY) {
            if (line == "ea" && haveEntry) {
                part = ENEMY;
                haveEntry = false;
                continue;
            }
            if (line == "ea" && !haveEntry)
                throw std::invalid_argument("Invalid game save file.");

            readFriendlyAnthill(line);
            haveEntry = true;
        }
        else if (part == ENEMY) {
            if (line == "o" && haveEntry) {
                part = OBSTACLE;
                haveEntry = false;
                continue;
            }
            if (line == "o" && !haveEntry)
                throw std::invalid_argument("There must be at least one enemy anthill in the map!");

            readEnemyAnthill(line);
            haveEntry = true;
        }
        else if (part == OBSTACLE) {
            readObstacle(line);
        }
    }
    if (!atLeastOneFAnthill || !atLeastOneEAnthill)
        throw std::runtime_error("Cannot load that game save");
}

void SaveFile::readFriendlyAnthill(const std::string & line) {
    std::istringstream iss(line);
    int x, y, frequency, antCount;

    if (!(iss >> x >> y >> frequency >> antCount))
        throw std::invalid_argument("Invalid map file.");

    if (antCount > 0)
        atLeastOneFAnthill = true;

    checkNumbers(x ,y, frequency, antCount);

    FAnthill newAnthill(y * screenConstants::BLOCK_SIZE, x * screenConstants::BLOCK_SIZE, frequency, antCount);
    m_places.push_back(std::make_shared<FAnthill>(newAnthill));
}

void SaveFile::readEnemyAnthill(const std::string & line) {
    std::istringstream iss(line);
    int x, y, frequency, antCount;

    if (!(iss >> x >> y >> frequency >> antCount))
        throw std::invalid_argument("Invalid map file.");

    if (antCount > 0)
        atLeastOneEAnthill = true;

    checkNumbers(x ,y, frequency, antCount);

    EAnthill newAnthill(y * screenConstants::BLOCK_SIZE, x * screenConstants::BLOCK_SIZE, frequency, antCount);
    m_places.push_back(std::make_shared<EAnthill>(newAnthill));
}

void SaveFile::readObstacle(const std::string & line) {
    std::istringstream iss(line);
    int x, y;

    if (!(iss >> x >> y))
        throw std::invalid_argument("Invalid map file.");

    checkNumbers(x ,y, 0, 1);

    Obstacle newObstacle(y * screenConstants::BLOCK_SIZE, x * screenConstants::BLOCK_SIZE);
    m_places.push_back(std::make_shared<Obstacle>(newObstacle));
}

void SaveFile::checkNumbers(int x, int y, int frequency, int antCount) const {
    if (x > 9 || x < 0 || y > 9 || y < 0)
        throw std::invalid_argument("Wrong coordinates in the save file.");

    if (frequency < 0)
        throw std::invalid_argument("Birth frequency cannot be negative.");

    if (antCount < 0)
        throw std::invalid_argument("Ant count cannot be less than 0");

    for (auto & place : m_places) {
        if (place->getX() == x && place->getY() == y)
            throw std::invalid_argument("There are two things in one coordinate in the map file");
    }
}

void SaveFile::readAIDifficulty(const std::string &line) {
    std::istringstream iss(line);

    if (!(iss >> m_AIdifficulty))
        throw std::invalid_argument("Invalid map file.");

    if (m_AIdifficulty < 50 || m_AIdifficulty > 200)
        throw std::invalid_argument("AI difficulty beyond borders.");
}
