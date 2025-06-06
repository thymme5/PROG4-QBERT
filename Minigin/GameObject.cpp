#pragma once
#include <string>
#include <iostream>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

GameObject::GameObject():
	m_transform{},
    m_Parent{},
    m_Children{},
    m_positionIsDirty{}
{
}

GameObject::~GameObject()
{
    m_Children.clear();
};

void GameObject::Update()
{
    for (const auto& component : m_Components)
    {
        component->Update();
    }
}

void GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}
}
void GameObject::RenderImGui()
{
    for (auto& component : m_Components)
    {
        if (auto* imguiComponent = dynamic_cast<ImGuiComponent*>(component.get()))
        {
            imguiComponent->ImGuiRender();
        }
    }
}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

Transform GameObject::GetTransform() const
{
	return m_transform;
}

GameObject* GameObject::GetParent() const noexcept
{
	return m_Parent;
}
int GameObject::GetChildCount() const noexcept
{
	return int(m_Children.size());
}

void GameObject::SetParent(GameObject* parent) //todo: fix lol
{
    if (parent == this || std::find(m_Children.begin(), m_Children.end(), parent) != m_Children.end())
    {
        return; 
    }

    if (m_Parent)
    {
        auto it = std::remove(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), this);
        m_Parent->m_Children.erase(it, m_Parent->m_Children.end());
    }

    m_Parent = parent;
    
    if (parent)
    {
        parent->m_Children.push_back(this);
    }

    if (parent)
    {
        m_transform.SetPosition(parent->m_transform.GetPosition().x + m_transform.GetPosition().x,
            parent->m_transform.GetPosition().y + m_transform.GetPosition().y, 0.0f);
        m_transform.SetRotation(parent->m_transform.GetRotation());
    }
    else
    {
        m_transform.SetPosition(0.0f, 0.0f, 0.0f);
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

GameObject* GameObject::GetChildAt(int index)
{
    if (index < 0 || index >= static_cast<int>(m_Children.size())) {
        return nullptr;
    }

    return m_Children[index];
}

glm::vec3 GameObject::GetWorldPosition()
{
    if (m_positionIsDirty)
        UpdateWorldPosition();
    return m_WorldPosition;
}
void GameObject::UpdateWorldPosition()
{
    if (m_positionIsDirty)
    {
        if (m_Parent == nullptr)
            m_WorldPosition = m_LocalPosition;
        else
            m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
    }
    m_positionIsDirty = false;
}

void GameObject::AddObserver(Observer* pObserver)
{
    m_Observers.push_back(pObserver);
}
void GameObject::RemoveObserver(Observer* pObserver)
{
    m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), pObserver), m_Observers.end());
}

void GameObject::NotifyObservers(Event event)
{
    for (Observer* observer : m_Observers)
    {
        observer->OnNotify(event, this);
    }
}