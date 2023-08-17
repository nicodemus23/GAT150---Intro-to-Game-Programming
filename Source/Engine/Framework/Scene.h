#pragma once
#include <list>
#include "Actor.h"



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
		void RemoveAll();

		bool Load(const std::string& filename); // bool can fail - good for when you want to add an ERROR_LOG
		void Read(const json_t& value);


		template<typename T>
		T* GetActor();

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
}