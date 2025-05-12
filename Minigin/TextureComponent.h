#pragma once
#include "Component.h"
#include <iostream>
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

class GameObject;

namespace dae
{
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject& pOwner, const std::string& filename, float scale = 1.f);
		virtual ~TextureComponent();
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_texture{};
		float m_Scale;
	};
}

