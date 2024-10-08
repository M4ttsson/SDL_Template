#include <iostream>
#include <SDL2/SDL_image.h>
#include <entt/entt.hpp>

#include "game.h"
#include "constants.h"
#include "components/KeyInputComponent.h"
#include "components/SpriteComponent.h"
#include "components/TransformComponent.h"

// TODO: Consider installing SDL2 with conan

int main() {
    std::cout << "Hello, World!" << std::endl;



    Game game(800, 600);

    auto dog = game.GetRegistry().create();

    game.GetRegistry().emplace<SpriteComponent>(dog,
        SDL_Rect(0,0,616, 622),
        SDL_Rect(10,10,116, 122),

        game.LoadTexture (DOG_PATH, textures::TextureId::Dog)
        );

    game.GetRegistry().emplace<TransformComponent>(dog, 10.0f, 10.0f, 0.0f, 0.0f, 10.0f);
    game.GetRegistry().emplace<KeyInputComponent>(dog);

    while (game.IsRunning())
    {
        game.ReadInput();
        game.Update();
        game.Render();
    }

    return 0;
}
