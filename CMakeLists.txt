cmake_minimum_required(VERSION 3.29)
project(SDL_Template)

set(CMAKE_CXX_STANDARD 20)

add_executable(SDL_Template
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/components/SpriteComponent.h
        src/components/TransformComponent.h
        src/components/KeyInputComponent.h
        src/systems/SpriteSystem.h
        src/systems/SpriteSystem.cpp
        src/systems/TransformSystem.cpp
        src/systems/TransformSystem.h
        src/systems/MovementSystem.cpp
        src/systems/MovementSystem.h
        src/Constants.h
)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
#if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
#endif()

find_package(EnTT REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)


target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image EnTT::EnTT)

target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
)

# copy assets
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)