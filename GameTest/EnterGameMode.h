#pragma once
#include "Command.h"
#include "MainMenuUIComponent.h"
#include "GameModeManager.h"
#include "SinglePlayerMode.h"
#include "CoopMode.h"
#include "VersusMode.h"

class EnterGameMode final : public dae::Command
{
public:
    explicit EnterGameMode(MainMenuUIComponent* menuUI)
        : m_pMenuUI(menuUI)
    {

    }

    void Execute() override
    {
        if (!m_pMenuUI)
            return;

        const int selected = m_pMenuUI->GetSelectedIndex();
        switch (selected)
        {
        case 0:
            GameModeManager::GetInstance().SetMode(std::make_unique<SinglePlayerMode>());
            break;
        case 1:
            GameModeManager::GetInstance().SetMode(std::make_unique<CoopMode>());
            break;
        case 2:
            GameModeManager::GetInstance().SetMode(std::make_unique<VersusMode>());
            break;
        default:
            break;
        }
    }

private:
    MainMenuUIComponent* m_pMenuUI;
};
