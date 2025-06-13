#pragma once
#include "Command.h"
#include "MainMenuUIComponent.h"
#include "GameModeManager.h"
#include "SinglePlayerMode.h"
#include "CoopMode.h"
#include "VersusMode.h"
#include "HighScoreMenu.h"
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
            GameModeManager::GetInstance().SetMode(std::make_unique<SinglePlayerMode>(1));
            break;
        case 1:
            GameModeManager::GetInstance().SetMode(std::make_unique<CoopMode>(1));
            break;
        case 2:
            GameModeManager::GetInstance().SetMode(std::make_unique<VersusMode>(1));
            break;
        case 3:
            GameModeManager::GetInstance().SetMode(std::make_unique<HighScoreMenu>( ));
            break;
        default:
            break;
        }
    }

private:
    MainMenuUIComponent* m_pMenuUI;
};
