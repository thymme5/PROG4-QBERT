#pragma once
#include "Component.h"
#include "TileComponent.h"

#include <glm.hpp>
#include <memory>
#include <vector>

enum class Direction
{
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

struct JumpData
{
    glm::vec2 startPos;
    glm::vec2 endPos;
    float elapsed = 0.f;
    float duration = 0.3f;
    bool isJumping = false;
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
        const float m_xOffset = 15.f;
        const float m_yOffset = -19.f;
        
        JumpData m_Jump;
    };
}
