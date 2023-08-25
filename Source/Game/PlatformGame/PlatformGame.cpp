#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "PlatformGame.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include <cmath>

bool PlatformGame::Initialize()
{

	// CREATE FONT AND TEXT OBJECTS // shared pointer used so multiple assets can use it. 
	//m_font = GET_RESOURCE(kiko::Font, "StarJediLogoMonoline-6nGg.ttf", 30);
	
	// load audio //
	//kiko::g_audioSystem.AddAudio("laser", "Laser_Shoot.wav");

	// create scene //

	m_scene->Load("scenes/scene.json");
	m_scene->Initialize();

	// add events

	

	

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
	{
		
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName("Background")->active; // way to hide and unhide actors without destroying them

			// check if null 
			//auto actor = m_scene->GetActorByName<kiko::Actor>("Background");
			//if (actor) actor->active = false;
		}
		
		break;
	}
	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			// CREATE PLAYER //

			/*auto player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 365, 300 }, 0, 0.075f });
			player->tag = "Player";
			player->m_game = this;*/

			// CREATE COMPONENTS //

			// sprite component //
			//auto renderComponent = CREATE_CLASS(SpriteRenderComponent)
			//renderComponent->m_texture = GET_RESOURCE (kiko::Texture, "Jet_01.png", kiko::g_renderer);
			//player->AddComponent(std::move(renderComponent));

			//// physics component //
			//auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
			//physicsComponent->m_damping = 0.9f;
			//player->AddComponent(std::move(physicsComponent));

			//// collision component //
			//auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			//collisionComponent->m_radius = 30.0f;
			//player->AddComponent(std::move(collisionComponent));

			// initialize player //
			//player->Initialize(); // doing Initialize() operation before move because the unique pointer is no longer valid once moved
			//m_scene->Add(std::move(player));

		}
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			//  CREATE ENEMY //
		/*	m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 0.05f});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			auto renderComponent = std::make_unique<kiko::SpriteRenderComponent>();
			renderComponent->m_texture = GET_RESOURCE (kiko::Texture, "enemy_01.png", kiko::g_renderer);
			enemy->AddComponent(std::move(renderComponent));

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
			m_scene->Add(std::move(enemy));*/

			// add WeaponComponents here
		}
		break;

	case eState::PlayerDeadStart:
		
		break;

	case PlatformGame::eState::PlayerDead:
		
		break;
	case PlatformGame::eState::GameOver:
		
		break;
	default:
		break;
	}

	
	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{

}
