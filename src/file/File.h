//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_FILE_H
#define BENESM41_FILE_H

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

#include "FAnthill.h"
#include "EAnthill.h"
#include "Obstacle.h"

/**
 * Base abstract class
 */
class File {
public:
    /**
     * Constructor of the File
     * @param filePath is the path to the file
     */
    explicit File(std::string filePath);

    /**
     * @return the path to the file
     */
    [[nodiscard]] std::string getFilePath() const;

    /**
     * Procceses the file = get the information, checks if all is good
     */
    virtual void processFile() = 0;

    /**
     * @return the vector containing all the initiated characters in the map file
     */
    [[nodiscard]] std::vector<std::shared_ptr<Character>> getPlaces() const;

    /**
     * @return the read AI difficulty
     */
    [[nodiscard]] int getAIdifficulty() const;

protected:
    std::string m_filePath;                             /*!< Path to the file */
    std::vector<std::shared_ptr<Character>> m_places;   /*!< All of the anthills and obstacles */
    int m_AIdifficulty;                                 /*!< How often the enemy chooses the target (higher number less often) */

    /**
     * Finds out if the file in the given destination exists
     * @param filePath is the path to the file
     * @return True if the file exists, otherwise false
     */
    static bool fileExist(const std::string & filePath);

    /**
     * Reads AI difficulty
     * @param line
     */
    virtual void readAIDifficulty(const std::string & line) = 0;

    /**
     * Reads friendly anthill
     * @param line
     */
    virtual void readFriendlyAnthill(const std::string & line) = 0;

    /**
     * Reads enemy anthill
     * @param line
     */
    virtual void readEnemyAnthill(const std::string & line) = 0;

    /**
     * Reads an obstacle
     * @param line
     */
    virtual void readObstacle(const std::string & line) = 0;
};


#endif //BENESM41_FILE_H
