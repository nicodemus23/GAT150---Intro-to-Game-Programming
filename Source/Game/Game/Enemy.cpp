#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Player.h"
#include "SpaceGame.h"


void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();

	if (player)
	{

		Actor::Update(dt);
		kiko::vec2 direction = player->m_transform.position - m_transform.position;
		
		// follow player 1
		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		m_transform.rotation += turnAngle * dt;


		// check for player in sight 
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
		}
	}

	
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());


}

void Enemy::OnCollision(Actor* other)
{	// checks the type of player
	//Player* p = dynamic_cast<Player*>(other);

	if (other->m_tag == "Player")
	{
		m_game->AddPoints(100);
		m_destroyed = true;

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
		data.speedMax = 250;
		data.damping = 0.5f;

		data.color = kiko::Color{ 1, 1, 1, 1 };

		kiko::Transform transform{ m_transform.position, 0, 1};
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->m_lifespan = 0.1f;
		m_scene->Add(std::move(emitter));
	}

}
