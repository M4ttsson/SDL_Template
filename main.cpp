#include <iostream>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "constants.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Game game(800, 600);

    entity dog = create_entity();

    game.get_registry().sprites[dog] = sprite_component{
        SDL_Rect(0,0,616, 622),
        SDL_Rect(10,10,116, 122),

        IMG_LoadTexture(game.get_renderer(), DOG_PATH) // TODO: make cmake dynamic somehow
    };

    // a transform component
    game.get_registry().transforms[dog] = transform_component{10, 10, 0, 0};
    // and we add key inputs
    game.get_registry().keys[dog] = keyinputs_component { };

    while (game.IsRunning())
    {
        game.ReadInput();
        game.Update();
        game.Render();
    }

    return 0;
}
