//
// Created by michal on 25.5.22.
//

#include "Object.h"

void Object::initObject(const std::string & filePath, SDL_Renderer * renderer) {
    m_renderer = renderer;
    SDL_Surface * newSurface = SDL_LoadBMP(filePath.c_str());

    if (newSurface == nullptr)
        throw std::runtime_error(std::string("Unable to load image! SDL_Error: ") + SDL_GetError());

    // Creating texture
    SDL_Texture * newTexture = SDL_CreateTextureFromSurface(m_renderer, newSurface);

    if (newTexture == nullptr)
        throw std::runtime_error("Failed to created texture from surface.");

    SDL_FreeSurface(newSurface);
    m_texture = newTexture;
}

void Object::changeObject(const int x, const int y, const int w, const int h, const double angle) const {
    SDL_Rect r = {x, y, w, h};
    SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &r, angle, nullptr, SDL_FLIP_NONE);
}

Object::~Object() {
//    SDL_DestroyTexture(m_texture);
}
