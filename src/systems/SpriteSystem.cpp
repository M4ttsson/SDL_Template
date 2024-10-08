#include "SpriteSystem.h"

#include <SDL_render.h>
#include <entt/entity/registry.hpp>

#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"

void SpriteSystem::Update(entt::registry &reg)
{
    const auto view = reg.view<SpriteComponent, TransformComponent>();

    view.each([](auto &s, auto &t){
    s.dst.x = t.pos_x;
    s.dst.y = t.pos_y;
});
}

void SpriteSystem::Render(entt::registry &reg, SDL_Renderer *renderer)
{
    const auto view = reg.view<SpriteComponent>();

    view.each([renderer](auto &s) {
        SDL_RenderCopy(
                        renderer,
                        s.texture,
                        &s.src,
                        &s.dst
                        );
    });
}


