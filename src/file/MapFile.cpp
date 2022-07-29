//
// Created by michal on 7.5.22.
//

#include "MapFile.h"

MapFile::MapFile(const std::string & filePath) : File(filePath) {

}

void MapFile::processFile() {
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
                throw std::invalid_argument("Invalid map file.");
            part = FRIENDLY;
        }
        else if (part == FRIENDLY) {
            if (line == "ea" && haveEntry) {
                part = ENEMY;
                haveEntry = false;
                continue;
            }
            if (line == "ea" && !haveEntry)
                throw std::invalid_argument("There must be at least one friendly anthill in the map!");

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
}

void MapFile::checkNumbers(const int x, const int y, const int frequency) const {
    if (x > 9 || x < 0 || y > 9 || y < 0)
        throw std::invalid_argument("Wrong coordinates in the map file.");

    if (frequency < 0)
        throw std::invalid_argument("Birth frequency cannot be negative.");

    for (auto & place : m_places) {
        if (place->getX() == x && place->getY() == y)
            throw std::invalid_argument("There are two things in one coordinate in the map file");
    }
}

void MapFile::readFriendlyAnthill(const std::string & line) {
    std::istringstream iss(line);
    int x, y, frequency;

    if (!(iss >> x >> y >> frequency))
        throw std::invalid_argument("Invalid map file.");

    checkNumbers(x ,y, frequency);

    FAnthill newAnthill(y * screenConstants::BLOCK_SIZE, x * screenConstants::BLOCK_SIZE, frequency);
    m_places.push_back(std::make_shared<FAnthill>(newAnthill));
}

void MapFile::readEnemyAnthill(const std::string &line) {
    std::istringstream iss(line);
    int x, y, frequency;

    if (!(iss >> x >> y >> frequency))
        throw std::invalid_argument("Invalid map file.");

    checkNumbers(x ,y, frequency);

    EAnthill newAnthill(y * screenConstants::BLOCK_SIZE, x * screenConstants::BLOCK_SIZE, frequency);
    m_places.push_back(std::make_shared<EAnthill>(newAnthill));
}

void MapFile::readObstacle(const std::string &line) {
    std::istringstream iss(line);
    int x, y;

    if (!(iss >> x >> y))
        throw std::invalid_argument("Invalid map file.");

    checkNumbers(x ,y, 0);

    Obstacle newObstacle(y * screenConstants::BLOCK_SIZE, x * screenConstants::BLOCK_SIZE);
    m_places.push_back(std::make_shared<Obstacle>(newObstacle));
}

void MapFile::readAIDifficulty(const std::string &line) {
    std::istringstream iss(line);

    if (!(iss >> m_AIdifficulty))
        throw std::invalid_argument("Invalid map file.");

    if (m_AIdifficulty < 50 || m_AIdifficulty > 200)
        throw std::invalid_argument("AI difficulty beyond borders.");
}
