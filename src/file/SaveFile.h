//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_SAVEFILE_H
#define BENESM41_SAVEFILE_H

#include "File.h"

/**
 * Class that takes care of processing the save file, where all the init stuff is stored
 */
class SaveFile : public File {
public:
    explicit SaveFile(const std::string & filePath);
    void processFile() override;

private:
    bool atLeastOneFAnthill;                            /*!< To check if there is at least one friendly anthill alive */
    bool atLeastOneEAnthill;                            /*!< To check if there is at least one enemy anthill alive */

    /**
     * Checks the correctness of the given numbers, throws exception in case of a problem
     * @param x is the X coordinate
     * @param y is the Y coordinate
     * @param frequency is the ant birth frequency
     * @param antCount is the amount of ants in the anthill
     */
    void checkNumbers(int x, int y, int frequency, int antCount) const;
    void readAIDifficulty(const std::string & line) override;
    void readFriendlyAnthill(const std::string & line) override;
    void readEnemyAnthill(const std::string & line) override;
    void readObstacle(const std::string & line) override;
};


#endif //BENESM41_SAVEFILE_H
