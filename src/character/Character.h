//
// Created by michal on 7.5.22.
//

#ifndef BENESM41_CHARACTER_H
#define BENESM41_CHARACTER_H

#include <iostream>
#include <memory>
#include <utility>
#include <string>

#include "characterConstants.h"
#include "screenConstants.h"
#include "Window.h"
#include "Object.h"
#include "Text.h"
#include "MatrixCoordinates.h"
#include "Usings.h"

/**
 * Base abstract class over all characters in the game (ants, anthills, obstacles)
 */
class Character {
public:
    /**
     * Construct a character with coordinates
     * @param x coordinate
     * @param y coordinate
     */
    Character(int x, int y);

    /**
     * Loads renderer, gives the objects textures
     * @param renderer is the already initiated renderer
     */
    virtual void initCharacter(SDL_Renderer * renderer) = 0;

    /**
     * @return X coordinate of the character
     */
    [[nodiscard]] int getX() const;

    /**
     * @return Y coordinate of the character
     */
    [[nodiscard]] int getY() const;

    /**
     * @return the angle of the character
     */
    [[maybe_unused]] [[nodiscard]] double getAngle() const;

    /**
     * What the character do, changes etc. every frame
     * @param mouse is the current mouse coordinates (which block is the mouse over)
     */
    virtual void progress(const MatrixCoordinates & mouse) = 0;

    /**
     * @return true if character is selected (Works only with selectable characters)
     */
    [[nodiscard]] virtual bool isSelected() const;

    /**
     * Sets current selectable character to the value that is passed
     * @param selected
     * @return true if character is selectable, otherwise false
     */
    virtual bool setSelected(bool selected);

    /**
     * Sets target anthill and a path to it for *this
     * @param anthill is the target anthill
     * @param path is the path from *this to the target
     * @return true if success
     */
    virtual bool setTarget(std::shared_ptr<Character> anthill, std::shared_ptr<Path> path);

    /**
     * Get type of the object
     * @return string with the name of the object ("ant", "fanthill", "eanthill", "obstacle")
     */
    [[nodiscard]] virtual std::string getType() const = 0;

    /**
     * @return the character target pointer
     */
    [[nodiscard]] virtual std::shared_ptr<Character> getTarget() const;

    /**
     * @return the amount of ants in the anthill
     */
    [[nodiscard]] virtual size_t getAntCount() const;

    /**
     * Increases the amount of the ants in the anthill by 1
     */
    virtual void increaseAntCount();

    /**
     * Decreases the amount of the ants in the anthill by 1
     */
    virtual void decreaseAntCount();

    /**
     * Used to invert path and set target of an ant to his parent anthill to return back
     */
    virtual void goHome();

    /**
     * @return the vector with all the ants of the way that came from this anthill
     */
    virtual std::vector<std::shared_ptr<Character>> & getAnts();

    /**
     * Return string with the info about current state of the anthill (for saving the game)
     * @return string with everything
     */
    [[nodiscard]] virtual std::string printInfo() const;

protected:
    int m_x;                                            /*!< X coordinate */
    int m_y;                                            /*!< Y coordinate */
    double m_angle = 0;                                 /*!< Angle of the rotation */
    Object m_object;                                    /*!< Object holds the texture, renders the texture each frame */
    SDL_Renderer * m_renderer;                          /*!< Already initiated renderer */
    std::weak_ptr<Character> m_target;                  /*!< Pointer to the enemy or friendly anthill, where the army will head */
    std::shared_ptr<Path> m_path;                       /*!< Pointer to the path, that is leads from one anthill to another */
    std::vector<std::shared_ptr<Character>> m_ants;     /*!< Vector with all the ants on the way */

    /**
     * Loads the already initiated renderer
     * @param renderer
     */
    void loadRenderer(SDL_Renderer * renderer);
};


#endif //BENESM41_CHARACTER_H
