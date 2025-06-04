#pragma once
#include "Component.h"
#include <utility>

// Coordinate system used for moving entities
//
//                               (0,0)
//                          (1,0)     (1,1)
//                     (2,0)     (2,1)     (2,2)
//                (3,0)     (3,1)     (3,2)     (3,3)
//           (4,0)     (4,1)     (4,2)     (4,3)     (4,4)
//      (5,0)     (5,1)     (5,2)     (5,3)     (5,4)     (5,5)
// (6,0)     (6,1)     (6,2)     (6,3)     (6,4)     (6,5)     (6,6)

// todo: work this out to a state system with classes
enum class TileState
{
	Default,
	Intermediate,
	Target
};

class TileComponent final : public dae::Component
{
public:
	explicit TileComponent(dae::GameObject& owner);
	~TileComponent() override = default;

	void Update() override;
	void Render() const override;

	void SetID(int id);
	int GetID() const;

	void SetState(TileState state);
	TileState GetState() const;

	void SetTargetState(TileState targetState);
	bool IsCompleted() const;

	void OnStepped(dae::GameObject* actor);

	//grid position (coord system)
	void SetGridPosition(int row, int col);
	std::pair<int, int> GetGridPosition() const;

private:
	int m_ID{}; //basically index
	TileState m_CurrentState{ TileState::Default };
	TileState m_TargetState{ TileState::Target };
	bool m_IsCompleted{ false };

	int m_Row{};
	int m_Col{};
};
