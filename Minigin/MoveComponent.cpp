#include "MoveComponent.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
    MoveComponent::MoveComponent(GameObject& pOwner)
        : Component(pOwner)
    {
    }

    void MoveComponent::Update()
    {
    }

    void MoveComponent::Render() const
    {
    }

    void MoveComponent::SetCurrentTile(std::shared_ptr<TileComponent> tile)
    {
        m_CurrentTile = std::move(tile);

        if (m_CurrentTile)
        {
            const auto& pos = m_CurrentTile->GetOwner()->GetTransform().GetPosition();
            m_pOwner->SetPosition(pos.x, pos.y);
        }
    }

    void MoveComponent::SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap)
    {
        m_pTileMap = &tileMap;
    }

    void MoveComponent::TryMove(Direction dir)
    {
        if (!m_CurrentTile || !m_pTileMap)
            return;

        auto [row, col] = m_CurrentTile->GetGridPosition();

        // Adjust row/col based on direction
        switch (dir)
        {
        case Direction::UpLeft:
            row -= 1; col -= 1;
            break;
        case Direction::UpRight:
            row -= 1;
            break;
        case Direction::DownLeft:
            row += 1;
            break;
        case Direction::DownRight:
            row += 1; col += 1;
            break;
        }

        // Validate bounds
        if (row < 0 || row >= static_cast<int>(m_pTileMap->size()) || col < 0 || col > row)
        {
            // Fell off
            std::cout << "Q*bert fell off!\n";
            return;
        }

        auto nextTile = (*m_pTileMap)[row][col];
        m_CurrentTile = nextTile;

        const auto& targetPos = nextTile->GetOwner()->GetTransform().GetPosition();
        m_pOwner->SetPosition(targetPos.x, targetPos.y);

        nextTile->OnStepped();
    }
}
