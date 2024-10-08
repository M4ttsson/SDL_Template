
#include "MovementSystem.h"

#include <SDL_keyboard.h>

#include "../components/KeyInputComponent.h"
#include "../components/TransformComponent.h"


void MovementSystem::Update(entt::registry &reg)
{
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);

    const auto view = reg.view<TransformComponent, KeyInputComponent>();

    view.each([&keys](auto &t) {
        if (keys[SDL_SCANCODE_A]) { t.vel_x = -t.speed; }
        if (keys[SDL_SCANCODE_S]) { t.vel_y = t.speed; }
        if (keys[SDL_SCANCODE_W]) { t.vel_y = -t.speed; }
        if (keys[SDL_SCANCODE_D]) { t.vel_x = t.speed; }
        if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) { t.vel_x = 0.0f; }
        if (!keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) { t.vel_y = 0.0f; }
    });
}
