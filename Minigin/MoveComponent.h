#pragma once
#include <glm.hpp>

#include "Component.h"

namespace dae
{
    enum class MovementState
    {
        Idle,
        MovingUp,
        MovingDown,
        MovingLeft,
        MovingRight
    };

    class MoveComponent : public Component
    {    public:
        MoveComponent(GameObject& pOwner, float speed = 0.0f);
        virtual ~MoveComponent() override = default;

        MoveComponent(const MoveComponent& other) = delete;
        MoveComponent& operator=(const MoveComponent& other) = delete;
        MoveComponent(MoveComponent&& other) = delete;
        MoveComponent& operator=(MoveComponent&& other) = delete;

        void Update() override;
        void Render() const override;

        void SetMovementState(MovementState state);

    private:
        float m_Speed;                 
        MovementState m_State;         
        glm::vec3 m_Direction;
    };
}
