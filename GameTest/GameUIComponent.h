#pragma once
#include "Observer.h"
#include "Component.h"
#include "TextComponent.h"
#include "GameModeManager.h"
#include "GameOverMenu.h"
#include "HighScoreManager.h"

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

        void SetRoundText(std::shared_ptr<TextComponent> pText) { m_pRoundText = pText; }
        void SetLevelText(std::shared_ptr<TextComponent> pText) { m_pLevelText = pText; }
        void UpdateLives();


    private: 
        void UpdateScore(int newScore);

        int m_Lives;
        int m_Score;

        int m_Round = 1;
        int m_Level = 1;

        std::shared_ptr<dae::Texture2D> m_HeartTexture;

        std::shared_ptr<TextComponent> m_pRoundText;
        std::shared_ptr<TextComponent> m_pLevelText;

        bool m_IsDirty;
    };
}
