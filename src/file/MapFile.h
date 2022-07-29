//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_MAPFILE_H
#define BENESM41_MAPFILE_H

#include "File.h"

/**
 * Class that takes care of processing the map file, where all the init stuff is stored
 */
class MapFile : public File {
public:
    /**
     * Constructor of the MapFile
     * @param filePath is the path to the file
     */
    explicit MapFile(const std::string & filePath);
    void processFile() override;

private:

    /**
     * Checks the correctness of the given numbers, throws exception in case of a problem
     * @param x is the X coordinate
     * @param y is the Y coordinate
     * @param frequency is the ant birth frequency
     */
    void checkNumbers(int x, int y, int frequency) const;
    void readAIDifficulty(const std::string & line) override;
    void readFriendlyAnthill(const std::string & line) override;
    void readEnemyAnthill(const std::string & line) override;
    void readObstacle(const std::string & line) override;
};


#endif //BENESM41_MAPFILE_H
