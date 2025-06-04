#pragma once
#include "CoilyState.h"

class EggState final : public CoilyState {
public:
    void Enter(CoilyComponent& coily) override;
    void Update(CoilyComponent& coily) override;
    void Exit(CoilyComponent& coily) override;

private:
    //float m_DropSpeed = 100.0f; //pixels per second

    float m_AccumulatedTime = 0.0f;
};
