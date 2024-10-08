
#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H

#include <entt/entity/registry.hpp>

struct SDL_Renderer;

class SpriteSystem
{
public:
    void Update(entt::registry &reg);
    void Render(entt::registry &reg, SDL_Renderer *renderer);

};

#endif //SPRITESYSTEM_H
