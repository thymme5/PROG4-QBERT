#pragma once
#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"

//I had no other inspiration on how to do it otherwise
namespace dae
{
    class StopMovingCommand : public Command
    {
    public:
        StopMovingCommand(GameObject* pGameObject) :
            Command(),
            m_pGameObject{ pGameObject }
        {

        }
        void Execute() override
        {
            m_pGameObject->GetComponent<MoveComponent>()->SetMovementState(MovementState::Idle);
        }
    private:
        GameObject* m_pGameObject;
    };
}
