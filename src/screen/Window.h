//
// Created by michal on 16.4.22.
//

#ifndef BENESM41_WINDOW_H
#define BENESM41_WINDOW_H

#include <SDL2/SDL.h>

#include <stdexcept>
#include <vector>
#include <map>
#include <stack>

#include "screenConstants.h"

class Window {
public:
    Window();
    ~Window();

    /**
     * Loads the background texture
     * @param filePath is the path to the texture file
     */
    void loadBackground(const std::string & filePath);

    /**
     * Updates the renderer - needs to be done every frame, after every texture was rendered
     */
    void updateRenderer() const;

    /**
     * Resets renderer and renders the background - needs to be done at the beginning of every frame
     */
    void updateBackground() const;

    /**
     * @return the renderer
     */
    [[nodiscard]] SDL_Renderer * getRenderer() const;

private:
    SDL_Window * m_window;                                /*!< Window to render in */
    SDL_Renderer * m_renderer;                            /*!< Renderer */
    SDL_Texture * m_background;                           /*!< The background texture */
};

#endif //BENESM41_WINDOW_H
