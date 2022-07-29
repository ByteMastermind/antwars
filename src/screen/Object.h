//
// Created by michal on 25.5.22.
//

#ifndef BENESM41_OBJECT_H
#define BENESM41_OBJECT_H

#include <SDL2/SDL.h>

#include <string>
#include <stdexcept>
#include <memory>
#include <utility>

class Object {
public:
    Object() = default;
    ~Object();

    /**
     * Initialize the object, creates the texture, sets the renderer
     * @param filePath is the path to the texture file
     * @param renderer is the already initialized renderer
     */
    void initObject(const std::string & filePath, SDL_Renderer * renderer);

    /**
     * Renders the current state of the texture
     * @param x is the X coordinate
     * @param y is the Y coordinate
     * @param w is the texture width
     * @param h is the texture height
     * @param angle is the angle of the texture (rotation)
     */
    void changeObject(int x, int y, int w, int h, double angle) const;

private:
    SDL_Texture * m_texture = nullptr;                          /*!< The texture of the object */
    SDL_Renderer * m_renderer = nullptr;                        /*!< The already initialized renderer */
};


#endif //BENESM41_OBJECT_H
