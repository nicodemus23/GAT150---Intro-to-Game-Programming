#include "Enemy.h"
#include "Framework/Actor.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"


namespace kiko
{
	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>(); // 

		auto collisionComponent = GetComponent < kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
			}
		}
		return true;
	}

	void Enemy::OnDestroy()
	{
		Actor::OnDestroy();
	}



	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		auto collisionComponent = GetComponent < kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
			}
		}

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();

		if (player)
		{

			Actor::Update(dt);
			kiko::vec2 direction = player->transform.position - transform.position;

			// turn towards player
			float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
			//transform.rotation += turnAngle * dt;
			m_physicsComponent->ApplyTorque(turnAngle * 0.0001f);


			// check for player in sight 
			if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
			{
			}
		}

		m_physicsComponent->ApplyForce(forward * speed);

		//transform.position += forward * speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());


	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Player")
		{
			EVENT_DISPATCH("OnAddPoints", 100);

			//	m_game->AddPoints(100);
			destroyed = true;

			// create explosion
			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = kiko::random(100);
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 100;
			data.damping = 0.5f;

			data.color = kiko::Color{ 1, 1, 1, 1 };

			kiko::Transform transform{ this->transform.position, 0, 1};
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->lifespan = 0.1f;
			m_scene->Add(std::move(emitter));
		}
	}

	
		void Enemy::Read(const json_t& value)
		{
			Actor::Read(value);

			READ_DATA(value, speed);
			READ_DATA(value, turnRate);
			READ_DATA(value, fireRate);

		}

	
}
