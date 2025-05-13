#pragma once
#include "Observer.h"
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
    class GameObject;

    class GameUIComponent : public Component, public Observer
    {
    public:
        GameUIComponent(GameObject& owner);

        void OnNotify(Event event, GameObject* pGameObject) override;

        //virtual functions
        void Update() override;
        void Render() const override;

    private: 
        void UpdateLives();
        void UpdateScore(int newScore);

        int m_Lives;
        int m_Score;
    };
}
