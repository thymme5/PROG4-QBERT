#include "EggState.h"
#include "CoilyComponent.h"
#include "TransformingState.h"
#include "GameObject.h"

#include "TextureComponent.h"

void EggState::Enter(CoilyComponent& coily)
{
    // Set egg sprite
    auto* texture = coily.GetOwner()->GetComponent<dae::TextureComponent>();
    if (texture)
        texture->SetTexture("testing/coily_egg_test_character.png");

    //coily.SetPosition({ 256.f, 0.f });
}

void EggState::Update(CoilyComponent& coily)
{
    //move coily (inactive)
    //coily.MoveBy({ -50.0f * deltaTime, m_DropSpeed });

    //check if Coily reached bottom of pyramid
    if (coily.GetPosition().y >= 540.0f)
    {
        //coily.SetState(new TransformingState()); //next state
    }

    //For testing purposes, coily changes state after 2 seconds
    m_AccumulatedTime += 1.0f / 60.0f; //Fixed timesteps

    if (m_AccumulatedTime >= 2.0f)
    {
        coily.SetState(std::make_unique<TransformingState>());

    }

}

void EggState::Exit(CoilyComponent&)
{

}
