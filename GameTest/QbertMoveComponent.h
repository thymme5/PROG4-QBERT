#pragma once
#include "Component.h"
#include "TileComponent.h"

#include <memory>
#include <vector>

enum class Direction
{
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

namespace dae
{
    class QbertMoveComponent : public Component
    {
    public:
        QbertMoveComponent(GameObject& pOwner);
        void Update() override;
        void Render() const override;

        void SetCurrentTile(std::shared_ptr<TileComponent> tile);
        void SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap);

        void TryMove(Direction dir);

    private:
        std::shared_ptr<TileComponent> m_CurrentTile;
        const std::vector<std::vector<std::shared_ptr<TileComponent>>>* m_pTileMap = nullptr;
    };
}
