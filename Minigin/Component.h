#pragma once

namespace dae
{
	class GameObject;
	
	class Component
	{
	public:
		Component(GameObject& owner);
		virtual ~Component();

		virtual void Update() = 0;
		virtual void Render() const = 0;
	protected:
		GameObject* m_pOwner;
	};
}
