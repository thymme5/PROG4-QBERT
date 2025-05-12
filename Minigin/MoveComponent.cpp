#include "MoveComponent.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
    MoveComponent::MoveComponent(GameObject& pOwner, float speed)
        : Component(pOwner), m_Speed(speed), m_State(MovementState::Idle), m_Direction(glm::vec3(0, 0, 0))
    {
    }
  
    void MoveComponent::Update()
    {
        if (m_State == MovementState::Idle)
            return;

        // Calculate movement based on direction and speed
        glm::vec3 movement = m_Direction * m_Speed;

        // Update position
        const auto& position = m_pOwner->GetTransform().GetPosition();
        m_pOwner->SetPosition(position.x + movement.x, position.y + movement.y);

    }

    void MoveComponent::SetMovementState(MovementState state)
    {
        m_State = state;

        // Set movement direction based on the current state
        switch (state)
        {
        case MovementState::MovingUp:
            m_Direction = glm::vec3(0, -1, 0);
            break;
        case MovementState::MovingDown:
            m_Direction = glm::vec3(0, 1, 0);
            break;
        case MovementState::MovingLeft:
            m_Direction = glm::vec3(-1, 0, 0);
            break;
        case MovementState::MovingRight:
            m_Direction = glm::vec3(1, 0, 0);
            break;
        default:
            m_Direction = glm::vec3(0, 0, 0);
            break;
        }
    }
    void MoveComponent::Render() const
    {

    }
}
