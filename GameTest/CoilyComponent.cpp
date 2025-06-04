#include "CoilyComponent.h"

CoilyComponent::CoilyComponent(dae::GameObject& owner)
    : Component(owner)
{
}

CoilyComponent::~CoilyComponent()
{

}

void CoilyComponent::Update()
{
    if (m_pCurrentState)
        m_pCurrentState->Update(*this);
}
void CoilyComponent::Render() const
{
   
}

void CoilyComponent::SetState(std::unique_ptr<CoilyState> newState)
{
    if (m_pCurrentState)
        m_pCurrentState->Exit(*this);

    m_pCurrentState = std::move(newState);

    if (m_pCurrentState)
        m_pCurrentState->Enter(*this);
}

void CoilyComponent::MoveBy(const glm::vec3& offset)
{
    //random workaround
    offset;
}

void CoilyComponent::SetPosition(const glm::vec3& pos)
{
    //same here
    pos;
}

glm::vec3 CoilyComponent::GetPosition() const
{
    return GetOwner()->GetWorldPosition();
}
void CoilyComponent::SetCurrentTile(std::shared_ptr<TileComponent> tile)
{
    m_CurrentTile = std::move(tile);

    if (m_CurrentTile)
    {
        const auto& pos = m_CurrentTile->GetOwner()->GetTransform().GetPosition();
        m_pOwner->SetPosition(pos.x, pos.y);
    }
}
void CoilyComponent::SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap)
{
    m_pTileMap = &tileMap;
}
