#pragma once
#include "GameMode.h"
#include <iostream>

class VersusMode : public GameMode
{
public:
    void Enter() override;
    void Exit() override;
    void Update() override;
};
