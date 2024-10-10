#pragma once
#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <entt/entity/registry.hpp>

#include "Constants.h"
#include "systems/MovementSystem.h"
#include "systems/SpriteSystem.h"
#include "systems/TransformSystem.h"

struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;

class Game {
public:
    Game(int width, int height);
    ~Game();

    [[nodiscard]] bool IsRunning() const { return m_isRunning; }

    void ReadInput();
    void Update();
    void Render();

    entt::registry& GetRegistry();
    SDL_Renderer* GetRenderer() const { return m_renderer; }

    SDL_Texture* LoadTexture(const char* path, textures::TextureId textureId);

private:
    int m_width, m_height;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_isRunning = true;

    std::unordered_map<textures::TextureId,SDL_Texture*> m_textures;

    entt::registry m_registry;

    SpriteSystem m_spriteSystem;
    TransformSystem m_transformSystem;
    MovementSystem m_movementSystem;
};

#endif //GAME_H
