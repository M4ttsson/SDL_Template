#pragma once
#ifndef GAME_H
#define GAME_H

#include <cassert>
#include <SDL2/SDL.h>
#include <any>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct SDL_Texture;

// an alias to make it more expressive
using entity = std::size_t;
// we need the maximum count, this isn't the best solution, but it does the job for now
inline entity max_entity = 0;
// and here we create some unique ID's
inline std::size_t create_entity()
{
    static std::size_t entities = 0;
    ++entities;
    max_entity = entities;
    return entities;
}

// a sdl rect holds width, height, x and y
// a sprite takes a source  rectangle
// and places it to the given destination on the screen
struct sprite_component {
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Texture* texture;
};

// a position and a velocity represented as transform
struct transform_component {
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
};

// we'll only create a type for keyinputs, we get the pressed keys later
struct keyinputs_component {};

struct registry {
    std::unordered_map<entity, sprite_component> sprites;
    std::unordered_map<entity, transform_component> transforms;
    std::unordered_map<entity, keyinputs_component> keys;
};
struct sprite_system
{
    void update(registry& reg)
    {
        for (int e = 1 ; e <= max_entity ; e++) {
            if (reg.sprites.contains(e) && reg.transforms.contains(e)){
                reg.sprites[e].dst.x = reg.transforms[e].pos_x;
                reg.sprites[e].dst.y = reg.transforms[e].pos_y;
            }
        }
    }
    void render(registry& reg, SDL_Renderer* renderer)
    {
        for (int e = 1 ; e <= max_entity ; e++) {
            if (reg.sprites.contains(e)){
                SDL_RenderCopy(
                    renderer,
                    reg.sprites[e].texture,
                    &reg.sprites[e].src,
                    &reg.sprites[e].dst
                );
            }
        }
    }
};

struct transform_system
{
    float dt = 0.1f;

    void update(registry& reg)
    {
        for (int e = 1 ; e <= max_entity ; e++) {
            if (reg.transforms.contains(e)){
                reg.transforms[e].pos_x += reg.transforms[e].vel_x*dt;
                reg.transforms[e].pos_y += reg.transforms[e].vel_y*dt;
            }
        }
    }
};

struct movement_system
{
    void update(registry& reg)
    {
        // TODO: pollevents eller inte??
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        for (int e = 1 ; e <= max_entity ; e++) {
            if (reg.transforms.contains(e) && reg.keys.contains(e)){

                if (keys[SDL_SCANCODE_A]) { reg.transforms[e].vel_x = -5.0f; }
                if (keys[SDL_SCANCODE_S]) { reg.transforms[e].vel_y = 5.0f; }
                if (keys[SDL_SCANCODE_W]) { reg.transforms[e].vel_y = -5.0f; }
                if (keys[SDL_SCANCODE_D]) { reg.transforms[e].vel_x = 5.0f; }

                if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) { reg.transforms[e].vel_x = 0.0f; }
                if (!keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) { reg.transforms[e].vel_y = 0.0f; }
            }
        }
    }
};












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

    registry& get_registry() { return m_registry; }
    SDL_Renderer* get_renderer() { return m_renderer; }

private:
    int m_width, m_height;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_isRunning = true;


    registry m_registry;

    sprite_system m_sprite_system;
    transform_system m_transform_system;
    movement_system m_movement_system;
};



#endif //GAME_H
