#include "Scene.h"


namespace kiko
// adding namespace to the .cpp file before declaring the declaration from .h will truncate the need for kiko::
{
	void Scene::Update(float dt)
	{

	// update and remove destroyed actors 
	auto iter = m_actors.begin();

	// goes through each element // iterator contains actor // checking to see if actor is destroyed 
	while (iter != m_actors.end())
	{
		(*iter)->Update(dt);
		// if actor is destroyed, erase, else just go to the next one (++iter)
		((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;			
	}

		// check collisions // do this while we're NOT at the end // end is one past the last one 
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) // iter1
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) // iter2
			{
				// get the distance between these two objects (iter1 and iter2) *the distance is the sum of two radii
				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);
				// get the radii of these two objects 
				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius(); // GetRadius() comes from Actor.h 

				if (distance <= radius)
				{	// dereferenced iter1 collides with iter2 / tells first object that the second object collided with it
					(*iter1)->OnCollision(iter2->get()); // (*iter) gives us the unique_ptr // iter2 gets the actual object 
					(*iter2)->OnCollision(iter1->get()); // opposite of above 
				}
			}
		}
		
	}


	void Scene::Draw(Renderer& renderer)

		{
		for (auto& actor : m_actors) actor->Draw(renderer);
		}


	void Scene::Add(std::unique_ptr<Actor> actor)
	{

		actor->m_scene = this;
		m_actors.push_back(std::move(actor));

	}


	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
}
