#pragma once
#include <memory>

#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"

namespace dae
{
    class MoveCommand : public Command
    {
    public:
        MoveCommand(GameObject* pGameObject, MovementState movementState, float speed)
            : m_pGameObject(pGameObject), m_MovementState(movementState), m_Speed(speed)
        {
            //if no MoveComponent exists, add one and set movement state
            if (!m_pGameObject->HasComponent<MoveComponent>())
            {
                m_pGameObject->AddComponent<MoveComponent>(*m_pGameObject, m_Speed);
            }
        }

        void Execute() override
        {
            if (m_pGameObject->HasComponent<MoveComponent>())
            {
                m_pGameObject->GetComponent<MoveComponent>()->SetMovementState(m_MovementState);
            }
        }

    private:
        GameObject* m_pGameObject;
        MovementState m_MovementState;
        float m_Speed;
    };
}
