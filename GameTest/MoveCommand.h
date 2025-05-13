#pragma once
#include "Command.h"
#include "QbertMoveComponent.h"

namespace dae
{
    class MoveCommand : public Command
    {
    public:
        MoveCommand(GameObject* pGameObject, Direction dir)
            : m_pGameObject(pGameObject), m_Direction(dir) {
        }

        void Execute() override
        {
            if (m_pGameObject->HasComponent<QbertMoveComponent>())
            {
                m_pGameObject->GetComponent<QbertMoveComponent>()->TryMove(m_Direction);
            }
        }

    private:
        GameObject* m_pGameObject{};
        Direction m_Direction{};
    };
}
