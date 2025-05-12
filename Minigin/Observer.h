#pragma once

namespace dae
{
	class GameObject;
	enum class Event
	{
		PlayerDie,
		PlayerTookDamage,
		PlayerDidDamage,
		PlayerPickUpPellets10,
		PlayerPickUpPellets100
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Event event, GameObject* pGameObject) = 0;
	};
}
