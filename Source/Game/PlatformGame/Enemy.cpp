#include "Enemy.h"
#include "Framework/Actor.h"
#include "Core/Json.h"
#include "Player.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"


namespace kiko
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{

		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		//movement
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		


		//m_physicsComponent->ApplyForce(forward * speed * direction);
		//HOMEWORK: try to figure out how to move the bat

	/*	Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			
	*/



	}


	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{	// hidden on 8.29 but DON'T DELETE:
		//	destroyed = true;
		//	EVENT_DISPATCH("OnPlayerDead", 0);

		}

	}



	void Enemy::OnCollisionExit(Actor* other)
	{

	}


	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}











