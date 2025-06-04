#pragma once
#include "Component.h"
#include "CoilyState.h"
#include "GameObject.h"
#include "TileComponent.h"
#include "QbertMoveComponent.h"

struct CoilyJumpData
{
    bool isJumping = false;
    float elapsed = 0.f;
    float duration = 1.f; //TODO: tweak this value
};

class TileComponent;
class CoilyComponent final : public dae::Component
{
public:
    explicit CoilyComponent(dae::GameObject& owner);
    ~CoilyComponent() override;

    void Update() override;
    void Render() const override;

    void SetState(std::unique_ptr<CoilyState> newState);

    //tile functions
    void SetCurrentTile(std::shared_ptr<TileComponent> tile);
    void SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap);
    std::shared_ptr<TileComponent> GetCoilyTile();

    //Get pointer to qbert's ass
    void SetQbert(std::shared_ptr<dae::GameObject> qbert);
    std::shared_ptr<TileComponent> GetQbertTile();
    
    bool IsJumping() const;
    void TryMove(Direction direction);
    glm::vec3 GetPosition() const; //TODO: make this grid
private:

    //pointer to qbert
    std::shared_ptr<dae::GameObject> m_pQbert;

    //state
    std::unique_ptr<CoilyState> m_pCurrentState = nullptr;

    //incorporate him into the tile mechanic
    std::shared_ptr<TileComponent> m_CurrentTile;
    const std::vector<std::vector<std::shared_ptr<TileComponent>>>* m_pTileMap = nullptr;

    //slight offset to center them in tile
    const float m_xOffset = 15.f; //magic number but pre-calculated value (kevin would love this)
    const float m_yOffset = -40.f; //magic number but pre-calculated value

    CoilyJumpData m_Jump;
};
