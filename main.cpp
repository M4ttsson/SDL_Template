#include <iostream>
#include <SDL2/SDL_image.h>
#include <entt/entt.hpp>

#include "game.h"
#include "constants.h"

// TODO: Consider installing SDL2 with conan

int main() {
    std::cout << "Hello, World!" << std::endl;



    Game game(800, 600);

    auto dog = game.GetRegistry().create();

    game.GetRegistry().emplace<sprite_component>(dog,
        SDL_Rect(0,0,616, 622),
        SDL_Rect(10,10,116, 122),
        IMG_LoadTexture(game.get_renderer(), DOG_PATH) // TODO: make cmake dynamic somehow
        );

    game.GetRegistry().emplace<transform_component>(dog, 10.0f, 10.0f, 0.0f, 0.0f);
    game.GetRegistry().emplace<keyinputs_component>(dog);

    while (game.IsRunning())
    {
        game.ReadInput();
        game.Update();
        game.Render();
    }

    return 0;
}
