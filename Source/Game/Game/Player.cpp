#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"


bool Player::Initialize()
{
	Actor::Initialize();

	// cache off
	m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

	auto collisionComponent = GetComponent < kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = m_transform.scale;
			collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale * 0.75f; // remove or adjust 0.75 if necessary
		}
	}

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	// fire weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
	 !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		// create weapon // 
		kiko::Transform transform1{m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(500.0f, transform1);
		weapon->m_tag = "Player"; // player weapon

		// add rocket image // rocket 1
		auto component = std::make_unique<kiko::SpriteRenderComponent>();
		component->m_texture = GET_RESOURCE (kiko::Texture, "test.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		// rocket collision // rocket 1
		auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		// create weapon // rocket 2
		kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(10.0f), 1 };
		weapon = std::make_unique<Weapon>(400.0f, transform2);
		weapon->m_tag = "Player"; // player weapon

		// add rocket image //  rocket 2
		component = std::make_unique<kiko::SpriteRenderComponent>();
		component->m_texture = GET_RESOURCE (kiko::Texture, "test.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		// rocket collision // rocket 2
		collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		// add weapon sound here:

	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);

}

void Player::OnCollision(Actor* other)
{	
	if (other->m_tag == "Enemy")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}
}

