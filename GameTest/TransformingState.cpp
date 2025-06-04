#include "TransformingState.h"
#include "CoilyComponent.h"
#include "TextureComponent.h"

#include "ChasingState.h"
#include <memory>

void TransformingState::Enter(CoilyComponent& coily)
{
    // Set Coily's sprite to snake form (just a placeholder for now)
    auto* texture = coily.GetOwner()->GetComponent<dae::TextureComponent>();
    if (texture)
        texture->SetTexture("testing/coily_snake_test_character.png");
 
    m_AccumulatedTime = 0.0f;
}

void TransformingState::Update(CoilyComponent& coily)
{
    m_AccumulatedTime += 1.0f / 60.0f; //Fixed timesteps

    if (m_AccumulatedTime >= 1.0f) //After 1 second
    {
        coily.SetState(std::make_unique<ChasingState>());
        coily;
    }
}

void TransformingState::Exit(CoilyComponent&)
{
    
}
