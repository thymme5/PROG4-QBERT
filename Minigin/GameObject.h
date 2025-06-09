#pragma once
#include <memory>
#include <vector>
#include <algorithm>

#include "Transform.h"
#include "Component.h"
#include "ImGuiComponent.h"
#include "Observer.h"

enum class RenderLayer { 
    Background = 0, 
    Tiles = 1, 
    Characters = 2, 
    UI = 3 
};

namespace dae
{
    class Texture2D;
    class Component;
    class Observer;

    class GameObject final
    {
    public:

        void Update();
        void Render() const;
        void RenderImGui();
        void SetPosition(float x, float y);

        void SetRenderLayer(RenderLayer layer) { m_RenderLayer = layer; }
        RenderLayer GetRenderLayer() const { return m_RenderLayer; }


        template <typename T, typename... Args>
        T* AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            T* rawPtr = component.get(); 
            m_Components.push_back(std::move(component)); 
            return rawPtr;
        }

        template <typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
            m_Components.erase(
                std::remove_if(m_Components.begin(), m_Components.end(),
                    [](const std::unique_ptr<Component>& component) { return dynamic_cast<T*>(component.get()) != nullptr; }),
                m_Components.end());
        }

        template <typename T>
        T* GetComponent() const
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            for (const auto& component : m_Components)
            {
                if (auto castedComponent = dynamic_cast<T*>(component.get()))
                {
                    return castedComponent;
                }
            }
            return nullptr;
        }

        template <typename T>
        bool HasComponent() const
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            for (const auto& component : m_Components)
            {
                if (dynamic_cast<T*>(component.get()))
                {
                    return true;
                }
            }
            return false;
        }

        GameObject();
        ~GameObject();
        GameObject(GameObject&& other) noexcept = default;
        GameObject& operator=(GameObject&& other) noexcept = default; 
        GameObject(const GameObject& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;

        Transform GetTransform() const;

        GameObject* GetParent() const noexcept;
        int GetChildCount() const noexcept;

        void SetParent(GameObject* parent);
        GameObject* GetChildAt(int index);

        glm::vec3 GetWorldPosition();
        void UpdateWorldPosition();

        //Observers
        void AddObserver(Observer* pObserver);
        void RemoveObserver(Observer* pObserver);
        
        void NotifyObservers(Event event);

    private:

        RenderLayer m_RenderLayer{ RenderLayer::Tiles };

        Transform m_transform{};

        std::vector<std::unique_ptr<Component>> m_Components;

        GameObject* m_Parent;
        std::vector<GameObject*> m_Children;
       
        bool m_positionIsDirty;

        glm::vec3 m_LocalPosition;
        glm::vec3 m_WorldPosition;

        std::vector<Observer*> m_Observers;
    };
}
