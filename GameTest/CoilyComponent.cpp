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
    constexpr float fixedDeltaTime = 1.f / 60.f;
    
    if (m_Jump.isJumping)
    {
        m_Jump.elapsed += fixedDeltaTime;
        if (m_Jump.elapsed >= m_Jump.duration)
        {
            m_Jump.isJumping = false;
        }
    }

    if (!m_Jump.isJumping && m_pCurrentState)
    {
        m_pCurrentState->Update(*this);
    }
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
void CoilyComponent::TryMove(Direction direction)
{
    if (!m_CurrentTile || !m_pTileMap) return;

    auto [row, col] = m_CurrentTile->GetGridPosition();
    int newRow = row;
    int newCol = col;

    switch (direction)
    {
        case Direction::UpLeft:    newRow -= 1; newCol -= 1; break;
        case Direction::UpRight:   newRow -= 1; break;
        case Direction::DownLeft:  newRow += 1; break;
        case Direction::DownRight: newRow += 1; newCol += 1; break;
    }

    if (newRow < 0 || newRow >= static_cast<int>(m_pTileMap->size())) return;
    if (newCol < 0 || newCol >= static_cast<int>((*m_pTileMap)[newRow].size())) return;

    auto targetTile = (*m_pTileMap)[newRow][newCol];
    if (!targetTile) return;

    m_CurrentTile = targetTile;

    //move instantly for now — animation later
    const auto& pos = targetTile->GetOwner()->GetTransform().GetPosition();
    m_pOwner->SetPosition(pos.x + m_xOffset, pos.y + m_yOffset);

    m_Jump.elapsed = 0.f;
    m_Jump.isJumping = true;
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
        m_pOwner->SetPosition(pos.x + m_xOffset, pos.y + m_yOffset);
    }
}
void CoilyComponent::SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap)
{
    m_pTileMap = &tileMap;
}

std::shared_ptr<TileComponent> CoilyComponent::GetQbertTile()
{
    if (!m_pQbert) return nullptr;

    auto move = m_pQbert->GetComponent<QbertMoveComponent>();
    if (!move) return nullptr;

    return move->GetCurrentTile();
}
std::shared_ptr<TileComponent> CoilyComponent::GetCoilyTile()
{
    return m_CurrentTile;
}
void CoilyComponent::SetQbert(std::shared_ptr<dae::GameObject> qbert)
{ 
    m_pQbert = std::move(qbert); 
}

bool CoilyComponent::IsJumping() const
{
    return m_Jump.isJumping;
}