#include <iostream>

#include "GameUIComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

using namespace dae;

GameUIComponent::GameUIComponent(GameObject& owner, int startingLives, int startingScore)
    : Component(owner), m_Lives(startingLives), m_Score(startingScore)
{

}

void GameUIComponent::OnNotify(Event event, GameObject* pGameObject)
{
    //temp value to stop compiler from bitching
    GameObject* gameObject = pGameObject;
    gameObject;

    switch (event)
    {
    case dae::Event::PlayerDie:
        UpdateLives();
        break;
    case dae::Event::PlayerTookDamage:
        UpdateLives();
        break;
    case dae::Event::PlayerDidDamage:
        break;
    case dae::Event::PlayerPickUpPellets10:
        m_Score += 10;
        break;
    case dae::Event::PlayerPickUpPellets100:
        m_Score += 100;
        break;
    default:
        break;
    }

}

void GameUIComponent::UpdateLives()
{
    if (m_Lives > 0)
    {
        m_Lives--;
    }
}

void GameUIComponent::UpdateScore(int newScore)
{
    m_Score = newScore;
}

void GameUIComponent::Update() 
{
    std::string text{ "# Lives: " + std::to_string(m_Lives) + "\n" + "Score " + std::to_string(m_Score) };
    m_pOwner->GetComponent<TextComponent>()->SetText(text);
}

void GameUIComponent::Render() const
{

}
