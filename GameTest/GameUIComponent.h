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

        void SetRoundText(TextComponent* pText) { m_pRoundText = pText; }
        void SetLevelText(TextComponent* pText) { m_pLevelText = pText; }

    private: 
        void UpdateLives();
        void UpdateScore(int newScore);

        int m_Lives;
        int m_Score;

        int m_Round = 1;
        int m_Level = 1;

        std::shared_ptr<dae::Texture2D> m_HeartTexture;

        TextComponent* m_pRoundText = nullptr;
        TextComponent* m_pLevelText = nullptr;

        bool m_IsDirty;
    };
}
