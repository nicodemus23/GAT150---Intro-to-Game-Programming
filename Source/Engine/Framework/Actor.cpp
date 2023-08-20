#include "Actor.h"
#include "Components/RenderComponent.h"

namespace kiko
{
	CLASS_DEFINITION(Actor)
	// Actor& reference, copy this data (name, tag, etc.)
	Actor::Actor(const Actor& other)
	{	// other = copied version
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		// copy components // 
		for (auto& component : other.components) 
		{
			 
			//auto cloneComponent = std::unique_ptr<Component>((Component*)component->Clone().release());
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}
	}

	/////////////////////////////////////////////////
	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f)
		{
			{
				lifespan -= dt;
				destroyed = (lifespan <= 0);
			}
		}
		for (auto& component : components)
		{
			component->Update(dt);
		}

	}
	void Actor::Draw(kiko::Renderer& renderer)
	{
		for (auto& component : components) // auto so you don't have to think about how many components there will be // & because we're not making a new one - just referencing 
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
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		//transform.Read(value);

		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			   // auto& = reference to the value, not copy
				for (auto& componentValue : GET_DATA(value, components).GetArray())
				{
				std:: string type;

				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component));

				}
			
		}
		

	}

}

