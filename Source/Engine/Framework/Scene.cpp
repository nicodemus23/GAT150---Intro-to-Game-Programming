#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"


namespace kiko
{
	bool Scene::Initialize()
	{
		for (auto& actor : m_actors) actor->Initialize();
		return true;
	}

	void Scene::Update(float dt)
	{
		// update and remove destroyed actors 
		auto iter = m_actors.begin();

		// goes through each element // iterator contains actor // checking to see if actor is destroyed 
		while (iter != m_actors.end())
		{
			if ((*iter)->active) (*iter)->Update(dt);
			// if actor is destroyed, erase, else just go to the next one (++iter)
			((*iter)->destroyed) ? iter = m_actors.erase(iter) : iter++;
		}

		// check collisions // DON'T DELETE // 
		//for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) // iter1
		//{
		//	for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) // iter2
		//	{
		//		CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
		//		CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

		//		if (!collision1 || !collision2) continue; // same as collision1 == nullptr || collision2 == nullptr

		//		if (collision1->CheckCollision(collision2))
		//		{
		//			(*iter1)->OnCollision(iter2->get()); //*
		//			(*iter2)->OnCollision(iter1->get());
		//		}
		//	}
		//}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			if (actor->active) actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll(bool force)
	{
		// update and remove destroyed actors 
		auto iter = m_actors.begin();

		// goes through each element // iterator contains actor // checking to see if actor is destroyed 
		while (iter != m_actors.end())
		{

			// if actor is destroyed, erase, else just go to the next one (++iter)
			(force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
		}

	}

	bool Scene::Load(const std::string& filename)
	{	// Should this be !Json?? It wasn't but I got the error message every time. 
		rapidjson::Document document;
		if (!Json::Load(filename, document))
		{
			ERROR_LOG("Could not load scene file: " << filename);
			return false; // if fails return false
		}
		Read(document);

		return true;
	}

	void Scene::Read(const json_t& value)
	{
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
		{
			// auto& = reference to the value, not copy
			for (auto& actorValue : GET_DATA(value, actors).GetArray())
			{
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->Read(actorValue);
				// if the actor is a prototype then Register as prototype, else add to scene
				if (actor->prototype)
				{
					std::string name = actor->name; // to guarantee order of operations
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}
	}
};



//NOTES:
//// get the distance between these two objects (iter1 and iter2) *the distance is the sum of two radii
//float distance = (*iter1)->transform.position.Distance((*iter2)->transform.position);
//// get the radii of these two objects 
//float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius(); // GetRadius() comes from Actor.h 

//if (collision1->CheckCollision(collision2))
//{	// dereferenced iter1 collides with iter2 / tells first object that the second object collided with it
//	(*iter1)->OnCollision(iter2->get()); // (*iter) gives us the unique_ptr // iter2 gets the actual object 
//	(*iter2)->OnCollision(iter1->get()); // opposite of above 
//}