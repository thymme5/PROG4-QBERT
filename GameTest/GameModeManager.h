#pragma once
#include <memory>
#include "GameMode.h"

class GameMode;

enum class GameModeType 
{ 
    SinglePlayer, 
    Coop, 
    Versus 
};

class GameModeManager
{
public:
    void SetMode(std::unique_ptr<GameMode> newMode);
    void Update();
private:
    std::unique_ptr<GameMode> m_CurrentMode;
};