#include "TileComponent.h"

#include "GameObject.h"
#include "TextureComponent.h"

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

void TileComponent::SetColorStates(const std::string& startColor, const std::string& intermediateColor, const std::string& targetColor)
{
	m_StartColor = startColor;
	m_IntermediateColor = intermediateColor;
	m_TargetColor = targetColor;
}

std::string TileComponent::GetCurrentColor() const
{
	switch (m_CurrentState)
	{
	case TileState::Default:
		return m_StartColor;
	case TileState::Intermediate:
		return m_IntermediateColor;
	case TileState::Target:
		return m_TargetColor;
	default:
		return {};
	}
}

void TileComponent::OnStepped(dae::GameObject* actor)
{
	if (m_CurrentState == TileState::Target) return;

	m_CurrentState = TileState::Target;
	m_IsCompleted = true;

	actor->NotifyObservers(dae::Event::TileStateChanged);

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

void TileComponent::SetGridPosition(int row, int col)
{
	m_Row = row;
	m_Col = col;
}

std::pair<int, int> TileComponent::GetGridPosition() const
{
	return { m_Row, m_Col };
}