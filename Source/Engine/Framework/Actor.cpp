#include "Actor.h"
#include "Framework/Components/RenderComponent.h"

namespace kiko
{
	bool Actor::Initialize()
	{
		for (auto& component : m_components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : m_components)
		{
			component->Initialize();
		}
	}

	/////////////////////////////////////////////////
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{

			{
				m_lifespan -= dt;
				m_destroyed = (m_lifespan <= 0);
			}


		}
		for (auto& component : m_components)
		{
			component->Update(dt);
		}

	}
	void Actor::Draw(kiko::Renderer& renderer)
	{
		//if (m_model) m_model->Draw(renderer, m_transform);
		for (auto& component : m_components) // auto so you don't have to think about how many components there will be // & because we're not making a new one - just referencing 
		{
			RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());

			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this; // pointer to an actor 
		m_components.push_back(std::move(component));
	}

}

