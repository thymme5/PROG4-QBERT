#pragma once
#include "GameMode.h"
class MainMenu : public GameMode
{
public:
    void Enter() override;
    void Exit() override;
    void Update() override;
};
