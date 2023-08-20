#pragma once
#include "Actor.h"
#include <list>

namespace kiko
{
	// if we're just dealing with references and pointers, you can use a forward declarations:
	class Renderer;
	
	class Scene
	{
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		// pointer contains location of the next list (linked list)
		void Add(std::unique_ptr<Actor> actor);
		
		// clears the scene:
		void RemoveAll(bool force =  false);

		bool Load(const std::string& filename); // bool can fail - good for when you want to add an ERROR_LOG
		void Read(const json_t& value);

		// templates // always create declaration and definition in the .h file
		template<typename T>
		T* GetActor();
		
		template<typename T = Actor> // makes name passed by GetActorByName in scene.json optional
		T* GetActorByName(const std::string& name);

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result; 
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name)
			{
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		
		}
		return nullptr;
	}
}

//