#include "TileComponent.h"

#include "TileComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

using namespace dae;

TileComponent::TileComponent(dae::GameObject& owner)
	: Component(owner)
{
}

void TileComponent::Update() {}

void TileComponent::Render() const {}

void TileComponent::SetID(int id)
{
	m_ID = id;
}

int TileComponent::GetID() const
{
	return m_ID;
}

void TileComponent::SetState(TileState state)
{
	m_CurrentState = state;
}

TileState TileComponent::GetState() const
{
	return m_CurrentState;
}

void TileComponent::SetTargetState(TileState targetState)
{
	m_TargetState = targetState;
}

bool TileComponent::IsCompleted() const
{
	return m_IsCompleted;
}

void TileComponent::OnStepped(GameObject* actor)
{
	if (m_CurrentState == TileState::Target) return;

	m_CurrentState = TileState::Target;
	m_IsCompleted = true;


	actor->NotifyObservers(Event::TileStateChanged);

	//Update texture (inactive now)
	auto* texture = GetOwner()->GetComponent<dae::TextureComponent>();
	if (texture)
	{
		switch (m_CurrentState)
		{
		case TileState::Default:
			texture->SetTexture("testing/tile_default_test.png");
			break;
		//case TileState::Intermediate:
		//	texture->SetTexture("tile_mid.png");
		//	break;
		case TileState::Target:
			texture->SetTexture("testing/tile_finished_test.png");
			break;
		}
	}
}

void dae::TileComponent::SetGridPosition(int row, int col)
{
	m_Row = row;
	m_Col = col;
}

std::pair<int, int> dae::TileComponent::GetGridPosition() const
{
	return { m_Row, m_Col };
}