#pragma once
#include "Command.h"
#include "GameObject.h"
#include "Observer.h"
#include <SoundService.h>

namespace dae
{
    class HitCommand final : public Command
    {
    public:
        HitCommand(GameObject* attacker, GameObject* target)
            : m_pAttacker(attacker), m_pTarget(target) {
        }

        void Execute() override
        {
            if (m_pAttacker && m_pTarget)
            {
                // Play damage sound
                auto soundService = dae::ServiceLocator::GetSoundService();
                if (soundService)
                {
                    soundService->PlaySound("../Data/sound/damage.wav"); 
                    std::cout << "playing sound " << std::endl;
                }

                //notify target
                m_pTarget->NotifyObservers(Event::PlayerDie);

                //notify attacker
                m_pAttacker->NotifyObservers(Event::PlayerDidDamage);
            }
        }

    private:
        GameObject* m_pAttacker; //Player giving hit
        GameObject* m_pTarget; //Player receiving hit  
    };
}
