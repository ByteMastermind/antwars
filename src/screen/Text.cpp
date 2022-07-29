//
// Created by michal on 26.5.22.
//

#include "Text.h"

void Text::initText(const std::string & text, SDL_Renderer * renderer) {
    if (m_text == text)
        return;
    m_text = text;
    m_renderer = renderer;

    // Destroying old texture (will do nothing if there is no texture)
    SDL_DestroyTexture(m_texture);

    SDL_Surface * textSurface;
    SDL_Color color = {255, 255, 255};
    TTF_Font * font = TTF_OpenFont("assets/font/basic_regular_400.ttf", 120);
    if (!font)
        throw std::invalid_argument("Failed to load the text font.");

    textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (!textSurface)
        throw std::runtime_error("Failed to render text.");

    // Creating texture
    SDL_Texture * textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

    if (textTexture == nullptr)
        throw std::runtime_error("Failed to created texture from surface.");

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    m_texture = textTexture;
}

Text::~Text() {
//    SDL_DestroyTexture(m_texture);
}

void Text::renderText(const int x, const int y, const int w, const int h) const {
    SDL_Rect r = {x, y, w, h};
    SDL_RenderCopy(m_renderer,m_texture,nullptr ,&r);
}
