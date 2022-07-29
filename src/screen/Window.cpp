//
// Created by michal on 16.4.22.
//

#include "Window.h"

Window::Window() : m_window(nullptr), m_renderer(nullptr), m_background(nullptr) {
    // Creating window
    m_window = SDL_CreateWindow(screenConstants::WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              screenConstants::SCREEN_WIDTH, screenConstants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Catching problems
    if (m_window == nullptr)
        throw std::runtime_error(std::string("The window could not be created! SDL_Error: ") + SDL_GetError());

    // Creating the renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == nullptr)
        throw std::runtime_error("Renderer could not be created.");

    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    loadBackground("assets/background_sand.bmp");
}

void Window::loadBackground(const std::string & filePath) {
    SDL_Surface * newSurface = SDL_LoadBMP(filePath.c_str());

    if (newSurface == nullptr)
        throw std::runtime_error(std::string("Unable to load image! SDL_Error: ") + SDL_GetError());

    // Creating texture
    m_background = SDL_CreateTextureFromSurface(m_renderer, newSurface);

    if (m_background == nullptr)
        throw std::runtime_error("Unable to create texture from surface.");

    SDL_FreeSurface(newSurface);
}

void Window::updateBackground() const {
    SDL_RenderClear(m_renderer);

    SDL_Rect r = {0, 0, screenConstants::SCREEN_WIDTH, screenConstants::SCREEN_HEIGHT};
    SDL_RenderCopy(m_renderer, m_background, nullptr, &r);
}

Window::~Window() {
    SDL_DestroyTexture(m_background);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Window::updateRenderer() const {
    if (m_renderer == nullptr)
        throw std::runtime_error("No renderer has been initiated yet!");

    SDL_RenderPresent(m_renderer);
}

SDL_Renderer * Window::getRenderer() const {
    return m_renderer;
}
