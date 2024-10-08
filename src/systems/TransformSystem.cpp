
#include "TransformSystem.h"

#include "../components/TransformComponent.h"

void TransformSystem::Update(entt::registry &reg)
{
    const auto view = reg.view<TransformComponent>();
    view.each([&](auto &t) {
       t.pos_x += t.vel_x * dt;
       t.pos_y += t.vel_y * dt;
    });
}
