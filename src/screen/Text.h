//
// Created by michal on 26.5.22.
//

#ifndef BENESM41_TEXT_H
#define BENESM41_TEXT_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>


/**
 * Class that takes care of rendering text
 */
class Text {
public:
    Text() = default;
    ~Text();

    /**
     * Initialize the text, creates the texture, sets the renderer
     * @param text is the text to render
     * @param renderer is the already initialized renderer
     */
    void initText(const std::string & text, SDL_Renderer * renderer);

    /**
     * Renders the current state of the texture
     * @param x is the X coordinate
     * @param y is the Y coordinate
     * @param w is the texture width
     * @param h is the texture height
     */
    void renderText(int x, int y, int w, int h) const;

private:
    SDL_Texture * m_texture = nullptr;                          /*!< The texture of the object */
    SDL_Renderer * m_renderer = nullptr;                        /*!< The already initialized renderer */
    std::string m_text;                                         /*!< The text to render */
};


#endif //BENESM41_TEXT_H
