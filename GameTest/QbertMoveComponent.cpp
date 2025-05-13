#include "QbertMoveComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "LevelBuilder.h"

namespace dae
{
    QbertMoveComponent::QbertMoveComponent(GameObject& pOwner)
        : Component(pOwner)
    {
    }

    void QbertMoveComponent::Update()
    {
    }

    void QbertMoveComponent::Render() const
    {
    }

    void QbertMoveComponent::SetCurrentTile(std::shared_ptr<TileComponent> tile)
    {
        m_CurrentTile = std::move(tile);

        if (m_CurrentTile)
        {
            const auto& pos = m_CurrentTile->GetOwner()->GetTransform().GetPosition();
            m_pOwner->SetPosition(pos.x, pos.y);
        }
    }

    void QbertMoveComponent::SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap)
    {
        m_pTileMap = &tileMap;
    }

	void QbertMoveComponent::TryMove(Direction direction)
	{
		auto tileMap = LevelBuilder::GetTileMap();
		for (size_t r = 0; r < tileMap.size(); ++r)
		{
			std::cout << "Row " << r << " has " << tileMap[r].size() << " tiles\n";
		}

		if (!m_CurrentTile || !m_pTileMap) return;

		auto [row, col] = m_CurrentTile->GetGridPosition();
		int newRow = row;
		int newCol = col;

		switch (direction)
		{
		case Direction::UpLeft:
			newRow -= 1;
			newCol -= 1;
			break;
		case Direction::UpRight:
			newRow -= 1;
			// col stays same
			break;
		case Direction::DownLeft:
			newRow += 1;
			// col stays same
			break;
		case Direction::DownRight:
			newRow += 1;
			newCol += 1;
			break;
		}


		std::cout << "Trying move from (" << row << "," << col << ") to (" << newRow << "," << newCol << ")\n";

		// Check row bounds
		if (newRow < 0 || newRow >= static_cast<int>(m_pTileMap->size()))
		{
			std::cout << "Out of bounds row: " << newRow << "\n";
			return;
		}

		// Check col bounds
		if (newCol < 0 || newCol >= static_cast<int>((*m_pTileMap)[newRow].size()))
		{
			std::cout << "Out of bounds col: " << newCol << "\n";
			return;
		}

		auto targetTile = (*m_pTileMap)[newRow][newCol];
		if (!targetTile)
		{
			std::cout << "Null tile at position\n";
			return;
		}

		m_CurrentTile = targetTile;

		const auto& pos = m_CurrentTile->GetOwner()->GetTransform().GetPosition();
		m_pOwner->SetPosition(pos.x, pos.y);
	}

}
