#pragma once
#include "Component.h"
#include "CoilyState.h"
#include "GameObject.h"

class CoilyComponent final : public dae::Component
{
public:
    explicit CoilyComponent(dae::GameObject& owner);
    ~CoilyComponent() override;

    void Update() override;
    void Render() const override;

    void SetState(std::unique_ptr<CoilyState> newState);

    //utility functions for the states to use
    void MoveBy(const glm::vec3& offset);
    void SetPosition(const glm::vec3& pos);
    glm::vec3 GetPosition() const;

private:
    std::unique_ptr<CoilyState> m_pCurrentState = nullptr;
};
