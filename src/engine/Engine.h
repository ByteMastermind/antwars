//
// Created by michal on 25.5.22.
//

#ifndef BENESM41_ENGINE_H
#define BENESM41_ENGINE_H

#include <queue>

#include "Window.h"
#include "Character.h"
#include "Ant.h"
#include "MapFile.h"
#include "SaveFile.h"
#include "MatrixCoordinates.h"
#include "Node.h"
#include "Usings.h"


class Engine {
public:
    Engine();
    /**
     * Loads the map
     * @param filePath is the path to the map file
     */
    void loadMap(const std::string & filePath);

    void loadGameSave(const std::string & filePath);

    /**
     * Initialize all the enemy and friendly anthills
     */
    void initCharacters();

    /**
     * Runs the engine
     */
    void run();

private:
    std::vector<std::shared_ptr<Character>> m_characters;       /*!< Vector containing all the enemy and friendly anthills */
    Window m_window;                                            /*!< Window object, takes care of rendering */
    size_t m_numberOfBlocks;                                    /*!< Number of blocks from left to right calculated from screen width and size of a block */
    bool m_isRunning = false;                                   /*!< Boolean of the state of the engine */
    bool m_isSelected = false;                                  /*!< Tells if some character is selected */
    std::shared_ptr<Character> m_selectedCharacter;             /*!< Shared pointer to the selected character */
    MatrixCoordinates m_mouse;                                  /*!< Current matrix block coordinates of the cursor */
    Map<bool> m_map;                                            /*!< Map for shortest path algorithm */
    std::vector<Path> m_shortestPaths;                          /*!< Vector of shortest paths from every anthill to every other one */
    int m_AIDifficulty;                                         /*!< How often the enemy chooses new target (smaller number = more often) */

    void saveGame() const;

    /**
     * Manage events like mouse clicks, or button presses
     */
    void catchEvent();

    /**
     * Selects the friendly anthill
     * @return true, if friendly anthill was selected, false if not
     */
    [[nodiscard]] bool selectAnthill() const;

    /**
     * Checks, if there is an enemy or friendly anthill on current cursor coordinates
     * @return true if it is
     */
    [[nodiscard]] bool isTarget() const;

    /**
     * @return the shared pointer of the anthill that is currently under the cursor
     */
    [[nodiscard]] std::shared_ptr<Character> getTargetPointer() const;

    /**
     * Finds the correct path from the source anthill to the target anthill
     * @param source
     * @param target
     * @return shared pointer to the path
     */
    [[nodiscard]] std::shared_ptr<Path> getPathPointer(std::shared_ptr<Character> source, std::shared_ptr<Character> target) const;

    /**
     * Sets the enemy of the selected friendly anthill
     * @return true if it was set successfully
     */
    [[nodiscard]] bool selectTarget() const;

    /**
     * Just initialize the map for finding the shortest path by BFS
     */
    void fillMap();

    /**
     * Finds shortest paths between every anthill
     */
    void findShortestPaths();

    /**
     * BFS algorithm to find closest path from A to B
     * @param start is the start coordinates
     * @param end is the end coordinates
     */
    void findShortestPath(const MatrixCoordinates & start, const MatrixCoordinates & end);

    /**
     * Simple AI, that chooses target for enemy anthills, simply chooses anthill with lowest number of ants inside
     */
    void chooseTarget() const;

    /**
     * Checks, when the game is won or lost
     */
    void end();

    /**
     * Takes care of killing the enemyants in the battlefield
     * @param anthill is the pointer to the anthill, over which ants it will iterate
     */
    void killAnts(std::shared_ptr<Character> & anthill);

    /**
     * Finds an enemy ant, that is in the same position, and kills it
     * @param x is the X position of our ant
     * @param y is the Y position of our ant
     * @param ch is the anthill, where our ant came from
     * @return true, if ant was killed
     */
    bool isAntNear(int x, int y, std::shared_ptr<Character> ch);
};


#endif //BENESM41_ENGINE_H
