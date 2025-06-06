#pragma once

namespace dae
{
	class GameObject;

	enum class Event
	{
		PlayerDied,
		PlayerLandedOnTile,
		TileStateChanged,
		PlayerWonGame,
		LevelComplete
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Event event, GameObject* pGameObject) = 0;
	};
}
