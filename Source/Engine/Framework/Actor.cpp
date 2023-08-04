#include "Actor.h"
#include "RenderComponent.h"

namespace kiko
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			
			{
				m_lifespan -= dt; 
				m_destroyed = (m_lifespan <= 0);
			}

			//m_transform.position += m_velocity * dt;
			//m_velocity *= std::pow(1.0f - m_damping, dt);

		}
	}
	void Actor::Draw(kiko::Renderer& renderer)
	{
		//if (m_model) m_model->Draw(renderer, m_transform);
		for (auto& component : m_components) // auto so you don't have to think about how many components there will be // & because we're not making a new one - just referencing 
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this; // pointer to an actor 
		m_components.push_back(std::move(component));
	}

}

