#include "HealthComponent.h"
#include "GameObject.h"

namespace dae
{
    HealthComponent::HealthComponent(GameObject& owner, int maxHealth)
        : Component(owner), m_MaxHealth(maxHealth), m_Health(maxHealth)
    {
    }

    HealthComponent::~HealthComponent() = default;

    void HealthComponent::TakeDamage(int damage)
    {
        if (m_Health > 0)
        {
            m_Health -= damage;

            m_pOwner->NotifyObservers(Event::PlayerTookDamage);
        }
        if (m_Health <= 0)
        {
            m_Health = 0;

            m_pOwner->NotifyObservers(Event::PlayerDie);
        }
    }

    bool HealthComponent::IsDead() const
    {
        return m_Health == 0;
    }

    int HealthComponent::GetHealth() const
    {
        return m_Health;
    }
}
