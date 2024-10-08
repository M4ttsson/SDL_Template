
#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL_rect.h>

struct SDL_Texture;

struct SpriteComponent {
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Texture* texture;
};

#endif //SPRITE_COMPONENT_H
