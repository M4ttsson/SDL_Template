cmake_minimum_required(VERSION 3.29)
project(SDL_Template)

set(CMAKE_CXX_STANDARD 20)

# Create an option to switch between a system sdl library and a vendored sdl library
option(SDL_VENDORED "Use vendored libraries" OFF)

if(SDL_VENDORED)
    add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

    # 1. Look for a SDL2 package, 2. Look for the SDL2 maincomponent and 3. DO NOT fail when SDL2main is not available
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

    # Add sdl image
    find_package(SDL2_image REQUIRED)

endif()



add_executable(SDL_Template
        src/main.cpp
        src/game.cpp
        src/game.h
        src/components/SpriteComponent.h
        src/components/TransformComponent.h
        src/components/KeyInputComponent.h
        src/systems/SpriteSystem.h
        src/systems/SpriteSystem.cpp
        src/systems/TransformSystem.cpp
        src/systems/TransformSystem.h
        src/systems/MovementSystem.cpp
        src/systems/MovementSystem.h
)


# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

find_package(EnTT)


# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image EnTT::EnTT)


target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
)

# copy assets
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)