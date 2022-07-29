//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_FANTHILL_H
#define BENESM41_FANTHILL_H

#include "Character.h"
#include "Ant.h"


/**
 * Class of an friendly anthill
 */
class FAnthill : public Character, public std::enable_shared_from_this<FAnthill> {
public:
    /**
     * Constructor of the friendly anthill
     * @param x is the X coordinate
     * @param y is the Y coordinate
     * @param frequency is the new ant birth frequency
     */
    FAnthill(int x, int y, int frequency);

    /**
     * Constructor of the friendly anthill used in loading the game save
     * @param x is the X coordinate
     * @param y is the Y coordinate
     * @param frequency is the new ant birth frequency
     * @param antCount is the amount of ants in the anthill
     */
    FAnthill(int x, int y, int frequency, int antCount);
    void initCharacter(SDL_Renderer * renderer) override;
    void progress(const MatrixCoordinates & mouse) override;
    [[nodiscard]] bool isSelected() const override;
    bool setSelected(bool selected) override;
    [[nodiscard]] std::string getType() const override;
    bool setTarget(std::shared_ptr<Character> anthill, std::shared_ptr<Path> path) override;
    [[nodiscard]] size_t getAntCount() const override;
    void increaseAntCount() override;
    void decreaseAntCount() override;
    std::vector<std::shared_ptr<Character>> & getAnts() override;
    std::string printInfo() const override;

private:
    int m_birthFrequency;                      /*!< Holds frequency, how often the anthill produces a new ant */
    size_t m_passedTimeBirth;                  /*!< Number of iterations passed, for measuring time between births */
    size_t m_passedTimeStep;                   /*!< Number of iterations passed, for measuring time between the ants going out of the anthill */
    size_t m_antCount;                         /*!< Number of ants in the anthill */
    bool m_isSelected;                         /*!< True, if this anthill is currently selected by the user */
    Object m_objectHover;                      /*!< Object, that holds the texture, when the cursor is over the character */
    Object m_objectSelected;                   /*!< Object, that holds the texture, when this character is selected */
    Text m_text;                               /*!< Text object, cares of rendering the number of ants in each anthill */

    /**
     * Moves each ant that belongs to this anthill, takes care of in/de creasing the antcount when arriving to another anthill
     * @param mouse is the cursor coordinates
     */
    void moveAnts(const MatrixCoordinates & mouse);
};


#endif //BENESM41_FANTHILL_H
