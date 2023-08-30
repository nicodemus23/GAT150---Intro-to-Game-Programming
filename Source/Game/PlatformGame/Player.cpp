#include "Player.h"
#include "Framework/Actor.h"
#include "Core/Json.h"
#include "Framework/Components/PhysicsComponent.h"


#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"


namespace kiko
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{

		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();
		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		bool onGround = (groundCount > 0);
		//movement
		float direction = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction = 1;

		kiko::vec2 forward = kiko::vec2{ 1, 0 };
		m_physicsComponent->ApplyForce(forward * speed * direction);


		// the more gravity, the more speed you'll need in json for Player


		//transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		//transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

		// jump

		if (onGround && 
			kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}

		// animation
		vec2 velocity = m_physicsComponent->velocity;

		// check if movin' 
		if (std::fabs(velocity.x) > 0.2f) // absolute value of a float
		{	
			if (direction != 0) m_spriteAnimComponent->flipH = (direction < 0);

			m_spriteAnimComponent->SetSequence("run");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
		}

	}


	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			//destroyed = true;
			//EVENT_DISPATCH("OnPlayerDead", 0);

		}
		if (other->tag == "Ground") groundCount++;

	}



	void Player::OnCollisionExit(Actor* other)
	{
		// if you leave the ground youre going to decrease the ground count
		// only if youre on the ground you can jump

		if (other->tag == "Ground") groundCount--;
	}




	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}











