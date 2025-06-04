#pragma once
#include "Component.h"
#include "CoilyState.h"
#include "GameObject.h"
#include "TileComponent.h"

class TileComponent;
class CoilyComponent final : public dae::Component
{
public:
    explicit CoilyComponent(dae::GameObject& owner);
    ~CoilyComponent() override;

    void Update() override;
    void Render() const override;

    void SetState(std::unique_ptr<CoilyState> newState);

    //utility functions for the states to use
    //ignore this
    void MoveBy(const glm::vec3& offset);
    void SetPosition(const glm::vec3& pos);
    glm::vec3 GetPosition() const;

    //tile functions
    void SetCurrentTile(std::shared_ptr<TileComponent> tile);
    void SetTileMap(const std::vector<std::vector<std::shared_ptr<TileComponent>>>& tileMap);


private:
    std::unique_ptr<CoilyState> m_pCurrentState = nullptr;
    
    //incorporate him into the tile mechanic
    std::shared_ptr<TileComponent> m_CurrentTile;
    const std::vector<std::vector<std::shared_ptr<TileComponent>>>* m_pTileMap = nullptr;

};
