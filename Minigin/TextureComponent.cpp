#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject& owner, const std::string& filename, float scale)
	: Component(owner), m_texture(ResourceManager::GetInstance().LoadTexture(filename)), m_Scale(scale)
{
}
dae::TextureComponent::~TextureComponent()
{

}
void dae::TextureComponent::Update() 
{

}
void dae::TextureComponent::Render() const 
{
	const auto& pos = m_pOwner->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_texture->GetSize().x * m_Scale, m_texture->GetSize().y * m_Scale);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
