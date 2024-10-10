
#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>

Game::Game(const int width, const int height)
{
    m_width = width;
    m_height = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    constexpr int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("Failed to img init: %s\n", SDL_GetError());
        exit(1);
    }

    constexpr int windowFlags = 0;
    m_window = SDL_CreateWindow("SDL Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, windowFlags);

    if (!m_window)
    {
        printf("Failed to open %d x %d window: %s\n", m_width, m_height, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    constexpr int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);

    if (!m_renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetRenderDrawColor(m_renderer, 96, 128, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);

}

Game::~Game()
{
    for (auto& [key, value]: m_textures)
    {
        SDL_DestroyTexture(value);
    }

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

entt::registry& Game::GetRegistry() {
    return m_registry;
}

SDL_Texture* Game::LoadTexture(const char *path, textures::TextureId textureId)
{
    SDL_Texture *texture = IMG_LoadTexture(m_renderer, path);
    if (!texture)
    {
        printf("Failed to load texture: %s\n", SDL_GetError());
        return nullptr;
    }

    m_textures.emplace(textureId, texture);
    return texture;
}

void Game::ReadInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // User requests quit
        if (event.type == SDL_QUIT)
        {
            m_isRunning = false;
        }
    }
}

void Game::Update()
{
    m_transformSystem.Update(m_registry);
    m_movementSystem.Update(m_registry);
    m_spriteSystem.Update(m_registry);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 96, 128, 255, 255);
    SDL_RenderClear(m_renderer);

    m_spriteSystem.Render(m_registry, m_renderer);

    SDL_RenderPresent(m_renderer);
}
