#pragma once
#include <iostream>

#include "Command.h"

namespace dae
{
	class PelletCommand final : public Command
	{
	public:
		PelletCommand(GameObject* owner, Event event) :
			m_pOwner(owner),
			m_Event{ event }
		{

		}

		void Execute() override
		{
			switch (m_Event)
			{
			case dae::Event::PlayerDie:
				break;
			case dae::Event::PlayerTookDamage:
				break;
			case dae::Event::PlayerDidDamage:
				break;
			case dae::Event::PlayerPickUpPellets10:
				m_pOwner->NotifyObservers(m_Event);
				break;
			case dae::Event::PlayerPickUpPellets100:
				m_pOwner->NotifyObservers(m_Event);
				break;
			default:
				break;
			}
		}
	private:
		GameObject* m_pOwner;
		Event m_Event;
	};
}
