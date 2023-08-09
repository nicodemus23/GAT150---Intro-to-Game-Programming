#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>


namespace kiko
{
	class Actor

	{
	public:
		Actor() = default;
		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; }
		virtual void OnCollision(Actor* other) {} // {} is a dummy function so it doesn't get implemented 

	//	void AddForce(const vec2& force) { m_velocity += force; }
	//	void SetDamping(float damping) { m_damping = damping; }

		// scene
		class Scene* m_scene = nullptr;
		// lets this class see your "privates" 
		friend class Scene;

		// game
		class Game* m_game = nullptr;

		Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
		//std::vector<Component> m_components; can't create an object of an abstract class <Component> without creating a pointer to the Abstract Class // unique pointer forces deletion so we don't have to do delete, delete

		bool m_destroyed = false;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}

}
