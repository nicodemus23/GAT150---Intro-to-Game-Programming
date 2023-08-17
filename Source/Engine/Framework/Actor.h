#pragma once
#include "Object.h"
#include "Renderer/Renderer.h"
#include "Components/Component.h"
#include <memory>


namespace kiko
{
	class Actor : public Object

	{
	public:

		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; }
		virtual void OnCollision(Actor* other) {} 

		// scene
		class Scene* m_scene = nullptr;
		friend class Scene;

		// game
		class Game* m_game = nullptr;

	public:
		Transform transform;
		std::string tag;
		float lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> components;
		bool destroyed = false;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}

}
