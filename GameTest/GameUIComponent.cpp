#include <iostream>

#include "GameUIComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

using namespace dae;

GameUIComponent::GameUIComponent(GameObject& owner)
    : Component(owner), m_Lives( 3), m_Score( 0 )
{

}

void GameUIComponent::OnNotify(Event event, GameObject* pGameObject)
{
    //temp value to stop compiler from bitching
    GameObject* gameObject = pGameObject;
    gameObject;

    switch (event)
    {
    case dae::Event::PlayerDied:
        break;
    case dae::Event::PlayerLandedOnTile:
        break;
    case dae::Event::TileStateChanged:
        m_Score += 25;
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
    std::string text{ "SCORE: " + std::to_string(m_Score) };
    m_pOwner->GetComponent<TextComponent>()->SetText(text);
}

void GameUIComponent::Render() const
{

}
