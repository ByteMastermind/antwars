//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_ANT_H
#define BENESM41_ANT_H

#include "Character.h"
#include "Usings.h"

/**
 * Class of a single ant
 */
class Ant : public Character {
public:
    Ant(int x, int y);
    void progress(const MatrixCoordinates & mouse) override;
    void initCharacter(SDL_Renderer * renderer) override;
    [[nodiscard]] std::string getType() const override;
    bool setTarget(std::shared_ptr<Character> anthill, std::shared_ptr<Path> path) override;
    [[nodiscard]] std::shared_ptr<Character> getTarget() const override;
    void goHome() override;

    /**
     * Sets parent anthill of this ant
     * @param parent is the shared pointer to the parent
     */
    void setParent(std::shared_ptr<Character> parent);

private:
    size_t m_distance;                                  /*!< Basically the index in the path vector of coordinates */
    bool m_invertedPath;                                /*!< If it is inverted, m_distance decreases with each iteration */
    std::weak_ptr<Character> m_parent;                  /*!< A weak pointer to the parent anthill */
};


#endif //BENESM41_ANT_H
