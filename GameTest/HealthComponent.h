#pragma once

#include "Component.h"
#include "GameObject.h"

namespace dae
{
    class HealthComponent final : public Component
    {
    public:
        HealthComponent(GameObject& owner, int maxHealth);
        virtual ~HealthComponent() override;

        void TakeDamage(int damage);
        bool IsDead() const;
        int GetHealth() const;
    private:
        int m_Health;
        int m_MaxHealth;
    };
}
