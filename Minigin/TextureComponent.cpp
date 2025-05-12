#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject& owner, const std::string& filename)
	: Component(owner), m_texture(ResourceManager::GetInstance().LoadTexture(filename))
{
}
dae::TextureComponent::~TextureComponent()
{

}
void dae::TextureComponent::Update() 
{

}
void dae::TextureComponent::TextureComponent::Render() const 
{
	const auto& pos = m_pOwner->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}
