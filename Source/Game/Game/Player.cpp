#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
// need this?:
#include "Audio/AudioSystem.h"



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
			float scale = transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale; // can add * 0.75 after scale if necessary
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
	transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

	m_physicsComponent->ApplyForce(forward * speed * thrust);

	//transform.position += forward * speed * thrust * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	// fire Weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{	// rocket1
		auto weapon = INSTANTIATE(Weapon, "Rocket");
		weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		// rocket2
		weapon = INSTANTIATE(Weapon, "Rocket");
		weapon->transform = { transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	
	// add Weapon sound here:

	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);

}

void Player::OnCollision(Actor* other)
{	
	if (other->tag == "Enemy")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}
}

