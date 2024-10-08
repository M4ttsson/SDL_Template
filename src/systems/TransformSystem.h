
#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

#include <entt/entity/registry.hpp>


class TransformSystem {

public:
    const float dt = 0.1f;
    void Update(entt::registry& reg);
};

#endif //TRANSFORMSYSTEM_H
