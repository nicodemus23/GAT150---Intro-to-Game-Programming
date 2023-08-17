#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"


bool Enemy::Initialize()
{
	Actor::Initialize();

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
		
		// follow player 1
		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		transform.rotation += turnAngle * dt;


		// check for player in sight 
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
		}
	}

	
	transform.position += forward * speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());


}

void Enemy::OnCollision(Actor* other)
{	
	if (other->tag == "Player")
	{
		m_game->AddPoints(100);
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
		data.speedMax = 250;
		data.damping = 0.5f;

		data.color = kiko::Color{ 1, 1, 1, 1 };

		kiko::Transform transform{ transform.position, 0, 1};
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->lifespan = 0.1f;
		m_scene->Add(std::move(emitter));
	}

}
